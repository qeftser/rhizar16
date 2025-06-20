
#ifndef __RHIZAR16_BIT_STRING__

#define __RHIZAR16_BIT_STRING__

#define __RHIZAR16_BIT_PER_BYTE__ 8

#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <functional>
#include "uniform_rand.h"

#ifdef _WIN32
typedef unsigned  int  uint;
typedef unsigned long long ulong;
#endif

namespace Rhizar16 {

/* A vector of bits to be manipulated individually */
template<unsigned N>
struct BitString {

   /* =========== Struct Values =========== */
   const uint length = (N % 64 == 0 ? N / 64 : (N + 64) / 64);
   const uint bits = N;
   uint64_t values[(N % 64 == 0 ? N / 64 : (N + 64) / 64)];
   /* =========== Struct Values =========== */

   /* construct a bit vector of length n */
   BitString();

   /* destroy the bit string */
   ~BitString();

   /* Compute the hamming distance between two bit strings */
   static int hamming_distance(const BitString<N> & bs1, const BitString<N> & bs2);

   /* fill the given bit string with random values
    * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    * Note: this is not going to be thread-safe   
    * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
   void randomize();

   static void single_point_crossover(BitString<N> ** const parents, BitString<N> ** children);
   static void two_point_crossover(BitString<N> ** const parents, BitString<N> ** children);
   static void uniform_crossover(BitString<N> ** const parents, BitString<N> ** children);
   static void three_parent_crossover(BitString<N> ** const parents, BitString<N> ** children);
   static void shuffle_crossover(BitString<N> ** const parents, BitString<N> ** children);

   static std::function<void(BitString<N> *)> flip(double probability);
   static std::function<void(BitString<N> *)> interchange(double probability);

   static size_t encode(BitString<N> * obj, uint8_t * buf);
   static size_t decode(BitString<N> * obj, uint8_t * buf);
};

template<unsigned N>
BitString<N>::BitString() {
}

template<unsigned N>
BitString<N>::~BitString() {
}


template<unsigned N>
void BitString<N>::randomize() {
   static UniformRand rnd = UniformRand();

   for (uint i = 0; i < length; ++i)
      values[i] = rnd.random();
}

template<unsigned N>
int BitString<N>::hamming_distance(const BitString<N> & bs1, const BitString<N> & bs2) {
   int retval = 0;

   /* use the builtin popcount intrinsic if it is avaliable */
#if (defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)) && __has_builtin(__builtin_popcountll)

   for (uint i = 0; i < bs1.length; ++i)
      retval += __builtin_popcountll(bs1.values[i] ^ bs2.values[i]);

#else

   for (int i = 0; i < bs1.length; ++i) {
      int nv = bs1.values[i] ^ bs2.values[i];

      for (int j = 0; j < 16; ++j) {
         switch (nv) {
            case 0x0:
               break;
            case 0x1:
            case 0x2:
            case 0x4:
            case 0x8:
               nv += 1;
               break;
            case 0x3:
            case 0x5:
            case 0x9:
            case 0x6:
            case 0xa:
            case 0xc:
               nv += 2;
            case 0x7:
            case 0xb:
            case 0xe:
            case 0xd:
               nv += 3;
            case 0xf:
               nv += 4;
         }
         nv >>= 4;
      }

   }

#endif

   return retval;
}

template<unsigned N>
void BitString<N>::single_point_crossover(BitString<N> ** const parents, BitString<N> ** children) {
   static UniformRand rnd = UniformRand();

   uint8_t * p0 = (uint8_t *)parents [0]->values;
   uint8_t * p1 = (uint8_t *)parents [1]->values;
   uint8_t * c0 = (uint8_t *)children[0]->values;
   uint8_t * c1 = (uint8_t *)children[1]->values;

   uint crosspoint = rnd.random() % (N + 1);

   uint before = crosspoint / __RHIZAR16_BIT_PER_BYTE__;
   uint after  = (N / __RHIZAR16_BIT_PER_BYTE__) - (before);
   uint low = crosspoint % __RHIZAR16_BIT_PER_BYTE__;
   uint high = __RHIZAR16_BIT_PER_BYTE__ - low;
   

   memcpy(c0,p1,before);
   memcpy(c1,p0,before);
   memcpy(c0 + before + 1,p0 + before + 1,after);
   memcpy(c1 + before + 1,p1 + before + 1,after);

   c0[before] = (p1[before] & (0xff >> high)) | (p0[before] & (0xff << low));
   c1[before] = (p0[before] & (0xff >> high)) | (p1[before] & (0xff << low));
}

template<unsigned N>
void BitString<N>::two_point_crossover(BitString<N> ** const parents, BitString<N> ** children) {
   static UniformRand rnd = UniformRand();

   uint8_t * p0 = (uint8_t *)parents [0]->values;
   uint8_t * p1 = (uint8_t *)parents [1]->values;
   uint8_t * c0 = (uint8_t *)children[0]->values;
   uint8_t * c1 = (uint8_t *)children[1]->values;

   uint M = (N % __RHIZAR16_BIT_PER_BYTE__ == 0 ? 
             N / __RHIZAR16_BIT_PER_BYTE__      : 
             (N + __RHIZAR16_BIT_PER_BYTE__) / __RHIZAR16_BIT_PER_BYTE__);

   uint crosspoint_low  = (rnd.random() % (N + 1));
   uint crosspoint_high = (rnd.random() % (N + 1));

   if (crosspoint_low > crosspoint_high) {
      crosspoint_low ^= crosspoint_high;
      crosspoint_high ^= crosspoint_low;
      crosspoint_low ^= crosspoint_high;
   }

   uint before = crosspoint_low / __RHIZAR16_BIT_PER_BYTE__;
   uint after = crosspoint_high / __RHIZAR16_BIT_PER_BYTE__;
   uint low = crosspoint_low % __RHIZAR16_BIT_PER_BYTE__;
   uint high = __RHIZAR16_BIT_PER_BYTE__ - (crosspoint_high % __RHIZAR16_BIT_PER_BYTE__);

   memcpy(c0,p0,before);
   memcpy(c1,p1,before);
   memcpy(c0 + after + 1, p0 + after + 1, (M - after)-1);
   memcpy(c1 + after + 1, p1 + after + 1, (M - after)-1);
   memcpy(c0 + before, p1 + before, (1 + after) - before);
   memcpy(c1 + before, p0 + before, (1 + after) - before);

   if (before == after) {
      uint8_t mask = ((0xff << low) & (0xff >> high));
      c0[before] = ((p0[before] & ~mask) | (p1[before] & mask));
      c1[before] = ((p1[before] & ~mask) | (p0[before] & mask));
   }
   else {
      c0[before] = ((p1[before] & (0xff << low)) | (p0[before] & ~(0xff << low)));
      c1[before] = ((p0[before] & (0xff << low)) | (p1[before] & ~(0xff << low)));
      c0[after] = ((p1[after] & (0xff >> high)) | (p0[after] & ~(0xff >> high)));
      c1[after] = ((p0[after] & (0xff >> high)) | (p1[after] & ~(0xff >> high)));
   }
}

template<unsigned N>
void BitString<N>::uniform_crossover(BitString<N> ** const parents, BitString<N> ** children) {
   static UniformRand rnd = UniformRand();
   uint64_t mask[parents[0]->length];

   for (uint i = 0; i < parents[0]->length; ++i)
      mask[i] = rnd.random();

   for (uint i = 0; i < parents[0]->length; ++i)
      children[0]->values[i] = (parents[0]->values[i] & mask[i]) | (parents[1]->values[i] & ~mask[i]);

}

template<unsigned N>
void BitString<N>::three_parent_crossover(BitString<N> ** const parents, BitString<N> ** children) {
   static UniformRand rnd = UniformRand();
   uint64_t mask[parents[0]->length];

   for (uint i = 0; i < parents[0]->length; ++i)
      mask[i] = parents[0]->values[i] ^ ~(parents[1]->values[i]);

   for (uint i = 0; i < parents[0]->length; ++i)
      children[0]->values[i] = (parents[0]->values[i] & mask[i]) | (parents[2]->values[i] & ~mask[i]);
}

template<unsigned N>
void BitString<N>::shuffle_crossover(BitString<N> ** const parents, BitString<N> ** children) {
   static UniformRand rnd = UniformRand();

   uint16_t mapping[N];

   for (uint i = 0; i < N; ++i)
      mapping[i] = i;

   for (uint i = 0; i < N; ++i) {
      uint swappos = rnd.random() % N;
      mapping[i] ^= mapping[swappos];
      mapping[swappos] ^= mapping[i];
      mapping[i] ^= mapping[swappos];
   }

   uint crosspoint = rnd.random() % (N + 1);

   memest(children[0]->values,0x00,children[0]->length*sizeof(long));
   memest(children[1]->values,0x00,children[1]->length*sizeof(long));
   for (int i = 0; i < crosspoint; ++i) {
      children[0]->values[mapping[i] / 64] |= (parents[0]->values[mapping[i] / 64] & (1LL << (mapping[i] % 64)));
      children[1]->values[mapping[i] / 64] |= (parents[1]->values[mapping[i] / 64] & (1LL << (mapping[i] % 64)));
   }
   for (int i = crosspoint; i < N; ++i) {
      children[0]->values[mapping[i] / 64] |= (parents[1]->values[mapping[i] / 64] & (1LL << (mapping[i] % 64)));
      children[1]->values[mapping[i] / 64] |= (parents[0]->values[mapping[i] / 64] & (1LL << (mapping[i] % 64)));
   }
}

template<unsigned N>
std::function<void(BitString<N> *)> BitString<N>::flip(double probability) {

   uint64_t compr = (double)ULLONG_MAX * probability;

   assert(probability <= 1.0 && probability >= 0.0 
         && "BitString: probability for function 'interchange' must be in the range [0.0, 1.0]");

   return [compr](BitString<N> * chromosome) {
      static UniformRand rnd = UniformRand();

      unsigned toflip = 0;
      while (rnd.random() < compr && toflip < N) toflip += 1;

      for (uint i = 0; i < toflip; ++i) {
         unsigned flip_pos = rnd.random() % N;
         chromosome->values[flip_pos / 64] ^= (1LL << flip_pos % 64);
      }
   };

}

template<unsigned N>
std::function<void(BitString<N> *)> BitString<N>::interchange(double probability) {

   uint64_t compr = (double)ULLONG_MAX * probability;

   assert(probability <= 1.0 && probability >= 0.0 
         && "BitString: probability for function 'interchange' must be in the range [0.0, 1.0]");

   return [compr](BitString<N> * chromosome) {
      static UniformRand rnd = UniformRand();

      unsigned toswap = 0;
      while (rnd.random() < compr && toswap < N) toswap += 1;

      uint64_t bit0, bit1;
      for (uint i = 0; i < toswap; ++i) {
         unsigned swap_0 = rnd.random() % N;
         unsigned swap_1 = rnd.random() % N;
         if (swap_0 == swap_1) continue;
         bit0 = (chromosome->values[swap_0 / 64] >> (swap_0 % 64)) & 1;
         bit1 = (chromosome->values[swap_1 / 64] >> (swap_1 % 64)) & 1;
         chromosome->values[swap_0 / 64] &= ~(1LL << (swap_0 % 64));
         chromosome->values[swap_1 / 64] &= ~(1LL << (swap_1 % 64));
         chromosome->values[swap_0 / 64] |= (bit1 << (swap_0 % 64));
         chromosome->values[swap_1 / 64] |= (bit0 << (swap_1 % 64));
      }
   };
}

template<unsigned N>
size_t BitString<N>::encode(BitString<N> * obj, uint8_t * buf) {

   size_t len = obj->length * sizeof(uint64_t);

   if (buf)
      memcpy(buf,obj->values,len);

   return len;
}

template<unsigned N>
size_t BitString<N>::decode(BitString<N> * obj, uint8_t * buf) {

   size_t len = obj->length * sizeof(uint64_t);

   if (buf)
      memcpy(obj->values,buf,len);

   return len;
}

}

#endif

