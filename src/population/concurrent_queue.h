
#ifndef __RHIZAR16_ATOMIC_QUEUE__

#define __RHIZAR16_ATOMIC_QUEUE__
#include <stdlib.h>
#include <stdio.h>
#include <atomic>
#include <mutex>

/* after a little bit of work on the implimentation of the 
 * unix version of the thread pond I felt things would be
 * much eaiser if an atomic queue was used as opposed to
 * a standard one with a mutex. So here is the implimentation. */

/* SOURCE
 * Michael, Maged; Scott, Michael (1996). 
 * Simple, Fast, and Practical Non-Blocking and Blocking Concurrent Queue Algorithms.
 * Proc. 15th Annual ACM Symp. on Principles of Distributed Computing (PODC). pp. 267–275.
 * doi:10.1145/248052.248106. ISBN 0-89791-800-2. 
 */

/* Note
 * Because some tricks are used in the construction of the nonblocking queue, it
 * is not perferrable to use it in cases where our pointers occupy less than
 * 33 or more than 56 bits. To deal with this, a lock based queue will be added
 * (from the same source), and the choice of which to use will be determined
 * at compile time by cmake.
 *
 * If the user does not wish to take their chances with the atomic queue, they
 * can define the following macro below this comment to force usage of the
 * lock based queue:
 *
 * __RHIZAR16_NO_UNSAFE_ATOMIC_QUEUE__
 *
 */

#define __RHIZAR16_NO_UNSAFE_ATOMIC_QUEUE__

namespace Rhizar16 {

#ifndef __RHIZAR16_NO_UNSAFE_ATOMIC_QUEUE__

#warning race conditions exist here, consider changing your decision

template<typename T>
class ConcurrentQueue {
private:

   union aba_ptr;

   struct queue_node {
      T data;
      std::atomic<aba_ptr> next;
   };

   union aba_ptr {
      struct queue_node * ptr;
      uint64_t count;
   };

   std::atomic<aba_ptr> head;
   std::atomic<aba_ptr> tail;

   /* one can note that on most all machines, the pointer type
    * takes up 64 bits but only the lower 48 or 56 are used.
    *
    * This can be taken advantage of to solve the aba problem
    * by including a pointer count in the upper byte of a
    * pointer. This can be disabled by defining the macro
    * __RHIZAR16_NO_UNSAFE_ATOMIC_QUEUE__
    */
   inline aba_ptr      aba_inc(aba_ptr ptr) const {
      uint8_t count = (ptr.count >> 56);
      count += 1;
      ptr.count &= 0xffffffffffffff;
      ptr.count |= (((uint64_t)count) << 56);
      return ptr;
   }

   inline queue_node * aba_ref(aba_ptr ptr) const {
      return (queue_node *)(ptr.count&0xffffffffffff);
   }

public:

   ConcurrentQueue() {
      queue_node * new_node = (queue_node *)malloc(sizeof(queue_node));
      new_node->next.store(aba_ptr{NULL});
      head = tail = aba_ptr{new_node};
   }

   ~ConcurrentQueue() {
      queue_node * next, * curr = aba_ref(head);
      while (curr != NULL) {

         next = aba_ref(curr->next);
         free(curr);
         curr = next;
      
      }
   }

   /* Returns true if the queue is empty */
   bool empty() {

      aba_ptr local_head, local_next;
      do {
         local_head = head;
         local_next = aba_ref(local_head)->next;
         if (local_head.ptr == head.load().ptr) {
            if (local_next.ptr == NULL)
               return true;
            else
               return false;
         }
      } while (1);

   }

   /* Add the given element to the end of the queue */
   void push(T element) {

      queue_node * new_node = (queue_node *)malloc(sizeof(queue_node));
      new_node->next.store(aba_ptr{NULL});
      new_node->data = element;

      aba_ptr local_tail, local_next;

      for ( ; ; ) {

         local_tail = tail.load(std::memory_order_acquire);
         local_next = aba_ref(local_tail)->next.load(std::memory_order_acquire);

         if (local_tail.ptr == tail.load(std::memory_order_acquire).ptr) {
            if (local_next.ptr == NULL) {
               if (aba_ref(local_tail)->next.compare_exchange_strong(local_next,aba_ptr{new_node}))
                  break;
            }
            else
               tail.compare_exchange_strong(local_tail,aba_inc(local_next));
         }
      }
      tail.compare_exchange_strong(local_tail,aba_ptr{new_node});
   }

   /* Remove the element at the head of the queue */
   T pop() {
      aba_ptr local_head, local_tail, local_next;
      T retval;

      for ( ; ; ) {

         local_head = head.load(std::memory_order_acquire);
         local_tail = tail.load(std::memory_order_acquire);;
         local_next = aba_ref(local_head)->next.load(std::memory_order_acquire);

         if (local_head.ptr == head.load(std::memory_order_acquire).ptr) {
            if (local_head.ptr == local_tail.ptr) {
               if (local_next.ptr == NULL)
                  return (T)(0);
               tail.compare_exchange_strong(local_tail,aba_inc(local_next));
            }
            else {
               retval = aba_ref(local_next)->data;
               if (head.compare_exchange_strong(local_head,aba_inc(local_next)))
                  break;
            }
         }
      }

      free(aba_ref(local_head));
      return retval;
   }

};

#else

template<typename T>
class ConcurrentQueue {
private:

   struct queue_node {
      struct queue_node * next;
      T data;
   };

   std::mutex h_lock = std::mutex();
   std::mutex t_lock = std::mutex();

   size_t items;

   struct queue_node * head;
   struct queue_node * tail;

public:

   ConcurrentQueue();
   ~ConcurrentQueue();

   /* Returns true if the queue is empty */
   bool empty();

   /* Add the given element to the end of the queue */
   void push(T element);

   /* Remove the element at the head of the queue */
   T pop();

};

template<typename T>
ConcurrentQueue<T>::ConcurrentQueue() {

   queue_node * new_node = (queue_node *)malloc(sizeof(queue_node));
   new_node->next = NULL;

   head = tail = new_node;
}

template<typename T>
ConcurrentQueue<T>::~ConcurrentQueue() {

   queue_node * next, * curr = head;

   while (curr) {
      next = curr->next;
      free(curr);
      curr = next;
   }
}

template<typename T>
bool ConcurrentQueue<T>::empty() {
   bool retval;
   h_lock.lock();

   if (head->next == NULL)
      retval = true;
   else
      retval = false;

   h_lock.unlock();
   return retval;
}

template<typename T>
void ConcurrentQueue<T>::push(T element) {
   queue_node * new_node = (queue_node *)malloc(sizeof(queue_node));
   new_node->next = NULL;
   new_node->data = element;

   t_lock.lock();
   tail->next = new_node;
   tail = new_node;
   t_lock.unlock();
}

template<typename T>
T ConcurrentQueue<T>::pop() {
   T retval;
   h_lock.lock();
   queue_node * node = head;
   queue_node * new_head = node->next;
   if (new_head == NULL) {
      h_lock.unlock();
      return (T)(0);
   }
   retval = new_head->data;
   head = new_head;
   h_lock.unlock();
   free(node);
   return retval;
}

#endif

}

#endif
