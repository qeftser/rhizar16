
#ifndef __RHIZAR16_NUM_STRING__

#define __RHIZAR16_NUM_STRING__
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <functional>
#include <unordered_set>
#include "uniform_rand.h"

namespace Rhizar16 {

template<typename T, unsigned N>
struct NumString {

   const uint32_t length = N;
   const uint32_t bytes  = N * sizeof(T);
   T values[N];

   static void single_point_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children);
   static void two_point_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children);
   static void uniform_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children);
   static void shuffle_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children);
   static void precedence_preservative_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children);
   static void ordered_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children);
   static void partially_matched_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children);

   static std::function<void(NumString<T,N> *)> noise(std::function<T()> generator, double probability);
   static std::function<void(NumString<T,N> *)> interchange(double probability);

   static size_t encode(NumString<T,N> * obj, uint8_t * buf);
   static size_t decode(NumString<T,N> * obj, uint8_t * buf);
};

template<typename T, unsigned N>
void NumString<T,N>::single_point_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children) {
   static UniformRand rnd = UniformRand();

   uint32_t crossover_point = rnd.random() % N;
   uint32_t crossover_bytes = sizeof(T) * crossover_point;
   uint32_t crossover_rever = sizeof(T) * (N - crossover_point);

   memcpy((&children[0]->values),(&parents[0]->values),crossover_bytes);
   memcpy((&children[1]->values[crossover_point]),(&parents[0]->values[crossover_point]),crossover_rever);
   memcpy((&children[1]->values),(&parents[1]->values),crossover_bytes);
   memcpy((&children[0]->values[crossover_point]),(&parents[1]->values[crossover_point]),crossover_rever);

}

template<typename T, unsigned N>
void NumString<T,N>::two_point_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children) {
   static UniformRand rnd = UniformRand();

   uint32_t crossover_one = rnd.random() % N;
   uint32_t crossover_two = rnd.random() % (N + 1);

   if (crossover_one > crossover_two) {
      crossover_one ^= crossover_two;
      crossover_two ^= crossover_one;
      crossover_one ^= crossover_two;
   }

   uint32_t before_bytes = crossover_one * sizeof(T);
   uint32_t inside_bytes = (crossover_two - crossover_one) * sizeof(T);
   uint32_t after_bytes  = (N - crossover_two) * sizeof(T);

   memcpy((&children[0]->values),(&parents[0]->values),before_bytes);
   memcpy((&children[0]->values[crossover_one]),(&parents[1]->values[crossover_one]),inside_bytes);
   memcpy((&children[0]->values[crossover_two]),(&parents[0]->values[crossover_two]),after_bytes);
   memcpy((&children[1]->values),(&parents[1]->values),before_bytes);
   memcpy((&children[1]->values[crossover_one]),(&parents[0]->values[crossover_one]),inside_bytes);
   memcpy((&children[1]->values[crossover_two]),(&parents[1]->values[crossover_two]),after_bytes);
}

template<typename T, unsigned N>
void NumString<T,N>::uniform_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children) {
   static UniformRand rnd = UniformRand();
   uint8_t mask[N];

   for (uint32_t i = 0; i < N; ++i)
      mask[i] = rnd.random() % 2;

   for (uint32_t i = 0; i < N; ++i)
      children[0]->values[i] = (mask[i] ? parents[0]->values[i] : parents[1]->values[i]);
}

template<typename T, unsigned N>
void NumString<T,N>::shuffle_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children) {
   static UniformRand rnd = UniformRand();

   uint16_t mapping[N];

   for (uint32_t i = 0; i < N; ++i)
      mapping[i] = i;

   for (uint32_t i = 0; i < N; ++i) {
      uint32_t swappos = rnd.random() % N;
      if (swappos == i) continue;
      mapping[i] ^= mapping[swappos];
      mapping[swappos] ^= mapping[i];
      mapping[i] ^= mapping[swappos];
   }

   uint32_t crosspoint = rnd.random() % (N + 1);

   memset(children[0]->values,0x00,children[0]->bytes);
   memset(children[1]->values,0x00,children[1]->bytes);

   for (uint32_t i = 0; i < crosspoint; ++i) {
      children[0]->values[mapping[i]] = parents[0]->values[mapping[i]];
      children[1]->values[mapping[i]] = parents[1]->values[mapping[i]];
   }

   for (uint32_t i = crosspoint; i < N; ++i) {
      children[1]->values[mapping[i]] = parents[0]->values[mapping[i]];
      children[0]->values[mapping[i]] = parents[1]->values[mapping[i]];
   }
}

template<typename T, unsigned N>
void NumString<T,N>::precedence_preservative_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children) {
   static std::unordered_set<T> seen;
   seen.clear();

   uint32_t p0_head = 0;
   uint32_t p1_head = 0;

   for (uint32_t i = 0; i < N - 1; i += 2) {

      while (seen.count(parents[0]->values[p0_head])) p0_head += 1;
      children[0]->values[i+0] = parents[0]->values[p0_head];
      seen.insert(parents[0]->values[p0_head]);
      p0_head += 1;

      while (seen.count(parents[1]->values[p1_head])) p1_head += 1;
      children[0]->values[i+1] = parents[1]->values[p1_head];
      seen.insert(parents[1]->values[p1_head]);
      p1_head += 1;

   }

   if (N % 2) {

      while (seen.count(parents[0]->values[p0_head])) p0_head += 1;
      children[0]->values[N - 1] = parents[0]->values[p0_head];

   }

}

/* Note: due to the way this function is written (and indirectly what it is intended for) it
 * does not function correctly with duplicate values and has a chance to generate strings
 * that do not align with the documented behavior. */
template<typename T, unsigned N>
void NumString<T,N>::ordered_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children) {
   static UniformRand rnd = UniformRand();
   static std::unordered_set<T> seen0;
   static std::unordered_set<T> seen1;

   uint32_t crossover_one = rnd.random() % (N + 1);
   uint32_t crossover_two = rnd.random() % (N + 1);

   if (crossover_one > crossover_two) {
      crossover_one ^= crossover_two;
      crossover_two ^= crossover_one;
      crossover_one ^= crossover_two;
   }

   uint32_t low_bytes  = crossover_one * sizeof(T);
   uint32_t high_bytes = (N - crossover_two) * sizeof(T);

   memcpy((&children[0]->values),(&parents[0]->values),low_bytes);
   memcpy((&children[0]->values[crossover_two]),(&parents[0]->values[crossover_two]),high_bytes);
   memcpy((&children[1]->values),(&parents[1]->values),low_bytes);
   memcpy((&children[1]->values[crossover_two]),(&parents[1]->values[crossover_two]),high_bytes);

   seen0.clear();
   seen1.clear();
   for (uint32_t i = crossover_one; i < crossover_two; ++i) {
      seen0.insert(parents[0]->values[i]);
      seen1.insert(parents[1]->values[i]);
   }

   uint32_t pos0 = crossover_one;
   uint32_t pos1 = crossover_one;
   for (uint32_t i = 0; i < N; ++i) {
      if (seen0.count(parents[1]->values[i]))
         children[0]->values[pos0++] = parents[1]->values[i];
      if (seen1.count(parents[0]->values[i]))
         children[1]->values[pos1++] = parents[0]->values[i];
   }
}

template<typename T, unsigned N>
void NumString<T,N>::partially_matched_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children) {
   static UniformRand rnd = UniformRand();
   static std::unordered_set<T> seen0;
   static std::unordered_set<T> seen1;

   uint32_t crossover_one = rnd.random() % (N + 1);
   uint32_t crossover_two = rnd.random() % (N + 1);

   if (crossover_one > crossover_two) {
      crossover_one ^= crossover_two;
      crossover_two ^= crossover_one;
      crossover_one ^= crossover_two;
   }

   uint32_t before_bytes = crossover_one * sizeof(T);
   uint32_t inside_bytes = (crossover_two - crossover_one) * sizeof(T);
   uint32_t after_bytes  = (N - crossover_two) * sizeof(T);

   memcpy((&children[0]->values),(&parents[0]->values),before_bytes);
   memcpy((&children[0]->values[crossover_one]),(&parents[1]->values[crossover_one]),inside_bytes);
   memcpy((&children[0]->values[crossover_two]),(&parents[0]->values[crossover_two]),after_bytes);
   memcpy((&children[1]->values),(&parents[1]->values),before_bytes);
   memcpy((&children[1]->values[crossover_one]),(&parents[0]->values[crossover_one]),inside_bytes);
   memcpy((&children[1]->values[crossover_two]),(&parents[1]->values[crossover_two]),after_bytes);

   seen0.clear();
   seen1.clear();
   for (uint32_t i = crossover_one; i < crossover_two; ++i) {
      seen0.insert(parents[0]->values[i]);
      seen1.insert(parents[1]->values[i]);
   }

   uint32_t repl_pos0 = crossover_one;
   uint32_t repl_pos1 = crossover_one;

   while (seen1.count(parents[0]->values[repl_pos0])) repl_pos0 += 1;
   while (seen0.count(parents[1]->values[repl_pos1])) repl_pos1 += 1;

   for (uint32_t i = 0; i < N - (crossover_two - crossover_one); ++i) {
      uint32_t internal_pos = (i + crossover_two) % N;

      if (seen1.count(parents[0]->values[internal_pos])) {
         children[0]->values[internal_pos] = parents[0]->values[repl_pos0++];
         while (seen1.count(parents[0]->values[repl_pos0])) repl_pos0 += 1;
      }

      if (seen0.count(parents[1]->values[internal_pos])) {
         children[1]->values[internal_pos] = parents[1]->values[repl_pos1++];
         while (seen0.count(parents[1]->values[repl_pos1])) repl_pos1 += 1;
      }
   }
}

template<typename T, unsigned N>
std::function<void(NumString<T,N> *)> NumString<T,N>::noise(std::function<T()> generator, double probability) {

   assert(probability <= 1.0 && probability >= 0.0 
         && "NumString: probability for function 'noise' must be in the range [0.0, 1.0]");

   uint64_t compr = (double)ULLONG_MAX * probability;

   return [generator,compr](NumString<T,N> * val){
      static UniformRand rnd = UniformRand();

      unsigned toapply = 0;
      while (toapply < N && rnd.random() < compr) toapply += 1;

      for (uint32_t i = 0; i < toapply; ++i)
         val->values[rnd.random() % N] += generator();
   };
}

template<typename T, unsigned N>
std::function<void(NumString<T,N> *)> NumString<T,N>::interchange(double probability) {

   assert(probability <= 1.0 && probability >= 0.0 
         && "NumString: probability for function 'interchange' must be in the range [0.0, 1.0]");

   uint64_t compr = (double)ULLONG_MAX * probability;

   return [compr](NumString<T,N> * val){
      static UniformRand rnd = UniformRand();
      
      unsigned toswap = 0;
      while (toswap < N && rnd.random() < compr) toswap += 1;

      for (uint32_t i = 0; i < toswap; ++i) {
         unsigned swap0 = rnd.random() % N;
         unsigned swap1 = rnd.random() % N;
         if (swap0 == swap1) continue;

         val->values[swap0] ^= val->values[swap1];
         val->values[swap1] ^= val->values[swap0];
         val->values[swap0] ^= val->values[swap1];
      }
   };
}

template<typename T, unsigned N>
size_t NumString<T,N>::encode(NumString<T,N> * obj, uint8_t * buf) {

   size_t len = N * sizeof(T);

   if (buf)
      memcpy(buf,obj->values,len);

   return len;
}

template<typename T, unsigned N>
size_t NumString<T,N>::decode(NumString<T,N> * obj, uint8_t * buf) {

   size_t len = N * sizeof(T);

   if (buf)
      memcpy(obj->values,buf,len);

   return len;
}

};

#endif
