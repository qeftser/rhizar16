
#include <cstdio>
#include <ctime>
#include "bit_string_test.h"
#include "uniform_rand_test.h"

int total_tests = 0;
int passed_tests = 0;

#define __RHIZAR16_TEST(funcall)                                                           \
do {                                                                                       \
   total_tests += 1;                                                                       \
   int res = (funcall);                                                                    \
   if (res)                                                                                \
      passed_tests += 1;                                                                   \
   printf("[%s]: %s\n",res ? "\033[32mPASSED\033[0m" : "\033[31mFAILED\033[0m", #funcall); \
} while(0)

int main(void) {

   int tStart = clock();

   /* ===========================================================
    * UniformRand tests
    * =========================================================== */

   __RHIZAR16_TEST(Rhizar16::TestUniformRand::initialization());
   __RHIZAR16_TEST(Rhizar16::TestUniformRand::initialization_seed0());
   __RHIZAR16_TEST(Rhizar16::TestUniformRand::initialization_seed_0x43022432());
   __RHIZAR16_TEST(Rhizar16::TestUniformRand::random());
   __RHIZAR16_TEST(Rhizar16::TestUniformRand::random_seed0());
   __RHIZAR16_TEST(Rhizar16::TestUniformRand::random_seed_0x43022432());

   /* ===========================================================
    * BitString tests
    * =========================================================== */
   __RHIZAR16_TEST(Rhizar16::TestBitString::initialization_0());
   __RHIZAR16_TEST(Rhizar16::TestBitString::initialization_1());
   __RHIZAR16_TEST(Rhizar16::TestBitString::initialization_4());
   __RHIZAR16_TEST(Rhizar16::TestBitString::initialization_64());
   __RHIZAR16_TEST(Rhizar16::TestBitString::initialization_128());
   __RHIZAR16_TEST(Rhizar16::TestBitString::initialization_5000());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_0_0());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_1_1_1());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_1_1_0());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_4_4_1());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_4_4_3());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_4_4_4());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_64_64_12());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_64_64_18());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_64_64_47());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_64_64_64());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_128_128_64());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_128_128_128());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_5000_5000_1000());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_5000_5000_5000());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_0_1());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_0_128());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_64_128());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_128_5000());
   __RHIZAR16_TEST(Rhizar16::TestBitString::randomize_0());
   __RHIZAR16_TEST(Rhizar16::TestBitString::randomize_1());


   double elapsed = (double)(clock() - tStart) / CLOCKS_PER_SEC;

   printf("============================================================================\n");
   printf("Ran %d tests in %f seconds. Results: %d passing, %d failing\n",
           total_tests,elapsed,passed_tests,total_tests - passed_tests);
   printf("============================================================================\n");

   return 0;
}
