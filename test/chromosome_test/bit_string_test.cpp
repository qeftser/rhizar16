
#include "bit_string_test.h"
#include "bit_string.h"
#include "utils.h"

namespace Rhizar16 {

int TestBitString::initialization_0() {
   BitString<0> b;

   int ret = (b.length == 0 && b.bits == 0) ? 1 : 0;

   return ret;
}

int TestBitString::initialization_1() {
   BitString<1> b;

   int ret = (b.length == 1 && b.bits == 1) ? 1 : 0;

   return ret;
}

int TestBitString::initialization_4() {
   BitString<4> b;

   int ret = (b.length == 1 && b.bits == 4) ? 1 : 0;

   return ret;
}

int TestBitString::initialization_64() {
   BitString<64> b;

   int ret = (b.length == 1 && b.bits == 64) ? 1 : 0;

   return ret;
}

int TestBitString::initialization_128() {
   BitString<128> b;

   int ret = (b.length == 2 && b.bits == 128) ? 1 : 0;

   return ret;
}

int TestBitString::initialization_5000() {
   BitString<5000> b;

   int ret = (b.length == 79 && b.bits == 5000) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_0_0() {
   BitString<0> b1;
   BitString<0> b2;

   int ret = (BitString<0>::hamming_distance(b1,b2) == 0) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_1_1_1() {
   BitString<1> b1;
   BitString<1> b2;

   b1.values[0] = 1;
   b2.values[0] = 0;

   int ret = (BitString<1>::hamming_distance(b1,b2) == 1) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_1_1_0() {
   BitString<1> b1;
   BitString<1> b2;

   b1.values[0] = 1;
   b2.values[0] = 1;

   int ret = (BitString<1>::hamming_distance(b1,b2) == 0) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_4_4_1() {
   BitString<4> b1;
   BitString<4> b2;

   b2.values[0] = 1;
   b1.values[0] = 0;

   int ret = (BitString<4>::hamming_distance(b1,b2) == 1) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_4_4_3() {
   BitString<4> b1;
   BitString<4> b2;

   b2.values[0] = 0x7;
   b1.values[0] = 0x9;

   int ret = (BitString<4>::hamming_distance(b1,b2) == 3) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_4_4_4() {
   BitString<4> b1;
   BitString<4> b2;

   b2.values[0] = 0x0;
   b1.values[0] = 0xf;

   int ret = (BitString<4>::hamming_distance(b1,b2) == 4) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_64_64_12() {
   BitString<64> b1;
   BitString<64> b2;

   b2.values[0] = 0x010120102103101a;
   b1.values[0] = 0x0;

   int ret = (BitString<64>::hamming_distance(b1,b2) == 12) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_64_64_18() {
   BitString<64> b1;
   BitString<64> b2;

   b2.values[0] = 0x010120102103101a;
   b1.values[0] = 0xf1f1f01f2103171a;

   int ret = (BitString<64>::hamming_distance(b1,b2) == 18) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_64_64_47() {
   BitString<64> b1;
   BitString<64> b2;

   b1.values[0] = 0xf1f1f01f21031f1a;
   b2.values[0] = 0xa70feff0defc10ea;

   int ret = (BitString<64>::hamming_distance(b1,b2) == 47) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_64_64_64() {
   BitString<64> b1;
   BitString<64> b2;

   b1.values[0] = 0x0;
   b2.values[0] = 0xffffffffffffffff;

   int ret = (BitString<64>::hamming_distance(b1,b2) == 64) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_128_128_64() {
   BitString<128> b1;
   BitString<128> b2;

   b1.values[0] = 0x0;
   b1.values[1] = 0x0;
   b2.values[0] = 0x0f0f0f0f0f0f0f0f;
   b2.values[1] = 0xf0f0f0f0f0f0f0f0;

   int ret = (BitString<128>::hamming_distance(b1,b2) == 64) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_128_128_128() {
   BitString<128> b1;
   BitString<128> b2;

   b2.values[0] = 0x0;
   b2.values[1] = 0x0;
   b1.values[0] = 0xffffffffffffffff;
   b1.values[1] = 0xffffffffffffffff;

   int ret = (BitString<128>::hamming_distance(b1,b2) == 128) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_5000_5000_1014() {
   BitString<5000> b1;
   BitString<5000> b2;
   
   for (int i = 0; i < b1.length; ++i) {
      b1.values[i] = 0;
      b2.values[i] = 0;
   }

   int val = 0;
   for (int i = 0; i < b1.length-1; ++i) {

      b1.values[i] = 0x0e01003f0400c000;

   }

   int ret = (BitString<5000>::hamming_distance(b1,b2) == 1014) ? 1 : 0;

   return ret;
}


int TestBitString::hamming_distance_5000_5000_5000() {
   BitString<5000> b1;
   BitString<5000> b2;
   
   for (int i = 0; i < b1.length; ++i) {
      b1.values[i] = 0;
      b2.values[i] = 0xffffffffffffffff;
   }

   b2.values[b2.length-1] &= bitmask(b2.bits % 64);

   int ret = (BitString<5000>::hamming_distance(b1,b2) == 5000) ? 1 : 0;

   return ret;
}

int TestBitString::randomize_0() {
   BitString<128> b;

   b.values[0] = 100;
   b.values[1] = -100;

   int before0 = b.values[0];
   int before1 = b.values[1];

   b.randomize();

   int ret = (before0 != b.values[0] && before1 != b.values[1]) ? 1 : 0;

   return ret;
}

int TestBitString::randomize_1() {
   BitString<5000> b;

   int before_sum = 0;

   for (int i = 0; i < b.length; ++i)
      before_sum += (b.values[i] = i*25);

   b.randomize();

   int after_sum = 0;

   for (int i = 0; i < b.length; ++i)
      after_sum += b.values[i];
   
   int ret = (before_sum != after_sum) ? 1 : 0;

   return ret;
}

}
