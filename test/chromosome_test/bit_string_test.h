
#ifndef __RHIZAR16_BIT_STRING_TEST__

#define __RHIZAR16_BIT_STRING_TEST__
#include <stdint.h>
#include <stdlib.h>
#include "bit_string.h"

namespace Rhizar16 {

namespace TestBitString {

int initialization_0();
int initialization_1();
int initialization_4();
int initialization_64();
int initialization_128();
int initialization_5000();

int hamming_distance_0_0();
int hamming_distance_1_1_1();
int hamming_distance_1_1_0();
int hamming_distance_4_4_1();
int hamming_distance_4_4_3();
int hamming_distance_4_4_4();
int hamming_distance_64_64_12();
int hamming_distance_64_64_18();
int hamming_distance_64_64_47();
int hamming_distance_64_64_64();
int hamming_distance_128_128_64();
int hamming_distance_128_128_128();
int hamming_distance_5000_5000_1014();
int hamming_distance_5000_5000_5000();

int randomize_0();
int randomize_1();

template<unsigned N>
class BitStringSimulation {
public:
   static void single_point_crossover(BitString<N> ** const parents, BitString<N> ** children, uint64_t * rnd);
   static void two_point_crossover(BitString<N> ** const parents, BitString<N> ** children, uint64_t * rnd);
   static void uniform_crossover(BitString<N> ** const parents, BitString<N> ** children, uint64_t * rnd);
   static void three_parent_crossover(BitString<N> ** const parents, BitString<N> ** children, uint64_t * rnd);
   static void shuffle_crossover(BitString<N> ** const parents, BitString<N> ** children, uint64_t * rnd);
   static void flip(BitString<N> * chromosome, uint64_t * rnd, uint num, uint den);
   static void interchange(BitString<N> * chromosome, uint64_t * rnd, uint num, uint den);
};

int single_point_crossover_0();
int single_point_crossover_1();
int single_point_crossover_2();
int single_point_crossover_3();

int two_point_crossover_0();
int two_point_crossover_1();
int two_point_crossover_2();
int two_point_crossover_3();
int two_point_crossover_4();
int two_point_crossover_5();
int two_point_crossover_6();
int two_point_crossover_7();
int two_point_crossover_8();

int uniform_crossover_0();
int uniform_crossover_1();
int uniform_crossover_2();
int uniform_crossover_3();

int three_parent_crossover_0();
int three_parent_crossover_1();
int three_parent_crossover_2();
int three_parent_crossover_3();
int three_parent_crossover_4();
int three_parent_crossover_5();
int three_parent_crossover_6();

int shuffle_crossover_0();
int shuffle_crossover_1();
int shuffle_crossover_2();
int shuffle_crossover_3();
int shuffle_crossover_4();

int flip_0();
int flip_1();
int flip_2();
int flip_3();
int flip_4();

int interchange_0();
int interchange_1();
int interchange_2();
int interchange_3();
int interchange_4();

}

}

#endif
