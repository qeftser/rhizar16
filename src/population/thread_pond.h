
#ifndef __RHIZAR16_THREAD_POND__

#define __RHIZAR16_THREAD_POND__
#include <stdint.h>
#include <thread>
#include <functional>
#include "concurrent_queue.h"

/* a thread pool. Will be windows/unix cross 
 * platform, which is the cause of the weird
 * name and the class-based implimentation */

#ifdef _WIN32

#include <condition_variable>
#include <windows.h>
#include <processthreadsapi.h>
#include <winnt.h>
#include <malloc.h>
#include <synchapi.h>
#include <handleapi.h>

#elif defined(__unix__)

/* the signals we will send to our threads
 * to notify them of special events.     */
#ifndef __RHIZAR16_THREAD_SIGNAL__
   #define __RHIZAR16_THREAD_SIGNAL__    (SIGRTMIN+16)
#endif
#ifndef __RHIZAR16_THREAD_TERMINATE__
   #define __RHIZAR16_THREAD_TERMINATE__ (SIGRTMIN+17)
#endif

#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <limits.h>
#include <mutex>
#include <queue>

#endif

namespace Rhizar16 {

class ThreadPond {
private:

   const uint32_t thread_count;

#ifdef _WIN32

   struct task {
      std::function<void(void *)> func;
      void * arg;
   };

   struct worker_init {
      std::condition_variable   * notify;
      std::mutex                * lock;
      LONG                      * ready_count;
      ConcurrentQueue<task *>   * tasks;
      volatile bool             * live;
      LPSYNCHRONIZATION_BARRIER   barrier;
   };

   std::condition_variable notify;
   std::mutex lock;
   std::thread * threads;
   worker_init * runtime;
   LONG * ready_count;
   ConcurrentQueue<task *> tasks;
   volatile bool live;

   static void worker_callback(worker_init * arg);


#elif defined(__unix__)

   struct task {
      std::function<void(void *)> func;
      void * arg;
   };

   struct worker_init {
      int                 notify_ready;
      task             ** worker_task;
      pthread_barrier_t * barrier;
      pthread_cond_t    * notify_work;
      pthread_mutex_t   * lock_work;
   };

   struct scheduler_init {
      pthread_barrier_t       * barrier;
      std::atomic<int>        * active;
      uint32_t                  thread_count;
      int                     * read_end;
      task                   ** task_ptr;
      pthread_t               * threads;
      ConcurrentQueue<task *> * task_queue;
      pthread_cond_t          * triggers;
      pthread_mutex_t         * mutexes;
   };

   pthread_t * workers;
   pthread_t scheduler;
   task ** task_ptr;
   int * read_end;
   int * write_end;
   pthread_cond_t * triggers;
   pthread_mutex_t * mutexes;
   worker_init * worker_data;
   scheduler_init scheduler_data;
   std::atomic<int> scheduler_active;

   static void thread_callback(int sig);
   static void termination_callback(int sig);

   static void * worker_runtime(void * init);
   static void * scheduler_runtime(void * init);


   ConcurrentQueue<task *> task_queue;

#endif

public:

   /* will initialize with the expected best number of hardware threads
    * if it can find that value using hardware_concurrency. Otherwise
    * will default to 1. User can also pass the number of threads they
    * want to use.                                                     */
   ThreadPond(uint32_t thread_count = std::thread::hardware_concurrency());

   ~ThreadPond();

   /* wait until all queued tasks have finished, or
    * until the passed timeout is reached. Will block 
    * forever if a timeout of zero (default) is passed.
    *
    * Returns true if there are no remaining tasks         */
   bool wait(std::chrono::nanoseconds timeout =
             std::chrono::nanoseconds::zero());

   /* add a job to the thread pond */
   void queue(std::function<void(void *)>, void * arg);

};

}

#endif 
