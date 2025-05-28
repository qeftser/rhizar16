
#include <cstdio>
#include <ctime>
#include "bit_string_test.h"
#include "uniform_rand_test.h"
#include "population_test.h"
#include "selection_test.h"

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
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_5000_5000_1014());
   __RHIZAR16_TEST(Rhizar16::TestBitString::hamming_distance_5000_5000_5000());
   __RHIZAR16_TEST(Rhizar16::TestBitString::randomize_0());
   __RHIZAR16_TEST(Rhizar16::TestBitString::randomize_1());

   /* ===========================================================
    * Population round 1 tests
    * =========================================================== */
   __RHIZAR16_TEST(Rhizar16::TestPopulation::initialization());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::population_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::poplen_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::poplen_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::grow_population_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::grow_population_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::grow_population_2());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::try_expand_vector_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::try_expand_vector_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::try_expand_vector_2());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::try_expand_vector_3());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::try_expand_vector_4());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::sort_population_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::sort_population_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::sort_population_2());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::set_fitness_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::set_fitness_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::evaluate_fitness_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::evaluate_fitness_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::evaluate_fitness_2());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::advance_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::advance_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::retrieve_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::retrieve_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::retrieve_2());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::finished_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::finished_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::finished_2());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::add_before_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::add_before_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::add_before_2());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::add_before_3());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::add_after_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::add_after_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::add_after_2());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::add_after_3());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::initialize_0());

   /* ===========================================================
    * Selection tests
    * =========================================================== */

   __RHIZAR16_TEST(Rhizar16::TestSelection::intialization_0());
   __RHIZAR16_TEST(Rhizar16::TestSelection::intialization_1());
   __RHIZAR16_TEST(Rhizar16::TestSelection::selection_0());
   __RHIZAR16_TEST(Rhizar16::TestSelection::selection_1());
   __RHIZAR16_TEST(Rhizar16::TestSelection::selection_2());
   __RHIZAR16_TEST(Rhizar16::TestSelection::selection_3());
   __RHIZAR16_TEST(Rhizar16::TestSelection::selection_4());
   __RHIZAR16_TEST(Rhizar16::TestSelection::selection_5());
   __RHIZAR16_TEST(Rhizar16::TestSelection::as_function_0());
   __RHIZAR16_TEST(Rhizar16::TestSelection::as_function_1());
   __RHIZAR16_TEST(Rhizar16::TestSelection::as_function_2());
   __RHIZAR16_TEST(Rhizar16::TestSelection::as_function_3());
   __RHIZAR16_TEST(Rhizar16::TestSelection::as_function_4());
   __RHIZAR16_TEST(Rhizar16::TestSelection::as_function_5());

   /* ===========================================================
    * Population round 2 tests
    * =========================================================== */
   __RHIZAR16_TEST(Rhizar16::TestPopulation::set_selection_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::set_selection_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::perform_evolution_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::perform_evolution_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::perform_evolution_2());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::perform_evolution_3());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::perform_evolution_4());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::perform_evolution_5());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::simulate_0());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::simulate_1());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::simulate_2());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::simulate_3());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::simulate_4());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::simulate_5());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::simulate_6());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::simulate_7());
   __RHIZAR16_TEST(Rhizar16::TestPopulation::simulate_8());

   double elapsed = (double)(clock() - tStart) / CLOCKS_PER_SEC;

   printf("============================================================================\n");
   printf("Ran %d tests in %f seconds. Results: %d passing, %d failing\n",
           total_tests,elapsed,passed_tests,total_tests - passed_tests);
   printf("============================================================================\n");

   return 0;
}
