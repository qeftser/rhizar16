
#include "concurrent_queue.h"
#include <thread>
#include <stdio.h>

namespace Rhizar16 {

namespace TestConcurrentQueue {

int initialization() {
   ConcurrentQueue<int> c;

   return 1;
}

int empty_0() {
   ConcurrentQueue<int> c;

   int retval = 1;

   if (c.empty() != true)
      retval = 0;

   return retval;
}

int push_0() {
   ConcurrentQueue<int> c;

   c.push(1);
   c.push(2);
   c.push(3);

   return 1;
}

int empty_1() {
   ConcurrentQueue<int> c;

   c.push(1);

   int retval = 1;

   if (c.empty() == true)
      retval = 0;

   return retval;
}

int pop_0() {
   ConcurrentQueue<int> c;

   c.push(0xffffffff);

   int retval = 1;

   if (c.pop() != 0xffffffff)
      retval = 0;

   return retval;
}

int push_1() {
   ConcurrentQueue<int> c;

   c.push(1);
   c.push(2);
   c.push(3);

   int retval = 1;

   if (c.pop() != 1)
      retval = 0;
   if (c.pop() != 2)
      retval = 0;
   if (c.pop() != 3)
      retval = 0;

   c.push(3);
   c.push(1);
   c.push(2);

   if (c.pop() != 3)
      retval = 0;
   if (c.pop() != 1)
      retval = 0;
   if (c.pop() != 2)
      retval = 0;

   return retval;
}

int empty_2() {
   ConcurrentQueue<int> c;

   c.push(1);
   c.pop();

   int retval = 1;

   if (c.empty() != true)
      retval = 0;

   return retval;
}

void test_concurrent_push_n_order(ConcurrentQueue<int> * q, int count, int * go) {
   while (!(*go)) std::this_thread::yield();
   for (int i = 1; i <= count; ++i)
      q->push(i);
}

int push_2() {
   ConcurrentQueue<int> c;
   int count = 10;

   int threads = std::thread::hardware_concurrency();
   if (threads == 0)
      threads = 4;

   std::thread pushers[threads];

   int sum = 0;
   int go = 0;

   for (int i = 0; i < threads; ++i) {
      pushers[i] = std::thread(test_concurrent_push_n_order,&c,count,&go);
   }

   go = 1;

   for (int i = 0; i < threads; ++i) {
      if (pushers[i].joinable())
         pushers[i].join();
   }

   int retval = 1;

   while (!c.empty())
      sum += c.pop();

   if (sum != ((count * (count + 1)) / 2) * threads)
      retval = 0;

   return retval;
}

void test_concurrent_pop_n_order(ConcurrentQueue<int> * q,
                                 int count, int * go, int * sum) {
   *sum = 0;
   while (!(*go)) std::this_thread::yield();
   for (int i = 1; i <= count; ++i)
      *sum += q->pop();
}

int pop_1() {
   ConcurrentQueue<int> c;
   int count = 10;

   int threads = std::thread::hardware_concurrency();
   if (threads == 0)
      threads = 4;

   std::thread paupers[threads];

   int sum[threads];
   int go = 0;
   int total_sum;

   for (int i = 0; i < threads; ++i) {
      for (int i = 1; i <= count; ++i)
         c.push(i);
   }

   for (int i = 0; i < threads; ++i) {
      paupers[i] = std::thread(test_concurrent_pop_n_order,&c,count,&go,&sum[i]);
   }

   go = 1;

   for (int i = 0; i < threads; ++i) {
      if (paupers[i].joinable())
         paupers[i].join();
   }

   int retval = 1;

   total_sum = 0;
   for (int i = 0; i < threads; ++i)
      total_sum += sum[i];

   if (total_sum != ((count * (count + 1)) / 2) * threads)
      retval = 0;

   return retval;
}

int push_3() {
   ConcurrentQueue<int> c;
   int count = 10000;

   int threads = std::thread::hardware_concurrency();
   if (threads == 0)
      threads = 4;

   std::thread pushers[threads];

   int sum = 0;
   int go = 0;

   for (int i = 0; i < threads; ++i) {
      pushers[i] = std::thread(test_concurrent_push_n_order,&c,count,&go);
   }

   go = 1;

   for (int i = 0; i < threads; ++i) {
      if (pushers[i].joinable())
         pushers[i].join();
   }

   int retval = 1;

   while (!c.empty())
      sum += c.pop();

   if (sum != ((count * (count + 1)) / 2) * threads)
      retval = 0;

   return retval;
}

int pop_2() {
   ConcurrentQueue<int> c;
   int count = 10000;

   int threads = std::thread::hardware_concurrency();
   if (threads == 0)
      threads = 4;

   std::thread paupers[threads];

   int sum[threads];
   int go = 0;
   int total_sum;

   for (int i = 0; i < threads; ++i) {
      for (int i = 1; i <= count; ++i)
         c.push(i);
   }

   for (int i = 0; i < threads; ++i) {
      paupers[i] = std::thread(test_concurrent_pop_n_order,&c,count,&go,&sum[i]);
   }

   go = 1;

   for (int i = 0; i < threads; ++i) {
      if (paupers[i].joinable())
         paupers[i].join();
   }

   int retval = 1;

   total_sum = 0;
   for (int i = 0; i < threads; ++i)
      total_sum += sum[i];

   if (total_sum != ((count * (count + 1)) / 2) * threads)
      retval = 0;

   return retval;
}

int push_4() {
   ConcurrentQueue<int> c;
   int count = 1000000;

   int threads = std::thread::hardware_concurrency();
   if (threads == 0)
      threads = 4;

   std::thread pushers[threads];

   int sum = 0;
   int go = 0;

   for (int i = 0; i < threads; ++i) {
      pushers[i] = std::thread(test_concurrent_push_n_order,&c,count,&go);
   }

   go = 1;

   for (int i = 0; i < threads; ++i) {
      if (pushers[i].joinable())
         pushers[i].join();
   }

   int retval = 1;

   while (!c.empty())
      sum += c.pop();

   if (sum != ((count * (count + 1)) / 2) * threads)
      retval = 0;

   return retval;
}

int pop_3() {
   ConcurrentQueue<int> c;
   int count = 1000000;

   int threads = std::thread::hardware_concurrency();
   if (threads == 0)
      threads = 4;

   std::thread paupers[threads];

   int sum[threads];
   int go = 0;
   int total_sum;

   for (int i = 0; i < threads; ++i) {
      for (int i = 1; i <= count; ++i)
         c.push(i);
   }

   for (int i = 0; i < threads; ++i) {
      paupers[i] = std::thread(test_concurrent_pop_n_order,&c,count,&go,&sum[i]);
   }

   go = 1;

   for (int i = 0; i < threads; ++i) {
      if (paupers[i].joinable())
         paupers[i].join();
   }

   int retval = 1;

   total_sum = 0;
   for (int i = 0; i < threads; ++i)
      total_sum += sum[i];

   if (total_sum != ((count * (count + 1)) / 2) * threads)
      retval = 0;

   return retval;
}

void test_concurrent_push_until_n(ConcurrentQueue<int> * q,
                                  int limit, std::atomic<int> * push_sum,
                                  int * go) {
   while (!(*go)) std::this_thread::yield();
   while (push_sum->load() < limit) {
      push_sum->fetch_add(1);
      q->push(1);
   }
}

void test_concurrent_pop_until_n(ConcurrentQueue<int> * q,
                                 int limit, std::atomic<int> * pop_sum,
                                 int * sum, int * go) {
   *sum = 0;
   while (!(*go)) std::this_thread::yield();
   while (pop_sum->load() < limit) {
      if (!q->empty()) {
         pop_sum->fetch_add(1);
         *sum += q->pop();
         //printf("%016lx / %016lx\n",pop_sum->load(),limit);
      }
   }
}

int usage() {
   ConcurrentQueue<int> c;

   int goal = 1000000;
   int sum = 0;

   int threads = std::thread::hardware_concurrency() / 2;
   if (threads == 0)
      threads = 2;

   std::atomic<int> push_sum;
   std::atomic<int> pop_sum;

   push_sum.store(0);
   pop_sum.store(0);

   std::thread pushers[threads];
   std::thread paupers[threads];
   int sums[threads];

   int go = 0;


   for (int i = 0; i < threads; ++i) {
      pushers[i] = std::thread(test_concurrent_push_until_n,&c,goal,&push_sum,&go);
   }

   for (int i = 0; i < threads; ++i) {
      paupers[i] = std::thread(test_concurrent_pop_until_n,&c,goal,&pop_sum,&sums[i],&go);
   }

   go = 1;
   


   for (int i = 0; i < threads; ++i) {
      if (pushers[i].joinable())
         pushers[i].join();
   }

   for (int i = 0; i < threads; ++i) {
      if (paupers[i].joinable())
         paupers[i].join();
   }

   for (int i = 0; i < threads; ++i)
      sum += sums[i];

   int retval = 1;

   if (sum < goal)
      retval = 0;

   return retval;
}

}

}
