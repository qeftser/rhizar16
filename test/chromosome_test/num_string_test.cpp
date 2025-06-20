
#include "num_string_test.h"

namespace Rhizar16 {

namespace TestNumString {

template<typename T, unsigned N>
void NumStringSimulation<T,N>::single_point_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children, uint64_t * rnd) {

   uint32_t crossover_point = *(rnd++) % N;
   uint32_t crossover_bytes = sizeof(T) * crossover_point;
   uint32_t crossover_rever = sizeof(T) * (N - crossover_point);

   memcpy((&children[0]->values),(&parents[0]->values),crossover_bytes);
   memcpy((&children[1]->values[crossover_point]),(&parents[0]->values[crossover_point]),crossover_rever);
   memcpy((&children[1]->values),(&parents[1]->values),crossover_bytes);
   memcpy((&children[0]->values[crossover_point]),(&parents[1]->values[crossover_point]),crossover_rever);

}

#include <stdio.h>

template<typename T, unsigned N>
void NumStringSimulation<T,N>::two_point_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children, uint64_t * rnd) {

   uint32_t crossover_one = *(rnd++) % N;
   uint32_t crossover_two = *(rnd++) % (N + 1);

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
void NumStringSimulation<T,N>::uniform_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children, uint64_t * rnd) {

   uint8_t mask[N];

   for (uint32_t i = 0; i < N; ++i)
      mask[i] = *(rnd++) % 2;

   for (uint32_t i = 0; i < N; ++i)
      children[0]->values[i] = (mask[i] ? parents[0]->values[i] : parents[1]->values[i]);
}

template<typename T, unsigned N>
void NumStringSimulation<T,N>::shuffle_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children, uint64_t * rnd) {

   uint16_t mapping[N];

   for (uint32_t i = 0; i < N; ++i)
      mapping[i] = i;

   for (uint32_t i = 0; i < N; ++i) {
      uint32_t swappos = *(rnd++) % N;
      if (swappos == i) continue;
      mapping[i] ^= mapping[swappos];
      mapping[swappos] ^= mapping[i];
      mapping[i] ^= mapping[swappos];
   }

   uint32_t crosspoint = *(rnd++) % (N + 1);

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
void NumStringSimulation<T,N>::precedence_preservative_crossover(NumString<T,N> ** const parents,
                                                                 NumString<T,N> ** children, uint64_t * rnd) {
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

template<typename T, unsigned N>
void NumStringSimulation<T,N>::ordered_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children, uint64_t * rnd) {
   static std::unordered_set<T> seen0;
   static std::unordered_set<T> seen1;

   uint32_t crossover_one = *(rnd++) % (N + 1);
   uint32_t crossover_two = *(rnd++) % (N + 1);

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
void NumStringSimulation<T,N>::partially_matched_crossover(NumString<T,N> ** const parents,
                                                           NumString<T,N> ** children, uint64_t * rnd) {
   static std::unordered_set<T> seen0;
   static std::unordered_set<T> seen1;

   uint32_t crossover_one = *(rnd++) % (N + 1);
   uint32_t crossover_two = *(rnd++) % (N + 1);

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

   for (uint32_t i = 0; i < N; ++i) {
      uint32_t internal_pos = (i + crossover_two) % N;

      if (seen1.count(parents[0]->values[internal_pos]))
         children[0]->values[internal_pos] = parents[0]->values[repl_pos0++];

      if (seen0.count(parents[1]->values[internal_pos]))
         children[1]->values[internal_pos] = parents[1]->values[repl_pos1++];
   }
}

template<typename T, unsigned N>
std::function<void(NumString<T,N> *, uint64_t *)> NumStringSimulation<T,N>::noise(std::function<T()> generator, double probability) {

   uint64_t compr = (double)ULLONG_MAX * probability;

   return [generator,compr](NumString<T,N> * val, uint64_t * rnd){

      unsigned toapply = 0;
      while (toapply < N && *(rnd++) < compr) toapply += 1;

      for (uint32_t i = 0; i < toapply; ++i)
         val->values[*(rnd++) % N] += generator();
   };
}

template<typename T, unsigned N>
std::function<void(NumString<T,N> *, uint64_t *)> NumStringSimulation<T,N>::interchange(double probability) {

   uint64_t compr = (double)ULLONG_MAX * probability;

   return [compr](NumString<T,N> * val, uint64_t * rnd){
      
      unsigned toswap = 0;
      while (toswap < N && *(rnd++) < compr) toswap += 1;

      for (uint32_t i = 0; i < toswap; ++i) {
         unsigned swap0 = *(rnd++) % N;
         unsigned swap1 = *(rnd++) % N;
         if (swap0 == swap1) continue;

         val->values[swap0] ^= val->values[swap1];
         val->values[swap1] ^= val->values[swap0];
         val->values[swap0] ^= val->values[swap1];
      }
   };
}

int intialization_0() {
   NumString<uint8_t,4> n;

   int retval = 1;

   if (n.length != 4)
      retval = 0;

   if (n.bytes != 4)
      retval = 0;

   return retval;
}

int intialization_1() {
   NumString<uint16_t,8> n;

   int retval = 1;

   if (n.length != 8)
      retval = 0;

   if (n.bytes != 16)
      retval = 0;

   return retval;
}

int intialization_2() {
   NumString<uint32_t,11> n;

   int retval = 1;

   if (n.length != 11)
      retval = 0;

   if (n.bytes != 44)
      retval = 0;

   return retval;
}

int intialization_3() {
   NumString<uint64_t,3> n;

   int retval = 1;

   if (n.length != 3)
      retval = 0;

   if (n.bytes != 24)
      retval = 0;

   return retval;
}

int intialization_4() {
   NumString<float,27> n;

   int retval = 1;

   if (n.length != 27)
      retval = 0;

   if (n.bytes != 27 * sizeof(float))
      retval = 0;

   return retval;
}

int intialization_5() {
   NumString<double,83> n;

   int retval = 1;

   if (n.length != 83)
      retval = 0;

   if (n.bytes != 83 * sizeof(double))
      retval = 0;

   return retval;
}

int encode_0() {
   NumString<uint8_t,1> n;
   n.values[0] = 23;

   int retval = 1;

   size_t out = NumString<uint8_t,1>::encode(&n,NULL);

   if (out != 1)
      retval = 0;

   return retval;
}

int encode_1() {
   NumString<uint8_t,1> n;
   n.values[0] = 23;

   int retval = 1;

   uint8_t buf[1];
   size_t out = NumString<uint8_t,1>::encode(&n,buf);

   if (out != 1)
      retval = 0;

   if (buf[0] != 23)
      retval = 0;

   return retval;
}

/* from stackoverflow... */
int is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } e = { 0x01000000 };

    return e.c[0];
}

int encode_2() {
   NumString<uint16_t,12> n;
   n.values[0]  = 0x0123;
   n.values[1]  = 0x4567;
   n.values[2]  = 0x89ab;
   n.values[3]  = 0xcdef;
   n.values[4]  = 0xfedc;
   n.values[5]  = 0xba98;
   n.values[6]  = 0x7654;
   n.values[7]  = 0x3210;
   n.values[8]  = 0x0123;
   n.values[9]  = 0x4567;
   n.values[10] = 0x89ab;
   n.values[11] = 0xcdef;

   int retval = 1;

   uint8_t buf[sizeof(uint16_t) * 12];
   size_t out = NumString<uint16_t,12>::encode(&n,buf);

   if (out != sizeof(uint16_t) * 12)
      retval = 0;

   if (is_big_endian()) {
   if (buf[0] != 0x01)
      retval = 0;

   if (buf[1] != 0x23)
      retval = 0;

   if (buf[2] != 0x45)
      retval = 0;

   if (buf[3] != 0x67)
      retval = 0;

   if (buf[4] != 0x89)
      retval = 0;

   if (buf[5] != 0xab)
      retval = 0;

   if (buf[6] != 0xcd)
      retval = 0;

   if (buf[7] != 0xef)
      retval = 0;

   if (buf[8] != 0xfe)
      retval = 0;

   if (buf[9] != 0xdc)
      retval = 0;
   
   if (buf[10] != 0xba)
      retval = 0;

   if (buf[11] != 0x98)
      retval = 0;

   if (buf[12] != 0x76)
      retval = 0;

   if (buf[13] != 0x54)
      retval = 0;

   if (buf[14] != 0x32)
      retval = 0;

   if (buf[15] != 0x10)
      retval = 0;

   if (buf[16] != 0x01)
      retval = 0;

   if (buf[17] != 0x23)
      retval = 0;

   if (buf[18] != 0x45)
      retval = 0;

   if (buf[19] != 0x67)
      retval = 0;

   if (buf[20] != 0x89)
      retval = 0;

   if (buf[21] != 0xab)
      retval = 0;

   if (buf[22] != 0xcd)
      retval = 0;

   if (buf[23] != 0xef)
      retval = 0;
   }
   else {
   if (buf[0] != 0x23)
      retval = 0;

   if (buf[1] != 0x01)
      retval = 0;

   if (buf[2] != 0x67)
      retval = 0;

   if (buf[3] != 0x45)
      retval = 0;

   if (buf[4] != 0xab)
      retval = 0;

   if (buf[5] != 0x89)
      retval = 0;

   if (buf[6] != 0xef)
      retval = 0;

   if (buf[7] != 0xcd)
      retval = 0;

   if (buf[8] != 0xdc)
      retval = 0;

   if (buf[9] != 0xfe)
      retval = 0;
   
   if (buf[10] != 0x98)
      retval = 0;

   if (buf[11] != 0xba)
      retval = 0;

   if (buf[12] != 0x54)
      retval = 0;

   if (buf[13] != 0x76)
      retval = 0;

   if (buf[14] != 0x10)
      retval = 0;

   if (buf[15] != 0x32)
      retval = 0;

   if (buf[16] != 0x23)
      retval = 0;

   if (buf[17] != 0x01)
      retval = 0;

   if (buf[18] != 0x67)
      retval = 0;

   if (buf[19] != 0x45)
      retval = 0;

   if (buf[20] != 0xab)
      retval = 0;

   if (buf[21] != 0x89)
      retval = 0;

   if (buf[22] != 0xef)
      retval = 0;

   if (buf[23] != 0xcd)
      retval = 0;
   }

   return retval;
}

int encode_3() {
   NumString<double,3> n;
   n.values[0] = 1.0;
   n.values[1] = 25.0;
   n.values[2] = 0.25;

   int retval = 1;
   uint8_t buf[sizeof(double) * 3];

   size_t out = NumString<double,3>::encode(&n,buf);

   if (out != sizeof(double) * 3)
      retval = 0;

   double * res = (double *)buf;

   if (res[0] != 1.0)
      retval = 0;

   if (res[1] != 25.0)
      retval = 0;

   if (res[2] != 0.25)
      retval = 0;

   return retval;
}

int decode_0() {
   NumString<uint8_t,3> n;
   NumString<uint8_t,3> n_out;

   uint8_t buf[3];
   NumString<uint8_t,3>::encode(&n,buf);

   size_t out = NumString<uint8_t,3>::decode(&n_out,buf);

   int retval = 1;

   if (out != 3)
      retval = 0;

   return retval;
}

int decode_1() {
   NumString<uint8_t,3> n;
   NumString<uint8_t,3> n_out;
   n.values[0] = 0xe5;
   n.values[1] = 0xa4;
   n.values[2] = 0x32;

   uint8_t buf[3];
   NumString<uint8_t,3>::encode(&n,buf);

   size_t out = NumString<uint8_t,3>::decode(&n_out,buf);

   int retval = 1;

   if (out != 3)
      retval = 0;

   if (n_out.values[0] != 0xe5)
      retval = 0;

   if (n_out.values[1] != 0xa4)
      retval = 0;

   if (n_out.values[2] != 0x32)
      retval = 0;

   return retval;
}

int decode_2() {
   NumString<float,5> n, n_out;
   n.values[0] = 23423.238281;
   n.values[1] = -942.283977;
   n.values[2] = 409234.93750;
   n.values[3] = 48239024.0;
   n.values[4] = 120439.296875;

   int retval = 1;

   uint8_t buf[5 * sizeof(float)];
   NumString<float,5>::encode(&n,buf);

   size_t out = NumString<float,5>::decode(&n_out,buf);

   if (out != sizeof(float) * 5)
      retval = 0;

   if (n_out.values[0] - 23423.238281 > 0.001)
      retval = 0;

   if (n_out.values[1] - -942.283977 > 0.001)
      retval = 0;

   if (n_out.values[2] - 409234.9375 > 0.001)
      retval = 0;

   if (n_out.values[3] - 48239024.0 > 0.001)
      retval = 0;

   if (n_out.values[4] - 120439.296875 > 0.001)
      retval = 0;

   return retval;
}

int decode_3() {
   NumString<int,200> n, n_out;
   for (int i = 0; i < 200; ++i)
      n.values[i] = i;

   int retval = 1;

   uint8_t buf[200 * sizeof(int)];
   NumString<int,200>::encode(&n,buf);

   size_t out = NumString<int,200>::decode(&n_out,buf);

   if (out != sizeof(int) * 200)
      retval = 0;

   for (int i = 0; i < 200; ++i)
      if (n_out.values[i] != i)
         retval = 0;

   return retval;
}

int single_point_crossover_0() {
   NumString<int,2> p0, p1, c0, c1;
   p0.values[0] = 0xffffffff;
   p0.values[1] = 0xffffffff;
   p1.values[0] = 0x00000000;
   p1.values[1] = 0x00000000;

   NumString<int,2> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[1] = { 1 };

   NumStringSimulation<int,2>::single_point_crossover((NumString<int,2> **)&p,(NumString<int,2> **)&c,rnd);

   int retval = 1;

   if (c[0]->values[0] != 0xffffffff)
      retval = 0;

   if (c[0]->values[1] != 0x00000000)
      retval = 0;

   if (c[1]->values[0] != 0x00000000)
      retval = 0;

   if (c[1]->values[1] != 0xffffffff)
      retval = 0;

   return retval;
}

int single_point_crossover_1() {
   NumString<int,2> p0, p1, c0, c1;
   p0.values[0] = 0xffffffff;
   p0.values[1] = 0xffffffff;
   p1.values[0] = 0x00000000;
   p1.values[1] = 0x00000000;

   NumString<int,2> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[1] = { 0 };

   NumStringSimulation<int,2>::single_point_crossover((NumString<int,2> **)&p,(NumString<int,2> **)&c,rnd);

   int retval = 1;

   if (c[0]->values[0] != 0x00000000)
      retval = 0;

   if (c[0]->values[1] != 0x00000000)
      retval = 0;

   if (c[1]->values[0] != 0xffffffff)
      retval = 0;

   if (c[1]->values[1] != 0xffffffff)
      retval = 0;

   return retval;
}

int single_point_crossover_2() {
   NumString<int,5> p0, p1, c0, c1;
   p0.values[0] = 0x1a1a1a1a;
   p0.values[1] = 0x2b2b2b2b;
   p0.values[2] = 0x3c3c3c3c;
   p0.values[3] = 0x4d4d4d4d;
   p0.values[4] = 0x5f5f5f5f;
   p1.values[0] = 0x99999999;
   p1.values[1] = 0x88888888;
   p1.values[2] = 0x77777777;
   p1.values[3] = 0x66666666;
   p1.values[4] = 0x55555555;

   NumString<int,5> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[1] = { 2 };

   NumStringSimulation<int,5>::single_point_crossover((NumString<int,5> **)&p,(NumString<int,5> **)&c,rnd);

   int retval = 1;

   if (c[0]->values[0] != 0x1a1a1a1a)
      retval = 0;

   if (c[0]->values[1] != 0x2b2b2b2b)
      retval = 0;

   if (c[0]->values[2] != 0x77777777)
      retval = 0;

   if (c[0]->values[3] != 0x66666666)
      retval = 0;

   if (c[0]->values[4] != 0x55555555)
      retval = 0;

   if (c[1]->values[0] != 0x99999999)
      retval = 0;

   if (c[1]->values[1] != 0x88888888)
      retval = 0;

   if (c[1]->values[2] != 0x3c3c3c3c)
      retval = 0;

   if (c[1]->values[3] != 0x4d4d4d4d)
      retval = 0;

   if (c[1]->values[4] != 0x5f5f5f5f)
      retval = 0;

   return retval;
}

int single_point_crossover_3() {
   NumString<int,5> p0, p1, c0, c1;
   p0.values[0] = 0x1a1a1a1a;
   p0.values[1] = 0x2b2b2b2b;
   p0.values[2] = 0x3c3c3c3c;
   p0.values[3] = 0x4d4d4d4d;
   p0.values[4] = 0x5f5f5f5f;
   p1.values[0] = 0x99999999;
   p1.values[1] = 0x88888888;
   p1.values[2] = 0x77777777;
   p1.values[3] = 0x66666666;
   p1.values[4] = 0x55555555;

   NumString<int,5> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[1] = { 4 };

   NumStringSimulation<int,5>::single_point_crossover((NumString<int,5> **)&p,(NumString<int,5> **)&c,rnd);

   int retval = 1;

   if (c[0]->values[0] != 0x1a1a1a1a)
      retval = 0;

   if (c[0]->values[1] != 0x2b2b2b2b)
      retval = 0;

   if (c[0]->values[2] != 0x3c3c3c3c)
      retval = 0;

   if (c[0]->values[3] != 0x4d4d4d4d)
      retval = 0;

   if (c[0]->values[4] != 0x55555555)
      retval = 0;

   if (c[1]->values[0] != 0x99999999)
      retval = 0;

   if (c[1]->values[1] != 0x88888888)
      retval = 0;

   if (c[1]->values[2] != 0x77777777)
      retval = 0;

   if (c[1]->values[3] != 0x66666666)
      retval = 0;

   if (c[1]->values[4] != 0x5f5f5f5f)
      retval = 0;

   return retval;
}

int two_point_crossover_0() {
   NumString<int,3> p0, p1, c0, c1;
   p0.values[0] = 0xffffffff;
   p0.values[1] = 0xffffffff;
   p0.values[2] = 0xffffffff;
   p1.values[0] = 0x00000000;
   p1.values[1] = 0x00000000;
   p1.values[2] = 0x00000000;

   NumString<int,3> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[2] = { 1, 2 };

   NumStringSimulation<int,3>::two_point_crossover((NumString<int,3> **)&p,(NumString<int,3> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 0xffffffff)
      retval = 0;
   if (c0.values[1] != 0x00000000)
      retval = 0;
   if (c0.values[2] != 0xffffffff)
      retval = 0;

   if (c1.values[0] != 0x00000000)
      retval = 0;
   if (c1.values[1] != 0xffffffff)
      retval = 0;
   if (c1.values[2] != 0x00000000)
      retval = 0;

   return retval;
}

int two_point_crossover_1() {
   NumString<int,3> p0, p1, c0, c1;
   p0.values[0] = 0xffffffff;
   p0.values[1] = 0xffffffff;
   p0.values[2] = 0xffffffff;
   p1.values[0] = 0x00000000;
   p1.values[1] = 0x00000000;
   p1.values[2] = 0x00000000;

   NumString<int,3> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[2] = { 0, 2 };

   NumStringSimulation<int,3>::two_point_crossover((NumString<int,3> **)&p,(NumString<int,3> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 0x00000000)
      retval = 0;
   if (c0.values[1] != 0x00000000)
      retval = 0;
   if (c0.values[2] != 0xffffffff)
      retval = 0;

   if (c1.values[0] != 0xffffffff)
      retval = 0;
   if (c1.values[1] != 0xffffffff)
      retval = 0;
   if (c1.values[2] != 0x00000000)
      retval = 0;

   return retval;
}

int two_point_crossover_2() {
   NumString<int,3> p0, p1, c0, c1;
   p0.values[0] = 0xffffffff;
   p0.values[1] = 0xffffffff;
   p0.values[2] = 0xffffffff;
   p1.values[0] = 0x00000000;
   p1.values[1] = 0x00000000;
   p1.values[2] = 0x00000000;

   NumString<int,3> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[2] = { 2, 0 };

   NumStringSimulation<int,3>::two_point_crossover((NumString<int,3> **)&p,(NumString<int,3> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 0x00000000)
      retval = 0;
   if (c0.values[1] != 0x00000000)
      retval = 0;
   if (c0.values[2] != 0xffffffff)
      retval = 0;

   if (c1.values[0] != 0xffffffff)
      retval = 0;
   if (c1.values[1] != 0xffffffff)
      retval = 0;
   if (c1.values[2] != 0x00000000)
      retval = 0;

   return retval;
}

int two_point_crossover_3() {
   NumString<int,3> p0, p1, c0, c1;
   p0.values[0] = 0xffffffff;
   p0.values[1] = 0xffffffff;
   p0.values[2] = 0xffffffff;
   p1.values[0] = 0x00000000;
   p1.values[1] = 0x00000000;
   p1.values[2] = 0x00000000;

   NumString<int,3> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[2] = { 1, 3 };

   NumStringSimulation<int,3>::two_point_crossover((NumString<int,3> **)&p,(NumString<int,3> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 0xffffffff)
      retval = 0;
   if (c0.values[1] != 0x00000000)
      retval = 0;
   if (c0.values[2] != 0x00000000)
      retval = 0;

   if (c1.values[0] != 0x00000000)
      retval = 0;
   if (c1.values[1] != 0xffffffff)
      retval = 0;
   if (c1.values[2] != 0xffffffff)
      retval = 0;

   return retval;
}

int uniform_crossover_0() {
   NumString<int,3> p0, p1, c0;
   p0.values[0] = 0xffffffff;
   p0.values[1] = 0xffffffff;
   p0.values[2] = 0xffffffff;
   p1.values[0] = 0x00000000;
   p1.values[1] = 0x00000000;
   p1.values[2] = 0x00000000;

   NumString<int,3> * p[2], * c[1];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; 

   uint64_t rnd[3] = { 1, 1, 1 };

   NumStringSimulation<int,3>::uniform_crossover((NumString<int,3> **)&p,(NumString<int,3> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 0xffffffff)
      retval = 0;
   if (c0.values[1] != 0xffffffff)
      retval = 0;
   if (c0.values[2] != 0xffffffff)
      retval = 0;

   return retval;
}

int uniform_crossover_1() {
   NumString<int,3> p0, p1, c0;
   p0.values[0] = 0xffffffff;
   p0.values[1] = 0xffffffff;
   p0.values[2] = 0xffffffff;
   p1.values[0] = 0x00000000;
   p1.values[1] = 0x00000000;
   p1.values[2] = 0x00000000;

   NumString<int,3> * p[2], * c[1];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; 

   uint64_t rnd[3] = { 0, 0, 0 };

   NumStringSimulation<int,3>::uniform_crossover((NumString<int,3> **)&p,(NumString<int,3> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 0x00000000)
      retval = 0;
   if (c0.values[1] != 0x00000000)
      retval = 0;
   if (c0.values[2] != 0x00000000)
      retval = 0;

   return retval;
}

int uniform_crossover_2() {
   NumString<int,3> p0, p1, c0;
   p0.values[0] = 0xffffffff;
   p0.values[1] = 0xffffffff;
   p0.values[2] = 0xffffffff;
   p1.values[0] = 0x00000000;
   p1.values[1] = 0x00000000;
   p1.values[2] = 0x00000000;

   NumString<int,3> * p[2], * c[1];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; 

   uint64_t rnd[3] = { 0, 1, 0 };

   NumStringSimulation<int,3>::uniform_crossover((NumString<int,3> **)&p,(NumString<int,3> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 0x00000000)
      retval = 0;
   if (c0.values[1] != 0xffffffff)
      retval = 0;
   if (c0.values[2] != 0x00000000)
      retval = 0;

   return retval;
}

int uniform_crossover_3() {
   NumString<int,3> p0, p1, c0;
   p0.values[0] = 0xffffffff;
   p0.values[1] = 0xffffffff;
   p0.values[2] = 0xffffffff;
   p1.values[0] = 0x00000000;
   p1.values[1] = 0x00000000;
   p1.values[2] = 0x00000000;

   NumString<int,3> * p[2], * c[1];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; 

   uint64_t rnd[3] = { 1, 0, 1 };

   NumStringSimulation<int,3>::uniform_crossover((NumString<int,3> **)&p,(NumString<int,3> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 0xffffffff)
      retval = 0;
   if (c0.values[1] != 0x00000000)
      retval = 0;
   if (c0.values[2] != 0xffffffff)
      retval = 0;

   return retval;
}

int shuffle_crossover_0() {
   NumString<int,8> p0, p1, c0, c1;
   for (int i = 0; i < 8; ++i)
      p0.values[i] = ~(p1.values[i] = 0xffffffff);

   NumString<int,8> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 4 };

   NumStringSimulation<int,8>::shuffle_crossover((NumString<int,8> **)&p,(NumString<int,8> **)&c,rnd);

   int retval = 1;

   if ((c[0]->values[0] & c[0]->values[1] & c[0]->values[2] & c[0]->values[3]) != 0x00000000)
      retval = 0;
   if ((c[0]->values[4] & c[0]->values[5] & c[0]->values[6] & c[0]->values[7]) != 0xffffffff)
      retval = 0;
   if ((c[1]->values[0] & c[1]->values[1] & c[1]->values[2] & c[1]->values[3]) != 0xffffffff)
      retval = 0;
   if ((c[1]->values[4] & c[1]->values[5] & c[1]->values[6] & c[1]->values[7]) != 0x00000000)
      retval = 0;

   return retval;
}

int shuffle_crossover_1() {
   NumString<int,8> p0, p1, c0, c1;
   for (int i = 0; i < 8; ++i)
      p0.values[i] = ~(p1.values[i] = 0xffffffff);

   NumString<int,8> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[9] = { 7, 6, 5, 4, 4, 5, 6, 7, 4 };

   NumStringSimulation<int,8>::shuffle_crossover((NumString<int,8> **)&p,(NumString<int,8> **)&c,rnd);

   int retval = 1;

   if ((c[0]->values[0] & c[0]->values[1] & c[0]->values[2] & c[0]->values[3]) != 0xffffffff)
      retval = 0;
   if ((c[0]->values[4] & c[0]->values[5] & c[0]->values[6] & c[0]->values[7]) != 0x00000000)
      retval = 0;
   if ((c[1]->values[0] & c[1]->values[1] & c[1]->values[2] & c[1]->values[3]) != 0x00000000)
      retval = 0;
   if ((c[1]->values[4] & c[1]->values[5] & c[1]->values[6] & c[1]->values[7]) != 0xffffffff)
      retval = 0;

   return retval;
}

int shuffle_crossover_2() {
   NumString<int,8> p0, p1, c0, c1;
   for (int i = 0; i < 8; ++i)
      p1.values[i] = ~(p0.values[i] = 0xffffffff);

   NumString<int,8> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[9] = { 0, 1, 2, 3, 1, 3, 3, 7, 4 };

   NumStringSimulation<int,8>::shuffle_crossover((NumString<int,8> **)&p,(NumString<int,8> **)&c,rnd);

   int retval = 1;

   if ((c[0]->values[0] & c[1]->values[1] & c[0]->values[2] & c[1]->values[3]) != 0xffffffff)
      retval = 0;
   if ((c[0]->values[4] & c[1]->values[5] & c[0]->values[6] & c[1]->values[7]) != 0xffffffff)
      retval = 0;
   if ((c[1]->values[0] | c[0]->values[1] | c[1]->values[2] | c[0]->values[3]) != 0x00000000)
      retval = 0;
   if ((c[1]->values[4] | c[0]->values[5] | c[1]->values[6] | c[0]->values[7]) != 0x00000000)
      retval = 0;

   return retval;
}

int shuffle_crossover_3() {
   NumString<int,8> p0, p1, c0, c1;
   for (int i = 0; i < 8; ++i)
      p1.values[i] = ~(p0.values[i] = 0xffffffff);

   NumString<int,8> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[9] = { 7, 6, 5, 4, 1, 3, 3, 7, 4 };

   NumStringSimulation<int,8>::shuffle_crossover((NumString<int,8> **)&p,(NumString<int,8> **)&c,rnd);

   int retval = 1;

   if ((c[1]->values[0] & c[0]->values[1] & c[1]->values[2] & c[0]->values[3]) != 0xffffffff)
      retval = 0;
   if ((c[1]->values[4] & c[0]->values[5] & c[1]->values[6] & c[0]->values[7]) != 0xffffffff)
      retval = 0;
   if ((c[0]->values[0] | c[1]->values[1] | c[0]->values[2] | c[1]->values[3]) != 0x00000000)
      retval = 0;
   if ((c[0]->values[4] | c[1]->values[5] | c[0]->values[6] | c[1]->values[7]) != 0x00000000)
      retval = 0;

   return retval;
}

int precedence_preservative_crossover_0() {
   NumString<int,8> p0, p1, c0;
   for (int i = 0; i < 8; ++i)
      p0.values[i] = p1.values[i] = i;

   NumString<int,8> * p[2], * c[1];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; 

   uint64_t * rnd = NULL;

   NumStringSimulation<int,8>::precedence_preservative_crossover((NumString<int,8> **)&p,(NumString<int,8> **)&c,rnd);

   int retval = 1;

   for (int i = 0; i < 8; ++i)
      if (i != c0.values[i])
         retval = 0;

   return retval;
}

int precedence_preservative_crossover_1() {
   NumString<int,8> p0, p1, c0;
   p0.values[0] = 0; p1.values[0] = 7;
   p0.values[1] = 1; p1.values[1] = 6;
   p0.values[2] = 2; p1.values[2] = 5;
   p0.values[3] = 3; p1.values[3] = 4;
   p0.values[4] = 4; p1.values[4] = 3;
   p0.values[5] = 5; p1.values[5] = 2;
   p0.values[6] = 6; p1.values[6] = 1;
   p0.values[7] = 7; p1.values[7] = 0;

   NumString<int,8> * p[2], * c[1];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; 

   uint64_t * rnd = NULL;

   NumStringSimulation<int,8>::precedence_preservative_crossover((NumString<int,8> **)&p,(NumString<int,8> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 0)
      retval = 0;
   if (c0.values[1] != 7)
      retval = 0;
   if (c0.values[2] != 1)
      retval = 0;
   if (c0.values[3] != 6)
      retval = 0;
   if (c0.values[4] != 2)
      retval = 0;
   if (c0.values[5] != 5)
      retval = 0;
   if (c0.values[6] != 3)
      retval = 0;
   if (c0.values[7] != 4)
      retval = 0;

   return retval;
}

int precedence_preservative_crossover_2() {
   NumString<int,8> p0, p1, c0;
   p0.values[0] = 0; p1.values[0] = 7;
   p0.values[1] = 1; p1.values[1] = 6;
   p0.values[2] = 2; p1.values[2] = 5;
   p0.values[3] = 3; p1.values[3] = 0;
   p0.values[4] = 4; p1.values[4] = 1;
   p0.values[5] = 5; p1.values[5] = 2;
   p0.values[6] = 6; p1.values[6] = 3;
   p0.values[7] = 7; p1.values[7] = 4;

   NumString<int,8> * p[2], * c[1];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; 

   uint64_t * rnd = NULL;

   NumStringSimulation<int,8>::precedence_preservative_crossover((NumString<int,8> **)&p,(NumString<int,8> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 0)
      retval = 0;
   if (c0.values[1] != 7)
      retval = 0;
   if (c0.values[2] != 1)
      retval = 0;
   if (c0.values[3] != 6)
      retval = 0;
   if (c0.values[4] != 2)
      retval = 0;
   if (c0.values[5] != 5)
      retval = 0;
   if (c0.values[6] != 3)
      retval = 0;
   if (c0.values[7] != 4)
      retval = 0;

   return retval;
}

int precedence_preservative_crossover_3() {
   NumString<int,8> p0, p1, c0;
   p0.values[0] = 0; p1.values[0] = 7;
   p0.values[1] = 1; p1.values[1] = 6;
   p0.values[2] = 2; p1.values[2] = 5;
   p0.values[3] = 7; p1.values[3] = 4;
   p0.values[4] = 6; p1.values[4] = 3;
   p0.values[5] = 5; p1.values[5] = 2;
   p0.values[6] = 3; p1.values[6] = 1;
   p0.values[7] = 4; p1.values[7] = 0;

   NumString<int,8> * p[2], * c[1];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; 

   uint64_t * rnd = NULL;

   NumStringSimulation<int,8>::precedence_preservative_crossover((NumString<int,8> **)&p,(NumString<int,8> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 0)
      retval = 0;
   if (c0.values[1] != 7)
      retval = 0;
   if (c0.values[2] != 1)
      retval = 0;
   if (c0.values[3] != 6)
      retval = 0;
   if (c0.values[4] != 2)
      retval = 0;
   if (c0.values[5] != 5)
      retval = 0;
   if (c0.values[6] != 3)
      retval = 0;
   if (c0.values[7] != 4)
      retval = 0;

   return retval;
}

int ordered_crossover_0() {
   NumString<int,8> p0, p1, c0, c1;
   for (int i = 0; i < 8; ++i)
      p1.values[i] = p0.values[i] = i;

   NumString<int,8> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[9] = { 2,5 };

   NumStringSimulation<int,8>::ordered_crossover((NumString<int,8> **)&p,(NumString<int,8> **)&c,rnd);

   int retval = 1;

   for (int i = 0; i < 8; ++i)
      if (c0.values[i] != i || c1.values[i] != i)
         retval = 0;

   return retval;
}

int ordered_crossover_1() {
   NumString<int,6> p0, p1, c0, c1;
   p0.values[0] = 4; p1.values[0] = 2;
   p0.values[1] = 2; p1.values[1] = 3;
   p0.values[2] = 1; p1.values[2] = 1;
   p0.values[3] = 3; p1.values[3] = 4;
   p0.values[4] = 6; p1.values[4] = 5;
   p0.values[5] = 5; p1.values[5] = 6;

   NumString<int,6> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[9] = { 2,4 };

   NumStringSimulation<int,6>::ordered_crossover((NumString<int,6> **)&p,(NumString<int,6> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 4)
      retval = 0;
   if (c0.values[1] != 2)
      retval = 0;
   if (c0.values[2] != 3)
      retval = 0;
   if (c0.values[3] != 1)
      retval = 0;
   if (c0.values[4] != 6)
      retval = 0;
   if (c0.values[5] != 5)
      retval = 0;
   if (c1.values[0] != 2)
      retval = 0;
   if (c1.values[1] != 3)
      retval = 0;
   if (c1.values[2] != 4)
      retval = 0;
   if (c1.values[3] != 1)
      retval = 0;
   if (c1.values[4] != 5)
      retval = 0;
   if (c1.values[5] != 6)
      retval = 0;

   return retval;
}

int ordered_crossover_2() {
   NumString<int,6> p0, p1, c0, c1;
   p0.values[0] = 6; p1.values[0] = 2;
   p0.values[1] = 2; p1.values[1] = 3;
   p0.values[2] = 1; p1.values[2] = 5;
   p0.values[3] = 3; p1.values[3] = 4;
   p0.values[4] = 4; p1.values[4] = 1;
   p0.values[5] = 5; p1.values[5] = 6;

   NumString<int,6> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[9] = { 4,6 };

   NumStringSimulation<int,6>::ordered_crossover((NumString<int,6> **)&p,(NumString<int,6> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 6)
      retval = 0;
   if (c0.values[1] != 2)
      retval = 0;
   if (c0.values[2] != 1)
      retval = 0;
   if (c0.values[3] != 3)
      retval = 0;
   if (c0.values[4] != 5)
      retval = 0;
   if (c0.values[5] != 4)
      retval = 0;
   if (c1.values[0] != 2)
      retval = 0;
   if (c1.values[1] != 3)
      retval = 0;
   if (c1.values[2] != 5)
      retval = 0;
   if (c1.values[3] != 4)
      retval = 0;
   if (c1.values[4] != 6)
      retval = 0;
   if (c1.values[5] != 1)
      retval = 0;

   return retval;
}

int ordered_crossover_3() {
   NumString<int,6> p0, p1, c0, c1;
   p0.values[0] = 3; p1.values[0] = 6;
   p0.values[1] = 2; p1.values[1] = 5;
   p0.values[2] = 1; p1.values[2] = 4;
   p0.values[3] = 4; p1.values[3] = 1;
   p0.values[4] = 5; p1.values[4] = 2;
   p0.values[5] = 6; p1.values[5] = 3;

   NumString<int,6> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[9] = { 0,3 };

   NumStringSimulation<int,6>::ordered_crossover((NumString<int,6> **)&p,(NumString<int,6> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 1)
      retval = 0;
   if (c0.values[1] != 2)
      retval = 0;
   if (c0.values[2] != 3)
      retval = 0;
   if (c0.values[3] != 4)
      retval = 0;
   if (c0.values[4] != 5)
      retval = 0;
   if (c0.values[5] != 6)
      retval = 0;
   if (c1.values[0] != 4)
      retval = 0;
   if (c1.values[1] != 5)
      retval = 0;
   if (c1.values[2] != 6)
      retval = 0;
   if (c1.values[3] != 1)
      retval = 0;
   if (c1.values[4] != 2)
      retval = 0;
   if (c1.values[5] != 3)
      retval = 0;

   return retval;
}

int partially_matched_crossover_0() {
   NumString<int,6> p0, p1, c0, c1;
   for (int i = 0; i < 6; ++i)
      p0.values[i] = p1.values[i] = i;

   NumString<int,6> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[9] = { 0,3 };

   NumStringSimulation<int,6>::partially_matched_crossover((NumString<int,6> **)&p,(NumString<int,6> **)&c,rnd);

   int retval = 1;

   for (int i = 0; i < 6; ++i)
      if (p0.values[i] != i || p1.values[i] != i)
         retval = 0;

   return retval;
}

int partially_matched_crossover_1() {
   NumString<int,10> p0, p1, c0, c1;
   p0.values[0] = 9; p1.values[0] = 8;
   p0.values[1] = 8; p1.values[1] = 7;
   p0.values[2] = 4; p1.values[2] = 1;
   p0.values[3] = 5; p1.values[3] = 2;
   p0.values[4] = 6; p1.values[4] = 3;
   p0.values[5] = 7; p1.values[5] =10;
   p0.values[6] = 1; p1.values[6] = 9;
   p0.values[7] = 3; p1.values[7] = 5;
   p0.values[8] = 2; p1.values[8] = 4;
   p0.values[9] =10; p1.values[9] = 6;

   NumString<int,10> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[9] = { 3,6 };

   NumStringSimulation<int,10>::partially_matched_crossover((NumString<int,10> **)&p,(NumString<int,10> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 9 ||
       c0.values[1] != 8 ||
       c0.values[2] != 4 ||
       c0.values[3] != 2 ||
       c0.values[4] != 3 ||
       c0.values[5] !=10 ||
       c0.values[6] != 1 ||
       c0.values[7] != 5 ||
       c0.values[8] != 6 ||
       c0.values[9] != 7)
      retval = 0;

   if (c1.values[0] != 8 ||
       c1.values[1] !=10 ||
       c1.values[2] != 1 ||
       c1.values[3] != 5 ||
       c1.values[4] != 6 ||
       c1.values[5] != 7 ||
       c1.values[6] != 9 ||
       c1.values[7] != 2 ||
       c1.values[8] != 4 ||
       c1.values[9] != 3)
      retval = 0;

   return retval;
}

int partially_matched_crossover_2() {
   NumString<int,10> p0, p1, c0, c1;
   p0.values[0] = 9; p1.values[0] = 8;
   p0.values[1] = 8; p1.values[1] = 7;
   p0.values[2] = 4; p1.values[2] = 1;
   p0.values[3] = 5; p1.values[3] = 2;
   p0.values[4] = 6; p1.values[4] = 3;
   p0.values[5] = 7; p1.values[5] =10;
   p0.values[6] = 1; p1.values[6] = 9;
   p0.values[7] = 3; p1.values[7] = 5;
   p0.values[8] = 2; p1.values[8] = 4;
   p0.values[9] =10; p1.values[9] = 6;

   NumString<int,10> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[9] = { 6,3 };

   NumStringSimulation<int,10>::partially_matched_crossover((NumString<int,10> **)&p,(NumString<int,10> **)&c,rnd);

   int retval = 1;

   if (c0.values[0] != 9 ||
       c0.values[1] != 8 ||
       c0.values[2] != 4 ||
       c0.values[3] != 2 ||
       c0.values[4] != 3 ||
       c0.values[5] !=10 ||
       c0.values[6] != 1 ||
       c0.values[7] != 5 ||
       c0.values[8] != 6 ||
       c0.values[9] != 7)
      retval = 0;

   if (c1.values[0] != 8 ||
       c1.values[1] !=10 ||
       c1.values[2] != 1 ||
       c1.values[3] != 5 ||
       c1.values[4] != 6 ||
       c1.values[5] != 7 ||
       c1.values[6] != 9 ||
       c1.values[7] != 2 ||
       c1.values[8] != 4 ||
       c1.values[9] != 3)
      retval = 0;

   return retval;
}

int partially_matched_crossover_3() {
   NumString<int,6> p0, p1, c0, c1;
   for (int i = 0; i < 6; ++i)
      p0.values[i] = p1.values[i] = -i;

   NumString<int,6> * p[2], * c[2];
   p[0] = &p0; p[1] = &p1;
   c[0] = &c0; c[1] = &c1;

   uint64_t rnd[9] = { 0,3 };

   NumStringSimulation<int,6>::partially_matched_crossover((NumString<int,6> **)&p,(NumString<int,6> **)&c,rnd);

   int retval = 1;

   for (int i = 0; i < 6; ++i)
      if (p0.values[i] != -i || p1.values[i] != -i)
         retval = 0;

   return retval;
}

int noise_0() {
   NumString<int,1> n;
   n.values[0] = 1;

   auto generator = []{
      return 1;
   };

   uint64_t rnd[2] = { 0, 0 };
   auto noise = NumStringSimulation<int,1>::noise(generator,0.99);
   noise(&n,rnd);

   int retval = 1;

   if (n.values[0] != 2)
      retval = 0;

   return retval;
}

int noise_1() {
   NumString<int,1> n;
   n.values[0] = 1;

   auto generator = []{
      return 1;
   };

   uint64_t rnd[2] = { (ULLONG_MAX / 2) + 1 };
   auto noise = NumStringSimulation<int,1>::noise(generator,0.5);
   noise(&n,rnd);

   int retval = 1;

   if (n.values[0] != 1)
      retval = 0;

   return retval;
}

int noise_2() {
   NumString<int,2> n;
   n.values[0] = 1;
   n.values[1] = 1;

   auto generator = []{
      return 1;
   };

   uint64_t rnd[3] = { (ULLONG_MAX / 2) - 1, ULLONG_MAX, 1 };
   auto noise = NumStringSimulation<int,2>::noise(generator,0.5);
   noise(&n,rnd);

   int retval = 1;

   if (n.values[0] != 1)
      retval = 0;
   if (n.values[1] != 2)
      retval = 0;

   return retval;
}

int noise_3() {
   NumString<int,2> n;
   n.values[0] = 1;
   n.values[1] = 1;

   auto generator = []{
      return 5;
   };

   uint64_t rnd[5] = { 0, 0, 1, 0 };
   auto noise = NumStringSimulation<int,2>::noise(generator,0.5);
   noise(&n,rnd);

   int retval = 1;

   if (n.values[0] != 6)
      retval = 0;
   if (n.values[1] != 6)
      retval = 0;

   return retval;
}

int interchange_0() {
   NumString<int,2> n;
   n.values[0] = 2;
   n.values[1] = 1;

   uint64_t rnd[6] = { 0, ULLONG_MAX, 1, 0 };
   auto interchange = NumStringSimulation<int,2>::interchange(0.5);
   interchange(&n,rnd);

   int retval = 1;

   if (n.values[0] != 1)
      retval = 0;
   if (n.values[1] != 2)
      retval = 0;

   return retval;
}

int interchange_1() {
   NumString<int,2> n;
   n.values[0] = 2;
   n.values[1] = 1;

   uint64_t rnd[6] = { 0, 0, 1, 0, 0, 1 };
   auto interchange = NumStringSimulation<int,2>::interchange(0.5);
   interchange(&n,rnd);

   int retval = 1;

   if (n.values[0] != 2)
      retval = 0;
   if (n.values[1] != 1)
      retval = 0;

   return retval;
}

int interchange_2() {
   NumString<int,2> n;
   n.values[0] = 2;
   n.values[1] = 1;

   uint64_t rnd[6] = { 0, 0, 1, 1, 0, 0 };
   auto interchange = NumStringSimulation<int,2>::interchange(0.5);
   interchange(&n,rnd);

   int retval = 1;

   if (n.values[0] != 2)
      retval = 0;
   if (n.values[1] != 1)
      retval = 0;

   return retval;
}

int interchange_3() {
   NumString<int,2> n;
   n.values[0] = 2;
   n.values[1] = 1;

   uint64_t rnd[5] = { 0, ULLONG_MAX, 1, 1 };
   auto interchange = NumStringSimulation<int,2>::interchange(0.5);
   interchange(&n,rnd);

   int retval = 1;

   if (n.values[0] != 2)
      retval = 0;
   if (n.values[1] != 1)
      retval = 0;

   return retval;
}

}

}


