
#ifndef __RHIZAR16_BIT_STRING__

#define __RHIZAR16_BIT_STRING__

#include <stdint.h>

namespace Rhizar16 {

/* A vector of bits to be manipulated individually */
struct BitString {

   /* =========== Struct Values =========== */
   int length;
   int bits;
   uint64_t * values;
   /* =========== Struct Values =========== */

   /* construct a bit vector of length n */
   BitString(int n);

   /* destroy the bit string */
   ~BitString();

   /* Compute the hamming distance between two bit strings */
   static int hamming_distance(const BitString & bs1, const BitString & bs2);

   /* return a bitmask of length n bits */
   static uint64_t bitmask(int n);

   /* fill the given bit string with random values
    * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    * Note: this is not going to be thread-safe   
    * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
   void randomize();

};

}

#endif

