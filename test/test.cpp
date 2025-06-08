
#include "bit_string_test.h"
#include "uniform_rand_test.h"
#include "population_test.h"
#include "concurrent_queue_test.h"
#include "selection_test.h"
#include "file_opts_test.h"
#include "wired_test.h"

#include <stdio.h>
#include <time.h>

int total_tests = 0;
int passed_tests = 0;
int ignored_tests = 0;

#define __RHIZAR16_TEST(funcall)                                                           \
do {                                                                                       \
   total_tests += 1;                                                                       \
   int res = (funcall);                                                                    \
   if (res == 1)                                                                           \
      passed_tests += 1;                                                                   \
   else if (res)                                                                           \
      ignored_tests += 1;                                                                  \
   printf("[%s]: %s\n",res ?                                                               \
                      (res == 1 ? "\033[32mPASSED\033[0m" : "\033[33mIGNORE\033[0m") :     \
                      "\033[31mFAILED\033[0m", #funcall);                                  \
} while(0)


int main(void) {

   Rhizar16::print_logo();

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

   /* ===========================================================
    * BitString reproduction tests
    * =========================================================== */
   __RHIZAR16_TEST(Rhizar16::TestBitString::single_point_crossover_0());
   __RHIZAR16_TEST(Rhizar16::TestBitString::single_point_crossover_1());
   __RHIZAR16_TEST(Rhizar16::TestBitString::single_point_crossover_2());
   __RHIZAR16_TEST(Rhizar16::TestBitString::single_point_crossover_3());
   __RHIZAR16_TEST(Rhizar16::TestBitString::two_point_crossover_0());
   __RHIZAR16_TEST(Rhizar16::TestBitString::two_point_crossover_1());
   __RHIZAR16_TEST(Rhizar16::TestBitString::two_point_crossover_2());
   __RHIZAR16_TEST(Rhizar16::TestBitString::two_point_crossover_3());
   __RHIZAR16_TEST(Rhizar16::TestBitString::two_point_crossover_4());
   __RHIZAR16_TEST(Rhizar16::TestBitString::two_point_crossover_5());
   __RHIZAR16_TEST(Rhizar16::TestBitString::two_point_crossover_6());
   __RHIZAR16_TEST(Rhizar16::TestBitString::two_point_crossover_7());
   __RHIZAR16_TEST(Rhizar16::TestBitString::two_point_crossover_8());
   __RHIZAR16_TEST(Rhizar16::TestBitString::uniform_crossover_0());
   __RHIZAR16_TEST(Rhizar16::TestBitString::uniform_crossover_1());
   __RHIZAR16_TEST(Rhizar16::TestBitString::uniform_crossover_2());
   __RHIZAR16_TEST(Rhizar16::TestBitString::uniform_crossover_3());
   __RHIZAR16_TEST(Rhizar16::TestBitString::three_parent_crossover_0());
   __RHIZAR16_TEST(Rhizar16::TestBitString::three_parent_crossover_1());
   __RHIZAR16_TEST(Rhizar16::TestBitString::three_parent_crossover_2());
   __RHIZAR16_TEST(Rhizar16::TestBitString::three_parent_crossover_3());
   __RHIZAR16_TEST(Rhizar16::TestBitString::three_parent_crossover_4());
   __RHIZAR16_TEST(Rhizar16::TestBitString::three_parent_crossover_5());
   __RHIZAR16_TEST(Rhizar16::TestBitString::three_parent_crossover_6());
   __RHIZAR16_TEST(Rhizar16::TestBitString::shuffle_crossover_0());
   __RHIZAR16_TEST(Rhizar16::TestBitString::shuffle_crossover_1());
   __RHIZAR16_TEST(Rhizar16::TestBitString::shuffle_crossover_2());
   __RHIZAR16_TEST(Rhizar16::TestBitString::shuffle_crossover_3());
   __RHIZAR16_TEST(Rhizar16::TestBitString::shuffle_crossover_4());
   __RHIZAR16_TEST(Rhizar16::TestBitString::flip_0());
   __RHIZAR16_TEST(Rhizar16::TestBitString::flip_1());
   __RHIZAR16_TEST(Rhizar16::TestBitString::flip_2());
   __RHIZAR16_TEST(Rhizar16::TestBitString::flip_3());
   __RHIZAR16_TEST(Rhizar16::TestBitString::flip_4());
   __RHIZAR16_TEST(Rhizar16::TestBitString::interchange_0());
   __RHIZAR16_TEST(Rhizar16::TestBitString::interchange_1());
   __RHIZAR16_TEST(Rhizar16::TestBitString::interchange_2());
   __RHIZAR16_TEST(Rhizar16::TestBitString::interchange_3());
   __RHIZAR16_TEST(Rhizar16::TestBitString::interchange_4());

   /* ===========================================================
    * FileOpts tests
    * =========================================================== */
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::initialization_0());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_0());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_1());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_2());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_3());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_4());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_5());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_6());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_7());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_8());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_9());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_a());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_b());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_c());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_d());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_e());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_f());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_g());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_h());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_i());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_j());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_k());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_l());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_m());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_n());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_o());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_p());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::load_q());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_int_0());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_int_1());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_int_2());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_int_3());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_int_4());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_int_5());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_int_6());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_flt_0());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_flt_1());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_flt_2());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_flt_3());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_flt_4());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_flt_5());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_flt_6());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_str_0());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_str_1());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_str_2());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_str_3());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_str_4());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::getopt_str_5());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::has_section_0());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::has_section_1());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::has_section_2());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::has_section_3());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::has_key_0());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::has_key_1());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::has_key_2());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::has_key_3());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::has_key_4());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::has_key_5());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::save_0());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::save_1());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::save_2());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::save_3());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::save_4());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::save_5());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::save_6());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::save_7());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::save_8());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::save_9());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::save_a());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::save_b());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::collect_sections_0());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::collect_sections_1());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::collect_sections_2());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::collect_keys_0());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::collect_keys_1());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::collect_keys_2());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::collect_keys_3());
   __RHIZAR16_TEST(Rhizar16::TestFileOpts::collect_keys_4());

   /* ===========================================================
    * Wired tests
    * =========================================================== */
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_initialization_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_initialization_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_initialization_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_initialization_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_initialization_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_initialization_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_open_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_open_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_open_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_open_3());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_open_4());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_open_5());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_start_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_start_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_start_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_close_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_close_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_close_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_connect_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_connect_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_connect_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_connect_3());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_connect_4());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_connect_5());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_close_3());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_close_4());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_close_5());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_close_6());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_send_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_send_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_send_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_is_live_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_is_live_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_is_live_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_is_live_3());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_is_live_4());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_is_live_5());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_is_live_6());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_link_is_live_7());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_get_ready_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_get_ready_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_get_ready_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_wait_ready_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_wait_ready_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_get_ready_3());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_wait_ready_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_wait_ready_3());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_get_closed_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_get_closed_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_get_closed_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_get_closed_3());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_clean_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_clean_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_clean_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_clean_3());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_close_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_close_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_clean_4());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_recv_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_recv_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_recv_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_recv_3());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_recv_4());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_recv_5());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_recv_6());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_send_link_recv_0());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_send_link_recv_1());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_send_link_recv_2());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_send_link_recv_3());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_send_link_recv_4());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_send_link_recv_5());
   __RHIZAR16_TEST(Rhizar16::TestWired::wired_server_send_link_recv_6());

   /* ===========================================================
    * ConcurrentQueue tests
    * =========================================================== */
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::initialization());
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::empty_0());
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::push_0());
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::empty_1());
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::pop_0());
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::push_1());
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::empty_2());
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::push_2());
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::pop_1());
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::push_3());
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::pop_2());
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::push_4());
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::pop_3());
   __RHIZAR16_TEST(Rhizar16::TestConcurrentQueue::usage());

   double elapsed = (double)(clock() - tStart) / CLOCKS_PER_SEC;

   printf("============================================================================\n");
   printf("Ran %d tests in %f seconds. Results: %d passing, %d failing\n",
           total_tests,elapsed,passed_tests,total_tests - passed_tests - ignored_tests);
   printf("============================================================================\n");

   return 0;
}
