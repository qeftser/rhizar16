
#include "thread_pond.h"
#include <handleapi.h>
#include <processthreadsapi.h>
#include <synchapi.h>
#include <thread>

namespace Rhizar16 {

#ifdef _WIN32

void ThreadPond::worker_callback(worker_init * runtime) {

   //printf("entering barrier...\n");
   EnterSynchronizationBarrier(runtime->barrier,0);

   while ( *runtime->live ) {

      InterlockedIncrement(runtime->ready_count);

      std::unique_lock lock(*runtime->lock);
      //printf("Waiting...\n");
      runtime->notify->wait_for(lock,std::chrono::milliseconds(10));
  //    printf("Started...\n");

      //printf("%s\n",*runtime->live ? "LIVE" : "DEAD");

      lock.unlock();

      //printf("Lock released...\n");

      InterlockedDecrement(runtime->ready_count);

      while (!runtime->tasks->empty() && *runtime->live) {

         task * worker_task = runtime->tasks->pop();
         if (worker_task) {
 //           printf("running task...\n");
            worker_task->func(worker_task->arg);

            /* note, this has a chance to leak memory when the
             * thread is reclaimed by the system on exit. However
             * I am going to ignore this for the windows implimentation
             * because I am done caring at this point xD lol         */
            delete worker_task;
         }
      }

      //printf("loop exited\n");
   }
   //printf("thread exiting\n");
   return;
}

ThreadPond::ThreadPond(uint32_t thread_count)
   : thread_count(thread_count ? thread_count : 1) {

   threads = new std::thread[this->thread_count];
   runtime = new worker_init[this->thread_count];
   ready_count = (LONG *)_aligned_malloc(sizeof(LONG),32);

   *ready_count = 0;
   live = TRUE;

   LPSYNCHRONIZATION_BARRIER barrier = NULL;
   InitializeSynchronizationBarrier(barrier, 1 + this->thread_count, -1);

   for (u_int i = 0; i < this->thread_count; ++i) {
      runtime[i].ready_count = ready_count;
      runtime[i].tasks = &tasks;
      runtime[i].notify = &notify;
      runtime[i].lock = &lock;
      runtime[i].live = &live;
      runtime[i].barrier = barrier;
      threads[i] = std::thread(worker_callback,&runtime[i]);
   }

   EnterSynchronizationBarrier(barrier,0);
   DeleteSynchronizationBarrier(barrier);
}

ThreadPond::~ThreadPond() {

   while (!tasks.empty())
      delete tasks.pop();

   live = FALSE;
   lock.lock();
   lock.unlock();
   notify.notify_all();
   for (u_int i = 0; i < thread_count; ++i) {
//      printf("killing thread %d %s %s\n",i,live ? "TRUE" : "FALSE",*runtime[i].live ? "TRUE" : "FALSE");
      if (threads[i].joinable())
         threads[i].join();
   }

   delete[] threads;
   delete[] runtime;
   _aligned_free(ready_count);

}

void ThreadPond::queue(std::function<void(void *)> func, void * arg) {

   task * new_task = new task;
   new_task->func = func;
   new_task->arg = arg;

   tasks.push(new_task);

   notify.notify_all();

}

bool ThreadPond::wait(std::chrono::nanoseconds timeout) {
   if (timeout == std::chrono::nanoseconds(0)) {
      do {

         if (tasks.empty() && *ready_count == thread_count)
            return true;
         std::this_thread::sleep_for(std::chrono::nanoseconds(100));
         std::this_thread::yield();
      } while (1);

   }
   else {
      auto start = std::chrono::steady_clock::now();

      do {

         if (tasks.empty() && *ready_count == thread_count)
            return true;
         std::this_thread::sleep_for(std::chrono::nanoseconds(100));
         std::this_thread::yield();

      } while (std::chrono::nanoseconds(std::chrono::steady_clock::now() - start) < timeout);

      return false;
   }
}



#elif defined(__unix__)

void ThreadPond::thread_callback(int sig) {
   (void)sig;
   return;
}

void ThreadPond::termination_callback(int sig) {
   (void)sig;
   pthread_exit(NULL);
   return;
}

void sigsegv_mask(int sig) {
   (void)sig;
   printf("dying!\n");
   return;
}

void * ThreadPond::worker_runtime(void * init) {
   struct worker_init * runtime = (struct worker_init *)init;
   uint8_t ready = 1;

   pthread_mutex_lock(runtime->lock_work);
   while (-1 == write(runtime->notify_ready,&ready,1));

   pthread_barrier_wait(runtime->barrier);
   runtime->barrier = NULL;

   do {

      pthread_cond_wait(runtime->notify_work,runtime->lock_work);
      pthread_mutex_unlock(runtime->lock_work);

      if (*runtime->worker_task == NULL)
         continue;

      (*runtime->worker_task)->func((*runtime->worker_task)->arg);

      pthread_mutex_lock(runtime->lock_work);
      while (write(runtime->notify_ready,&ready,1) < 1);

   } while (1);

   return NULL;
}

void * ThreadPond::scheduler_runtime(void * init) {
   struct scheduler_init * runtime = (struct scheduler_init *)init;

   pthread_barrier_wait(runtime->barrier);
   runtime->barrier = NULL;

   int maxfd = INT_MIN;
   for (int i = 0; i < runtime->thread_count; ++i) {
      if (runtime->read_end[i] > maxfd)
         maxfd = runtime->read_end[i];
   }
   
   fd_set read_set;
   struct timeval wait_delay;
   int finished;
   int ready[runtime->thread_count];
   explicit_bzero(ready,sizeof(int) * runtime->thread_count);

   sigset_t free_mask;
   sigemptyset(&free_mask);
   sigaddset(&free_mask,__RHIZAR16_THREAD_TERMINATE__);

   do {

      FD_ZERO(&read_set);
      for (int i = 0; i < runtime->thread_count; ++i) {
         FD_SET(runtime->read_end[i],&read_set);
      }

      explicit_bzero(&wait_delay,sizeof(struct timeval));
      wait_delay.tv_usec = 1000;

      finished = select(maxfd + 1,&read_set,NULL,NULL,&wait_delay);

      if (finished > 0) {
         for (int i = 0; i < runtime->thread_count; ++i) {
            if (FD_ISSET(runtime->read_end[i],&read_set)) {
               while (read(runtime->read_end[i],&ready[i],1) < 1);

               /* avoid the case where the destructor is called when
                * we are freeing memory, which could lead to a 
                * double-free if the thread is killed before it can
                * mark the memory as freed.                        */
               pthread_sigmask(SIG_BLOCK,&free_mask,NULL);

               free(runtime->task_ptr[i]);
               runtime->task_ptr[i] = NULL;

               runtime->active->fetch_add(-1);

               pthread_sigmask(SIG_UNBLOCK,&free_mask,NULL);
            }
         }
      }

      /* avoid killing the thread while it has obtained the queue lock */
      pthread_sigmask(SIG_BLOCK,&free_mask,NULL);
      for (int i = 0; i < runtime->thread_count && (!runtime->task_queue->empty()); ++i) {

         if (ready[i]) {

            runtime->active->fetch_add(1);

            runtime->task_ptr[i] = runtime->task_queue->pop();

            pthread_mutex_lock(&runtime->mutexes[i]);
            pthread_mutex_unlock(&runtime->mutexes[i]);
            pthread_cond_signal(&runtime->triggers[i]);

            ready[i] = 0;
         }

      }
      pthread_sigmask(SIG_UNBLOCK,&free_mask,NULL);

   } while (1);

   return NULL;
}

ThreadPond::ThreadPond(uint32_t thread_count)
   : thread_count(thread_count ? thread_count : 1) {

   worker_data = (worker_init *)malloc(sizeof(worker_init) * this->thread_count);
   workers = (pthread_t *)malloc(sizeof(pthread_t) * this->thread_count);
   task_ptr = (task **)malloc(sizeof(task *) * this->thread_count);
   read_end = (int *)malloc(sizeof(int) * this->thread_count);
   write_end = (int *)malloc(sizeof(int) * this->thread_count);
   triggers = (pthread_cond_t *)malloc(sizeof(pthread_cond_t) * this->thread_count);
   mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * this->thread_count);

   bzero(worker_data,sizeof(worker_init)*this->thread_count);
   bzero(workers,sizeof(pthread_t)*this->thread_count);
   bzero(task_ptr,sizeof(task *)*this->thread_count);
   bzero(read_end,sizeof(int)*this->thread_count);
   bzero(write_end,sizeof(int)*this->thread_count);
   bzero(triggers,sizeof(int)*this->thread_count);
   bzero(mutexes,sizeof(int)*this->thread_count);

   for (int i = 0; i < this->thread_count; ++i) {
      pthread_mutex_init(&mutexes[i],NULL);
      pthread_cond_init(&triggers[i],NULL);
   }

   /* all workers will declare themselves ready at start, which
    * means that the scheduler implicitly assumes that they were
    * active before. This means that the starting active count
    * shoud be set to the number of threads in the pond        */
   scheduler_active = this->thread_count;

   pthread_barrier_t barrier;
   pthread_barrier_init(&barrier,NULL,2 + this->thread_count);

   struct sigaction thread_action;
   bzero(&thread_action,sizeof(struct sigaction));
   thread_action.sa_handler = thread_callback;

   sigaction(__RHIZAR16_THREAD_SIGNAL__,&thread_action,NULL);

   thread_action.sa_handler = termination_callback;
   sigaction(__RHIZAR16_THREAD_TERMINATE__,&thread_action,NULL);

   thread_action.sa_handler = sigsegv_mask;
   sigaction(SIGSEGV,&thread_action,NULL);

   bzero(&scheduler_data,sizeof(scheduler_init));
   scheduler_data.active       = &scheduler_active;
   scheduler_data.thread_count = this->thread_count;
   scheduler_data.read_end     = read_end;
   scheduler_data.task_ptr     = task_ptr;
   scheduler_data.threads      = workers;
   scheduler_data.task_queue   = &task_queue;
   scheduler_data.barrier      = &barrier;
   scheduler_data.triggers     = triggers;
   scheduler_data.mutexes      = mutexes;

   pthread_create(&scheduler,NULL,scheduler_runtime,(void *)&scheduler_data);
   pthread_setname_np(scheduler,"scheduler");

   int collecter[2];
   for (int i = 0; i < this->thread_count; ++i) {

      pipe(collecter);
      read_end [i] = collecter[0];
      write_end[i] = collecter[1];

      worker_data[i].notify_ready = write_end[i];
      worker_data[i].worker_task  = &task_ptr[i];
      worker_data[i].barrier      = &barrier;
      worker_data[i].notify_work  = &triggers[i];
      worker_data[i].lock_work    = &mutexes[i];

      pthread_create(&workers[i],NULL,worker_runtime,(void *)&worker_data[i]);
      pthread_setname_np(workers[i],"worker");

   }

   pthread_barrier_wait(&barrier);
   pthread_barrier_destroy(&barrier);

}

ThreadPond::~ThreadPond() {

   pthread_kill(scheduler,__RHIZAR16_THREAD_TERMINATE__);
   pthread_join(scheduler,NULL);
   for (uint32_t i = 0; i < thread_count; ++i) {
      pthread_kill(workers[i],__RHIZAR16_THREAD_TERMINATE__);
      pthread_join(workers[i],NULL);
   }

   for (uint32_t i = 0; i < thread_count; ++i)
      free(task_ptr[i]);

   while (!task_queue.empty()) {
      free(task_queue.pop());
   }

   free(task_ptr);
   free(workers);
   free(worker_data);

   for (int i = 0; i < thread_count; ++i) {
      close(read_end[i]);
      close(write_end[i]);
   }
   free(read_end);
   free(write_end);

   for (int i = 0; i < this->thread_count; ++i) {
      pthread_mutex_destroy(&mutexes[i]);
      pthread_cond_destroy(&triggers[i]);
   }
   free(mutexes);
   free(triggers);

}

bool ThreadPond::wait(std::chrono::nanoseconds timeout) {
   if (timeout == std::chrono::nanoseconds(0)) {
      do {

         if (!scheduler_active && task_queue.empty())
            return true;
         std::this_thread::sleep_for(std::chrono::nanoseconds(100));
      } while (1);

   }
   else {
      auto start = std::chrono::steady_clock::now();

      do {

         if (!scheduler_active && task_queue.empty())
            return true;
         std::this_thread::sleep_for(std::chrono::nanoseconds(100));

      } while (std::chrono::nanoseconds(std::chrono::steady_clock::now() - start) < timeout);

      return false;
   }
}

void ThreadPond::queue(std::function<void(void *)> func, void * arg) {

   task * new_task = (task *)malloc(sizeof(task));
   bzero(new_task,sizeof(task));

   new_task->func = func;
   new_task->arg  = arg;

   task_queue.push(new_task);
   pthread_kill(scheduler,__RHIZAR16_THREAD_SIGNAL__);
}

#endif

}
