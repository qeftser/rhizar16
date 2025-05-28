
#ifndef __RHIZAR16_BIT_STRING__

#define __RHIZAR16_BIT_STRING__

#include <stdint.h>
#include <string.h>
#include "uniform_rand.h"

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

   for (int i = 0; i < length; ++i)
      values[i] = rnd.random();
}

template<unsigned N>
int BitString<N>::hamming_distance(const BitString<N> & bs1, const BitString<N> & bs2) {
   int retval = 0;

   /* use the builtin popcount intrinsic if it is avaliable */
#if (defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)) && __has_builtin(__builtin_popcountll)

   for (int i = 0; i < bs1.length; ++i)
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

}

#endif

