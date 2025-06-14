
#include "thread_pond_test.h"
#include <thread>
#include <chrono>
#include <stdio.h>

namespace Rhizar16 {

namespace TestThreadPond {

int initialization_0() {
   ThreadPond t;

   return 1;
}

int initialization_1() {
   ThreadPond t(0);

   return 1;
}

int initialization_2() {
   ThreadPond t[10];

   return 1;
}

int wait_0() {
   ThreadPond t;

   int retval = 1;

   if (t.wait() != true)
      retval = 0;

   return retval;
}

void test_thread_pond_dummy_never_end(void * arg) {
   (void)arg;
   while (1) std::this_thread::yield();
}

int wait_1() {
#ifdef _WIN32
   return 2;
#endif
   ThreadPond t;

   t.queue(test_thread_pond_dummy_never_end,NULL);

   int retval = 1;

   if (t.wait(std::chrono::milliseconds(3)) != false)
      retval = 0;

   return retval;
}

void test_thread_pond_dummy_calculate_n_factorial(void * arg) {
   uint64_t * res = (uint64_t *)arg;
   uint64_t desired = *res + 1;
   *res = 0;
   *res = 1;
   while (--desired)
      *res *= desired;
}

int queue_0() {
   ThreadPond t;

   int retval = 1;

   uint64_t factof = 20;

   t.queue(test_thread_pond_dummy_calculate_n_factorial,&factof);

   t.wait(std::chrono::milliseconds(100));

   if (factof != 2432902008176640000)
      retval = 0;

   return retval;
}

int queue_1() {
   ThreadPond t;

   int num_tasks = 10;

   int retval = 1;

   uint64_t * factof = new uint64_t[num_tasks];
   for (int i = 0; i < num_tasks; ++i)
      factof[i] = 20;

   for (int i = 0; i < num_tasks; ++i)
      t.queue(test_thread_pond_dummy_calculate_n_factorial,&factof[i]);

   t.wait(std::chrono::milliseconds(100));

   for (int i = 0; i < num_tasks; ++i)
      if (factof[i] != 2432902008176640000)
         retval = 0;

   delete[] factof;
   return retval;
}

int queue_2() {
   ThreadPond t;

   int num_tasks = 1000;

   int retval = 1;

   uint64_t * factof = new uint64_t[num_tasks];
   for (int i = 0; i < num_tasks; ++i)
      factof[i] = 20;

   for (int i = 0; i < num_tasks; ++i)
      t.queue(test_thread_pond_dummy_calculate_n_factorial,&factof[i]);

   t.wait();

   for (int i = 0; i < num_tasks; ++i)
      if (factof[i] != 2432902008176640000)
         retval = 0;

   delete[] factof;
   return retval;
}

int queue_3() {
   ThreadPond t;

   int num_tasks = 10000;

   int retval = 1;

   uint64_t * factof = new uint64_t[num_tasks];
   for (int i = 0; i < num_tasks; ++i)
      factof[i] = 20;

   for (int i = 0; i < num_tasks; ++i)
      t.queue(test_thread_pond_dummy_calculate_n_factorial,&factof[i]);

   t.wait();

   for (int i = 0; i < num_tasks; ++i)
      if (factof[i] != 2432902008176640000)
         retval = 0;

   delete[] factof;
   return retval;
}

int queue_4() {
   ThreadPond t;

   int num_tasks = 100000;

   int retval = 1;

   uint64_t * factof = new uint64_t[num_tasks];
   for (int i = 0; i < num_tasks; ++i)
      factof[i] = 20;

   for (int i = 0; i < num_tasks; ++i)
      t.queue(test_thread_pond_dummy_calculate_n_factorial,&factof[i]);

   t.wait();

   for (int i = 0; i < num_tasks; ++i)
      if (factof[i] != 2432902008176640000)
         retval = 0;

   delete[] factof;
   return retval;
}

int queue_5() {
   int num_tasks = 10000;
   uint64_t * factof = new uint64_t[num_tasks];
   for (int i = 0; i < 100; ++i) {
      ThreadPond t;

      for (int i = 0; i < num_tasks; ++i)
         factof[i] = 20;

      for (int i = 0; i < num_tasks; ++i)
         t.queue(test_thread_pond_dummy_calculate_n_factorial,&factof[i]);

   }
   delete[] factof;

   return 1;
}

int queue_6() {
   int retval = 1;
   int num_tasks = 1000;
   uint64_t * factof = new uint64_t[num_tasks];
   for (int i = 0; i < 1000; ++i) {
      ThreadPond t;

      for (int i = 0; i < num_tasks; ++i)
         factof[i] = 20;

      for (int i = 0; i < num_tasks; ++i) {
         t.queue(test_thread_pond_dummy_calculate_n_factorial,&factof[i]);
      }

      t.wait(std::chrono::milliseconds(1000));

      for (int i = 0; i < num_tasks; ++i)
         if (factof[i] != 2432902008176640000) {
            (exit(1));
            retval = 0;
         }

   }
   delete[] factof;

   return retval;
}

}

}
