
#ifndef __RHIZAR16_NUM_STRING_TEST__

#define __RHIZAR16_NUM_STRING_TEST__
#include <stdint.h>
#include <stdlib.h>
#include "num_string.h"

namespace Rhizar16 {

namespace TestNumString {

int intialization_0();
int intialization_1();
int intialization_2();
int intialization_3();
int intialization_4();
int intialization_5();

int encode_0();
int encode_1();
int encode_2();
int encode_3();

int decode_0();
int decode_1();
int decode_2();
int decode_3();

template<typename T, unsigned N>
class NumStringSimulation {
public:
   static void single_point_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children, uint64_t * rnd);
   static void two_point_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children, uint64_t * rnd);
   static void uniform_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children, uint64_t * rnd);
   static void shuffle_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children, uint64_t * rnd);
   static void precedence_preservative_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children, uint64_t * rnd);
   static void ordered_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children, uint64_t * rnd);
   static void partially_matched_crossover(NumString<T,N> ** const parents, NumString<T,N> ** children, uint64_t * rnd);
   static std::function<void(NumString<T,N> *, uint64_t *)> noise(std::function<T()> generator, double probability);
   static std::function<void(NumString<T,N> *, uint64_t *)> interchange(double probability);
};

int single_point_crossover_0();
int single_point_crossover_1();
int single_point_crossover_2();
int single_point_crossover_3();

int two_point_crossover_0();
int two_point_crossover_1();
int two_point_crossover_2();
int two_point_crossover_3();

int uniform_crossover_0();
int uniform_crossover_1();
int uniform_crossover_2();
int uniform_crossover_3();

int shuffle_crossover_0();
int shuffle_crossover_1();
int shuffle_crossover_2();
int shuffle_crossover_3();

int precedence_preservative_crossover_0();
int precedence_preservative_crossover_1();
int precedence_preservative_crossover_2();
int precedence_preservative_crossover_3();

int ordered_crossover_0();
int ordered_crossover_1();
int ordered_crossover_2();
int ordered_crossover_3();

int partially_matched_crossover_0();
int partially_matched_crossover_1();
int partially_matched_crossover_2();
int partially_matched_crossover_3();

int noise_0();
int noise_1();
int noise_2();
int noise_3();

int interchange_0();
int interchange_1();
int interchange_2();
int interchange_3();

}

}

#endif
