
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

template<unsigned N>
void TestBitString::BitStringSimulation<N>::single_point_crossover(BitString<N> ** const parents, BitString<N> ** children, uint64_t * rnd) {

   int randpos = 0;

   uint8_t * p0 = (uint8_t *)parents [0]->values;
   uint8_t * p1 = (uint8_t *)parents [1]->values;
   uint8_t * c0 = (uint8_t *)children[0]->values;
   uint8_t * c1 = (uint8_t *)children[1]->values;

   uint crosspoint = rnd[randpos++] % (N + 1);

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
void TestBitString::BitStringSimulation<N>::two_point_crossover(BitString<N> ** const parents, BitString<N> ** children, uint64_t * rnd) {

   int randpos = 0;

   uint8_t * p0 = (uint8_t *)parents [0]->values;
   uint8_t * p1 = (uint8_t *)parents [1]->values;
   uint8_t * c0 = (uint8_t *)children[0]->values;
   uint8_t * c1 = (uint8_t *)children[1]->values;

   uint M = (N % __RHIZAR16_BIT_PER_BYTE__ == 0 ? 
             N / __RHIZAR16_BIT_PER_BYTE__      : 
             (N + __RHIZAR16_BIT_PER_BYTE__) / __RHIZAR16_BIT_PER_BYTE__);

   uint crosspoint_low  = (rnd[randpos++] % (N + 1));
   uint crosspoint_high = (rnd[randpos++] % (N + 1));

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
void TestBitString::BitStringSimulation<N>::uniform_crossover(BitString<N> ** const parents, BitString<N> ** children, uint64_t * rnd) {

   int randpos = 0;

   uint64_t mask[parents[0]->length];

   for (uint i = 0; i < parents[0]->length; ++i)
      mask[i] = rnd[randpos++];

   for (uint i = 0; i < parents[0]->length; ++i)
      children[0]->values[i] = (parents[0]->values[i] & mask[i]) | (parents[1]->values[i] & ~mask[i]);
}

template<unsigned N>
void TestBitString::BitStringSimulation<N>::three_parent_crossover(BitString<N> ** const parents, BitString<N> ** children, uint64_t * rnd) {

   (void)rnd;

   uint64_t mask[parents[0]->length];

   for (uint i = 0; i < parents[0]->length; ++i)
      mask[i] = parents[0]->values[i] ^ ~(parents[1]->values[i]);

   for (uint i = 0; i < parents[0]->length; ++i)
      children[0]->values[i] = (parents[0]->values[i] & mask[i]) | (parents[2]->values[i] & ~mask[i]);
}

template<unsigned N>
void TestBitString::BitStringSimulation<N>::shuffle_crossover(BitString<N> ** const parents, BitString<N> ** children, uint64_t * rnd) {

   int randpos = 0;

   uint16_t mapping[N];

   for (uint i = 0; i < N; ++i)
      mapping[i] = i;

   for (uint i = 0; i < N; ++i) {
      uint swappos = rnd[randpos++] % N;
      if (swappos == i)
         continue;
      mapping[i] ^= mapping[swappos];
      mapping[swappos] ^= mapping[i];
      mapping[i] ^= mapping[swappos];
   }

   uint crosspoint = rnd[randpos++] % (N + 1);

   memset(children[0]->values,0,children[0]->length*sizeof(uint64_t));
   memset(children[1]->values,0,children[1]->length*sizeof(uint64_t));
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
void TestBitString::BitStringSimulation<N>::flip(BitString<N> * chromosome, uint64_t * rnd, uint num, uint den) {

   ulong threshold = (ULONG_MAX * ((double)num / den));
   int randpos = 0;

   unsigned toflip = 0;
   while (rnd[randpos++] < threshold && toflip < N) toflip += 1;

   for (uint i = 0; i < toflip; ++i) {
      unsigned flip_pos = rnd[randpos++] % N;
      chromosome->values[flip_pos / 64] ^= (1LL << flip_pos % 64);
   }

}

template<unsigned N>
void TestBitString::BitStringSimulation<N>::interchange(BitString<N> * chromosome, uint64_t * rnd, uint num, uint den) {

   ulong threshold = (ULONG_MAX * ((double)num / den));
   int randpos = 0;

   unsigned toswap = 0;
   while (rnd[randpos++] < threshold && toswap < N) toswap += 1;

   unsigned long long bit0, bit1;
   for (uint i = 0; i < toswap; ++i) {
      unsigned swap_0 = rnd[randpos++] % N;
      unsigned swap_1 = rnd[randpos++] % N;
      if (swap_0 == swap_1) continue;
      bit0 = (chromosome->values[swap_0 / 64] >> (swap_0 % 64)) & 1;
      bit1 = (chromosome->values[swap_1 / 64] >> (swap_1 % 64)) & 1;
      chromosome->values[swap_0 / 64] &= ~(1LL << (swap_0 % 64));
      chromosome->values[swap_1 / 64] &= ~(1LL << (swap_1 % 64));
      chromosome->values[swap_0 / 64] |= (bit1 << (swap_0 % 64));
      chromosome->values[swap_1 / 64] |= (bit0 << (swap_1 % 64));
   }
}

int TestBitString::single_point_crossover_0() {

   BitString<4> a, b, x, y;
   BitString<4> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xf;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd = 2;

   BitStringSimulation<4>::single_point_crossover(p,c,&rnd);

   int retval = 1;

   if (x.values[0] != 0x3)
      retval = 0;

   if (y.values[0] != 0xc)
      retval = 0;

   return retval;
}

int TestBitString::single_point_crossover_1() {

   BitString<20> a, b, x, y;
   BitString<20> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xfffff;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd = 2;

   BitStringSimulation<20>::single_point_crossover(p,c,&rnd);

   int retval = 1;

   if (x.values[0] != 0x3)
      retval = 0;

   if (y.values[0] != 0xffffc)
      retval = 0;

   return retval;
}

int TestBitString::single_point_crossover_2() {

   BitString<20> a, b, x, y;
   BitString<20> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xfffff;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd = 18;

   BitStringSimulation<20>::single_point_crossover(p,c,&rnd);

   int retval = 1;

   if (x.values[0] != 0x3ffff)
      retval = 0;

   if (y.values[0] != 0xc0000)
      retval = 0;

   return retval;
}

int TestBitString::single_point_crossover_3() {

   BitString<20> a, b, x, y;
   BitString<20> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xfffff;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd = 10;

   BitStringSimulation<20>::single_point_crossover(p,c,&rnd);

   int retval = 1;

   if (x.values[0] != 0x3ff)
      retval = 0;

   if (y.values[0] != 0xffc00)
      retval = 0;

   return retval;
}

int TestBitString::two_point_crossover_0() {

   BitString<4> a, b, x, y;
   BitString<4> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xf;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd[2] = { 2, 2 };

   BitStringSimulation<4>::two_point_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 0)
      retval = 0;

   if (y.values[0] != 0xf)
      retval = 0;

   return retval;
}

int TestBitString::two_point_crossover_1() {

   BitString<4> a, b, x, y;
   BitString<4> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xf;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd[2] = { 1, 3 };

   BitStringSimulation<4>::two_point_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 0x6)
      retval = 0;

   if (y.values[0] != 0x9)
      retval = 0;

   return retval;
}

int TestBitString::two_point_crossover_2() {

   BitString<4> a, b, x, y;
   BitString<4> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xf;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd[2] = { 0, 3 };

   BitStringSimulation<4>::two_point_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 7)
      retval = 0;

   if (y.values[0] != 8)
      retval = 0;

   return retval;
}

int TestBitString::two_point_crossover_3() {

   BitString<20> a, b, x, y;
   BitString<20> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xfffff;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd[2] = { 0, 3 };

   BitStringSimulation<20>::two_point_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 7)
      retval = 0;

   if (y.values[0] != 0xffff8)
      retval = 0;

   return retval;
}

int TestBitString::two_point_crossover_4() {

   BitString<20> a, b, x, y;
   BitString<20> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xfffff;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd[2] = { 16, 18 };

   BitStringSimulation<20>::two_point_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 0x30000)
      retval = 0;

   if (y.values[0] != 0xcffff)
      retval = 0;

   return retval;
}

int TestBitString::two_point_crossover_5() {

   BitString<20> a, b, x, y;
   BitString<20> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xfffff;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd[2] = { 8, 10 };

   BitStringSimulation<20>::two_point_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 0x00300)
      retval = 0;

   if (y.values[0] != 0xffcff)
      retval = 0;

   return retval;
}

int TestBitString::two_point_crossover_6() {

   BitString<40> a, b, x, y;
   BitString<40> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xffffffffff;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd[2] = { 10, 30 };

   BitStringSimulation<40>::two_point_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 0x003ffffc00)
      retval = 0;

   if (y.values[0] != 0xffc00003ff)
      retval = 0;

   return retval;
}

int TestBitString::two_point_crossover_7() {

   BitString<40> a, b, x, y;
   BitString<40> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xffffffffff;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd[2] = { 5, 10 };

   BitStringSimulation<40>::two_point_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 0x00000003e0)
      retval = 0;

   if (y.values[0] != 0xfffffffc1f)
      retval = 0;

   return retval;
}

int TestBitString::two_point_crossover_8() {

   BitString<40> a, b, x, y;
   BitString<40> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xffffffffff;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd[2] = { 17, 38 };

   BitStringSimulation<40>::two_point_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 0x3ffffe0000)
      retval = 0;

   if (y.values[0] != 0xc00001ffff)
      retval = 0;

   return retval;
}

int TestBitString::uniform_crossover_0() {

   BitString<64> a, b, x;
   BitString<64> * p[2], * c[1];
   p[0] = &a; p[1] = &b;
   c[0] = &x;

   a.values[0] = 0;
   b.values[0] = 0xffffffffffffffff;
   x.values[0] = 0;

   uint64_t rnd = 0xf0f0f0f0f0f0f0f0;

   BitStringSimulation<64>::uniform_crossover(p,c,&rnd);

   int retval = 1;

   if (x.values[0] != 0x0f0f0f0f0f0f0f0f)
      retval = 0;

   return retval;
}

int TestBitString::uniform_crossover_1() {

   BitString<64> a, b, x;
   BitString<64> * p[2], * c[1];
   p[0] = &a; p[1] = &b;
   c[0] = &x;

   a.values[0] = 0xffffffffffffffff;
   b.values[0] = 0;
   x.values[0] = 0;

   uint64_t rnd = 0xf0f0f0f0f0f0f0f0;

   BitStringSimulation<64>::uniform_crossover(p,c,&rnd);

   int retval = 1;

   if (x.values[0] != 0xf0f0f0f0f0f0f0f0)
      retval = 0;

   return retval;
}

int TestBitString::uniform_crossover_2() {

   BitString<320> a, b, x;
   BitString<320> * p[2], * c[1];
   p[0] = &a; p[1] = &b;
   c[0] = &x;

   memset(a.values,0,sizeof(uint64_t)*5);
   memset(b.values,0xff,sizeof(uint64_t)*5);
   memset(x.values,0,sizeof(uint64_t)*5);

   uint64_t rnd[5] = { 0x1111111111111111, 0x2222222222222222,
                       0x4444444444444444, 0x8888888888888888,
                       0x9999999999999999 };

   BitStringSimulation<320>::uniform_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 0xeeeeeeeeeeeeeeee)
      retval = 0;

   if (x.values[1] != 0xdddddddddddddddd)
      retval = 0;

   if (x.values[2] != 0xbbbbbbbbbbbbbbbb)
      retval = 0;

   if (x.values[3] != 0x7777777777777777)
      retval = 0;

   if (x.values[4] != 0x6666666666666666)
      retval = 0;

   return retval;
}

int TestBitString::uniform_crossover_3() {

   BitString<320> a, b, x;
   BitString<320> * p[2], * c[1];
   p[0] = &a; p[1] = &b;
   c[0] = &x;

   memset(a.values,0xff,sizeof(uint64_t)*5);
   memset(b.values,0,sizeof(uint64_t)*5);
   memset(x.values,0,sizeof(uint64_t)*5);

   uint64_t rnd[5] = { 0x1111111111111111, 0x2222222222222222,
                       0x4444444444444444, 0x8888888888888888,
                       0x9999999999999999 };

   BitStringSimulation<320>::uniform_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 0x1111111111111111)
      retval = 0;

   if (x.values[1] != 0x2222222222222222)
      retval = 0;

   if (x.values[2] != 0x4444444444444444)
      retval = 0;

   if (x.values[3] != 0x8888888888888888)
      retval = 0;

   if (x.values[4] != 0x9999999999999999)
      retval = 0;

   return retval;
}

int TestBitString::three_parent_crossover_0() {

   BitString<64> a, b, d, x;
   BitString<64> * p[3], * c[1];
   p[0] = &a; p[1] = &b;
   p[2] = &d; c[0] = &x;

   a.values[0] = 0;
   d.values[0] = 0;
   b.values[0] = 0xffffffffffffffff;
   x.values[0] = 0;

   BitStringSimulation<64>::three_parent_crossover(p,c,NULL);

   int retval = 1;

   if (x.values[0] != 0x0000000000000000)
      retval = 0;

   return retval;
}

int TestBitString::three_parent_crossover_1() {

   BitString<64> a, b, d, x;
   BitString<64> * p[3], * c[1];
   p[0] = &a; p[1] = &b;
   p[2] = &d; c[0] = &x;

   a.values[0] = 0;
   d.values[0] = 0xffffffffffffffff;
   b.values[0] = 0xffffffffffffffff;
   x.values[0] = 0;

   BitStringSimulation<64>::three_parent_crossover(p,c,NULL);

   int retval = 1;

   if (x.values[0] != 0xffffffffffffffff)
      retval = 0;

   return retval;
}

int TestBitString::three_parent_crossover_2() {

   BitString<64> a, b, d, x;
   BitString<64> * p[3], * c[1];
   p[0] = &a; p[1] = &b;
   p[2] = &d; c[0] = &x;

   a.values[0] = 0xffffffffffffffff;
   d.values[0] = 0;
   b.values[0] = 0xffffffffffffffff;
   x.values[0] = 0;

   BitStringSimulation<64>::three_parent_crossover(p,c,NULL);

   int retval = 1;

   if (x.values[0] != 0xffffffffffffffff)
      retval = 0;

   return retval;
}

int TestBitString::three_parent_crossover_3() {

   BitString<64> a, b, d, x;
   BitString<64> * p[3], * c[1];
   p[0] = &a; p[1] = &b;
   p[2] = &d; c[0] = &x;

   a.values[0] = 0xffffffffffffffff;
   d.values[0] = 0xffffffffffffffff;
   b.values[0] = 0;
   x.values[0] = 0;

   BitStringSimulation<64>::three_parent_crossover(p,c,NULL);

   int retval = 1;

   if (x.values[0] != 0xffffffffffffffff)
      retval = 0;

   return retval;
}

int TestBitString::three_parent_crossover_4() {

   BitString<320> a, b, d, x;
   BitString<320> * p[3], * c[1];
   p[0] = &a; p[1] = &b;
   p[2] = &d; c[0] = &x;

   memset(a.values,0x01,sizeof(uint64_t)*5);
   memset(d.values,0xff,sizeof(uint64_t)*5);
   memset(b.values,0x00,sizeof(uint64_t)*5);
   memset(x.values,0x00,sizeof(uint64_t)*5);

   BitStringSimulation<320>::three_parent_crossover(p,c,NULL);

   int retval = 1;

   if (x.values[0] != 0x0101010101010101)
      retval = 0;

   if (x.values[1] != 0x0101010101010101)
      retval = 0;

   if (x.values[2] != 0x0101010101010101)
      retval = 0;

   if (x.values[3] != 0x0101010101010101)
      retval = 0;

   if (x.values[4] != 0x0101010101010101)
      retval = 0;

   return retval;
}

int TestBitString::three_parent_crossover_5() {

   BitString<320> a, b, d, x;
   BitString<320> * p[3], * c[1];
   p[0] = &a; p[1] = &b;
   p[2] = &d; c[0] = &x;

   memset(a.values,0xff,sizeof(uint64_t)*5);
   memset(d.values,0x00,sizeof(uint64_t)*5);
   memset(b.values,0x88,sizeof(uint64_t)*5);
   memset(x.values,0x00,sizeof(uint64_t)*5);

   BitStringSimulation<320>::three_parent_crossover(p,c,NULL);

   int retval = 1;

   if (x.values[0] != 0x8888888888888888)
      retval = 0;

   if (x.values[1] != 0x8888888888888888)
      retval = 0;

   if (x.values[2] != 0x8888888888888888)
      retval = 0;

   if (x.values[3] != 0x8888888888888888)
      retval = 0;

   if (x.values[4] != 0x8888888888888888)
      retval = 0;

   return retval;
}

int TestBitString::three_parent_crossover_6() {

   BitString<320> a, b, d, x;
   BitString<320> * p[3], * c[1];
   p[0] = &a; p[1] = &b;
   p[2] = &d; c[0] = &x;

   memset(a.values,0x33,sizeof(uint64_t)*5);
   memset(d.values,0x00,sizeof(uint64_t)*5);
   memset(b.values,0xff,sizeof(uint64_t)*5);
   memset(x.values,0x00,sizeof(uint64_t)*5);

   BitStringSimulation<320>::three_parent_crossover(p,c,NULL);

   int retval = 1;

   if (x.values[0] != 0x3333333333333333)
      retval = 0;

   if (x.values[1] != 0x3333333333333333)
      retval = 0;

   if (x.values[2] != 0x3333333333333333)
      retval = 0;

   if (x.values[3] != 0x3333333333333333)
      retval = 0;

   if (x.values[4] != 0x3333333333333333)
      retval = 0;

   return retval;
}

int TestBitString::shuffle_crossover_0() {

   BitString<20> a, b, x, y;
   BitString<20> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xfffff;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd[21] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 
                        10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                        10 };

   BitStringSimulation<20>::shuffle_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 0xffc00)
      retval = 0;

   if (y.values[0] != 0x003ff)
      retval = 0;

   return retval;
}

int TestBitString::shuffle_crossover_1() {

   BitString<20> a, b, x, y;
   BitString<20> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   a.values[0] = 0;
   b.values[0] = 0xfffff;
   x.values[0] = 0;
   y.values[0] = 0;

   uint64_t rnd[21] = { 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 
                        10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                        10 };

   BitStringSimulation<20>::shuffle_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 0x003ff)
      retval = 0;

   if (y.values[0] != 0xffc00)
      retval = 0;

   return retval;
}

int TestBitString::shuffle_crossover_2() {

   BitString<320> a, b, x, y;
   BitString<320> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   memset(a.values,0,sizeof(uint64_t)*5);
   memset(x.values,0,sizeof(uint64_t)*5);
   memset(y.values,0,sizeof(uint64_t)*5);
   memset(b.values,0xff,sizeof(uint64_t)*5);
   uint8_t * setter = (uint8_t *)b.values;
   for (int i = 0; i < (320 / __RHIZAR16_BIT_PER_BYTE__); ++i)
      setter[i] = i;

   uint64_t rnd[321];
   for (int i = 0; i < 320; ++i)
      rnd[i] = i;
   for (int i = 0; i < 160; ++i)
      rnd[i] = 319 - i;
   rnd[320] = 320;

   BitStringSimulation<320>::shuffle_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[0] != 0)
      retval = 0;
   if (x.values[1] != 0)
      retval = 0;
   if (x.values[2] != 0)
      retval = 0;
   if (x.values[3] != 0)
      retval = 0;
   if (x.values[4] != 0)
      retval = 0;

   if (y.values[0] != 0x0706050403020100)
      retval = 0;
   if (y.values[1] != 0x0f0e0d0c0b0a0908)
      retval = 0;
   if (y.values[2] != 0x1716151413121110)
      retval = 0;
   if (y.values[3] != 0x1f1e1d1c1b1a1918)
      retval = 0;
   if (y.values[4] != 0x2726252423222120)
      retval = 0;

   return retval;
}

int TestBitString::shuffle_crossover_3() {

   BitString<320> a, b, x, y;
   BitString<320> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   memset(a.values,0,sizeof(uint64_t)*5);
   memset(x.values,0,sizeof(uint64_t)*5);
   memset(y.values,0,sizeof(uint64_t)*5);
   memset(b.values,0xff,sizeof(uint64_t)*5);
   uint8_t * setter = (uint8_t *)b.values;
   for (int i = 0; i < (320 / __RHIZAR16_BIT_PER_BYTE__); ++i)
      setter[i] = i;

   uint64_t rnd[321];
   for (int i = 0; i < 320; ++i)
      rnd[i] = i;
   for (int i = 0; i < 160; ++i)
      rnd[i] = 319 - i;
   rnd[320] = 0;

   BitStringSimulation<320>::shuffle_crossover(p,c,rnd);

   int retval = 1;

   if (y.values[0] != 0)
      retval = 0;
   if (y.values[1] != 0)
      retval = 0;
   if (y.values[2] != 0)
      retval = 0;
   if (y.values[3] != 0)
      retval = 0;
   if (y.values[4] != 0)
      retval = 0;

   if (x.values[0] != 0x0706050403020100)
      retval = 0;
   if (x.values[1] != 0x0f0e0d0c0b0a0908)
      retval = 0;
   if (x.values[2] != 0x1716151413121110)
      retval = 0;
   if (x.values[3] != 0x1f1e1d1c1b1a1918)
      retval = 0;
   if (x.values[4] != 0x2726252423222120)
      retval = 0;

   return retval;
}

int TestBitString::shuffle_crossover_4() {

   BitString<320> a, b, x, y;
   BitString<320> * p[2], * c[2];
   p[0] = &a; p[1] = &b;
   c[0] = &x; c[1] = &y;

   memset(a.values,0,sizeof(uint64_t)*5);
   memset(x.values,0,sizeof(uint64_t)*5);
   memset(y.values,0,sizeof(uint64_t)*5);
   memset(b.values,0xff,sizeof(uint64_t)*5);
   uint8_t * setter = (uint8_t *)b.values;
   for (int i = 0; i < (320 / __RHIZAR16_BIT_PER_BYTE__); ++i)
      setter[i] = i;

   uint64_t rnd[321];
   for (int i = 0; i < 320; ++i)
      rnd[i] = i;
   for (int i = 0; i < 160; ++i)
      rnd[i] = 319 - i;
   rnd[320] = 160;

   BitStringSimulation<320>::shuffle_crossover(p,c,rnd);

   int retval = 1;

   if (x.values[3] != 0)
      retval = 0;
   if (x.values[4] != 0)
      retval = 0;
   if (y.values[0] != 0)
      retval = 0;
   if (y.values[1] != 0)
      retval = 0;

   if (x.values[2] != 0x0000000013121110)
      retval = 0;
   if (x.values[1] != 0x0f0e0d0c0b0a0908)
      retval = 0;
   if (x.values[0] != 0x0706050403020100)
      retval = 0;

   if (y.values[2] != 0x1716151400000000)
      retval = 0;
   if (y.values[3] != 0x1f1e1d1c1b1a1918)
      retval = 0;
   if (y.values[4] != 0x2726252423222120)
      retval = 0;

   return retval;
}

int TestBitString::flip_0() {

   BitString<10> a;

   a.values[0] = 0;

   uint64_t rnd[1] = { ULONG_MAX };

   BitStringSimulation<10>::flip(&a,rnd,99,100);

   int retval = 1;

   if (a.values[0] != 0)
      retval = 0;

   return retval;
}

int TestBitString::flip_1() {

   BitString<10> a;

   a.values[0] = 0;

   uint64_t rnd[1] = { (uint64_t)(ULONG_MAX * ((double)50 / 100)) };

   BitStringSimulation<10>::flip(&a,rnd,50,100);

   int retval = 1;

   if (a.values[0] != 0)
      retval = 0;

   return retval;
}

int TestBitString::flip_2() {

   BitString<10> a;

   a.values[0] = 0;

   uint64_t rnd[3] = { (uint64_t)(ULONG_MAX * ((double)50 / 100)) - 1,
                       ULONG_MAX, 0 };

   BitStringSimulation<10>::flip(&a,rnd,50,100);

   int retval = 1;

   if (a.values[0] != 1)
      retval = 0;

   return retval;
}

int TestBitString::flip_3() {

   BitString<320> a;
   memset(a.values,0,sizeof(uint64_t)*5);

   uint64_t rnd[11] = { 0, 0, 0, 0, 0, ULONG_MAX,
                        5, 70, 140, 200, 300 };

   BitStringSimulation<320>::flip(&a,rnd,50,100);

   int retval = 1;

   if (a.values[0] != 0x20)
      retval = 0;
   if (a.values[1] != 0x40)
      retval = 0;
   if (a.values[2] != 0x1000)
      retval = 0;
   if (a.values[3] != 0x100)
      retval = 0;
   if (a.values[4] != 0x100000000000)
      retval = 0;

   return retval;
}

int TestBitString::flip_4() {

   BitString<3> a;
   memset(a.values,0,sizeof(uint64_t));

   uint64_t rnd[10] = { 0, 0, 0, 0, 0, 1, 2 };

   BitStringSimulation<3>::flip(&a,rnd,50,100);

   int retval = 1;

   if (a.values[0] != 7)
      retval = 0;

   return retval;
}

int TestBitString::interchange_0() {

   BitString<10> a;

   a.values[0] = 1;

   uint64_t rnd[1] = { ULONG_MAX };

   BitStringSimulation<10>::interchange(&a,rnd,99,100);

   int retval = 1;

   if (a.values[0] != 1)
      retval = 0;

   return retval;
}

int TestBitString::interchange_1() {

   BitString<10> a;

   a.values[0] = 1;

   uint64_t rnd[1] = { (uint64_t)(ULONG_MAX * ((double)50 / 100)) };

   BitStringSimulation<10>::interchange(&a,rnd,50,100);

   int retval = 1;

   if (a.values[0] != 1)
      retval = 0;

   return retval;
}

int TestBitString::interchange_2() {

   BitString<10> a;

   a.values[0] = 1;

   uint64_t rnd[4] = { (uint64_t)(ULONG_MAX * ((double)50 / 100)) - 1,
                       ULONG_MAX, 0, 1 };

   BitStringSimulation<10>::interchange(&a,rnd,50,100);

   int retval = 1;

   if (a.values[0] != 2)
      retval = 0;

   return retval;
}

int TestBitString::interchange_3() {

   BitString<320> a;
   a.values[0] = 0x0000000100000000; 
   a.values[1] = 0x0020000000000000; 
   a.values[2] = 0x0000000000400000;
   a.values[3] = 0x0000080000000000;
   a.values[4] = 0x0000000000000010;

   uint64_t rnd[16] = { 0, 0, 0, 0, 0, ULONG_MAX,
                        32,  300,
                        117, 200,
                        150, 140,
                        235,  70,
                        260,   5 };

   BitStringSimulation<320>::interchange(&a,rnd,50,100);

   int retval = 1;

   if (a.values[0] != 0x20)
      retval = 0;
   if (a.values[1] != 0x40)
      retval = 0;
   if (a.values[2] != 0x1000)
      retval = 0;
   if (a.values[3] != 0x100)
      retval = 0;
   if (a.values[4] != 0x100000000000)
      retval = 0;

   return retval;
}

int TestBitString::interchange_4() {

   BitString<3> a;
   a.values[0] = 1;

   uint64_t rnd[11] = { 0, 0, 0, 0, 0, 2, 2, 1, 1, 2 };

   BitStringSimulation<3>::interchange(&a,rnd,50,100);

   int retval = 1;

   if (a.values[0] != 4)
      retval = 0;

   return retval;
}


}
