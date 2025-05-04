
#include "bit_string_test.h"
#include "bit_string.h"

namespace Rhizar16 {

int TestBitString::initialization_0() {
   BitString b(0);

   int ret = (b.length == 0 && b.bits == 0) ? 1 : 0;

   return ret;
}

int TestBitString::initialization_1() {
   BitString b(1);

   int ret = (b.length == 1 && b.bits == 1) ? 1 : 0;

   return ret;
}

int TestBitString::initialization_4() {
   BitString b(4);

   int ret = (b.length == 1 && b.bits == 4) ? 1 : 0;

   return ret;
}

int TestBitString::initialization_64() {
   BitString b(64);

   int ret = (b.length == 1 && b.bits == 64) ? 1 : 0;

   return ret;
}

int TestBitString::initialization_128() {
   BitString b(128);

   int ret = (b.length == 2 && b.bits == 128) ? 1 : 0;

   return ret;
}

int TestBitString::initialization_5000() {
   BitString b(5000);

   int ret = (b.length == 5000/64 && b.bits == 5000) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_0_0() {
   BitString b1(0);
   BitString b2(0);

   int ret = (BitString::hamming_distance(b1,b2) == 0) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_1_1_1() {
   BitString b1(1);
   BitString b2(1);

   b1.values[0] = 1;
   b2.values[0] = 0;

   int ret = (BitString::hamming_distance(b1,b2) == 1) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_1_1_0() {
   BitString b1(1);
   BitString b2(1);

   b1.values[0] = 1;
   b2.values[0] = 1;

   int ret = (BitString::hamming_distance(b1,b2) == 0) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_4_4_1() {
   BitString b1(4);
   BitString b2(4);

   b2.values[0] = 1;
   b1.values[0] = 0;

   int ret = (BitString::hamming_distance(b1,b2) == 1) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_4_4_3() {
   BitString b1(4);
   BitString b2(4);

   b2.values[0] = 0x7;
   b1.values[0] = 0x9;

   int ret = (BitString::hamming_distance(b1,b2) == 3) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_4_4_4() {
   BitString b1(4);
   BitString b2(4);

   b2.values[0] = 0x0;
   b1.values[0] = 0xf;

   int ret = (BitString::hamming_distance(b1,b2) == 4) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_64_64_12() {
   BitString b1(64);
   BitString b2(64);

   b2.values[0] = 0x010120102103101a;
   b1.values[0] = 0x0;

   int ret = (BitString::hamming_distance(b1,b2) == 12) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_64_64_18() {
   BitString b1(64);
   BitString b2(64);

   b2.values[0] = 0x010120102103101a;
   b1.values[0] = 0xf1f1f01f21031f1a;

   int ret = (BitString::hamming_distance(b1,b2) == 18) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_64_64_47() {
   BitString b1(64);
   BitString b2(64);

   b1.values[0] = 0xf1f1f01f21031f1a;
   b2.values[0] = 0xa70feff0defc10ea;

   int ret = (BitString::hamming_distance(b1,b2) == 47) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_64_64_64() {
   BitString b1(64);
   BitString b2(64);

   b1.values[0] = 0x0;
   b2.values[0] = 0xffffffffffffffff;

   int ret = (BitString::hamming_distance(b1,b2) == 64) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_128_128_64() {
   BitString b1(128);
   BitString b2(128);

   b1.values[0] = 0x0;
   b1.values[1] = 0x0;
   b2.values[0] = 0x0f0f0f0f0f0f0f0f;
   b2.values[1] = 0xf0f0f0f0f0f0f0f0;

   int ret = (BitString::hamming_distance(b1,b2) == 64) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_128_128_128() {
   BitString b1(128);
   BitString b2(128);

   b2.values[0] = 0x0;
   b2.values[1] = 0x0;
   b1.values[0] = 0xffffffffffffffff;
   b1.values[1] = 0xffffffffffffffff;

   int ret = (BitString::hamming_distance(b1,b2) == 64) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_5000_5000_1000() {
   BitString b1(5000);
   BitString b2(5000);
   
   for (int i = 0; i < b1.length; ++i)
      b1.values[i] = b2.values[i] = 0;

   for (int i = 0; i < 5000; ++i) {
      if (i % 5)
         b2.values[i/64] |= 1 << (i%64);
   }

   int ret = (BitString::hamming_distance(b1,b2) == 1000) ? 1 : 0;

   return ret;
}


int TestBitString::hamming_distance_5000_5000_5000() {
   BitString b1(5000);
   BitString b2(5000);
   
   for (int i = 0; i < b1.length; ++i) {
      b1.values[i] = 0;
      b2.values[i] = 0xffffffffffffffff;
   }

   b2.values[b2.length-1] &= BitString::bitmask(b2.length % 64);

   int ret = (BitString::hamming_distance(b1,b2) == 1000) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_0_1() {
   BitString b1(0);
   BitString b2(1);

   b2.values[0] = 1;
   
   int ret = (BitString::hamming_distance(b1,b2) == 0) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_0_128() {
   BitString b1(0);
   BitString b2(128);

   b2.values[0] = 0xfffffffffff;
   b2.values[1] = 0xfffffffffff;
   
   int ret = (BitString::hamming_distance(b1,b2) == 0) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_64_128() {
   BitString b1(64);
   BitString b2(128);

   b1.values[0] = 0xffffffffffffffff;
   b2.values[0] = 0xffffffff;
   b2.values[1] = 0xffffffff;
   
   int ret = (BitString::hamming_distance(b1,b2) == 64) ? 1 : 0;

   return ret;
}

int TestBitString::hamming_distance_128_5000() {
   BitString b1(5000);
   BitString b2(128);

   for (int i = 0; i < b1.length; ++i)
      b1.values[i] = 0;

   b2.values[0] = 0xffffffffffffffff;
   b2.values[1] = 0xffffffffffffffff;
   
   int ret = (BitString::hamming_distance(b1,b2) == 128) ? 1 : 0;

   return ret;
}

int TestBitString::randomize_0() {
   BitString b(128);

   int before0 = b.values[0];
   int before1 = b.values[1];

   b.randomize();

   int ret = (before0 != b.values[0] && before1 != b.values[1]) ? 1 : 0;

   return ret;
}

int TestBitString::randomize_1() {
   BitString b(5000);

   int before_sum = 0;

   for (int i = 0; i < b.length; ++i)
      before_sum += b.values[i];

   b.randomize();

   int after_sum = 0;

   for (int i = 0; i < b.length; ++i)
      after_sum += b.values[i];
   
   int ret = (before_sum != after_sum) ? 1 : 0;

   return ret;
}

}
