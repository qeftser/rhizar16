
#ifndef __RHIZAR16_POPULATION_TEST__

#define __RHIZAR16_POPULATION_TEST__
#include "selection.h"
#include "chromosome.h"
#include "population.h"

namespace Rhizar16 {

class TestPopulation {
public:

   static int initialization();

   static int grow_population_0();
   static int grow_population_1();
   static int grow_population_2();

   static int try_expand_vector_0();
   static int try_expand_vector_1();
   static int try_expand_vector_2();
   static int try_expand_vector_3();
   static int try_expand_vector_4();

   static int sort_population_0();
   static int sort_population_1();
   static int sort_population_2();

   static int set_fitness_0();
   static int set_fitness_1();

   static int evaluate_fitness_0();
   static int evaluate_fitness_1();
   static int evaluate_fitness_2();

   static int advance_0();
   static int advance_1();

   static int retrieve_0();
   static int retrieve_1();
   static int retrieve_2();

   static int finished_0();
   static int finished_1();
   static int finished_2();

   static int population_0();

   static int poplen_0();
   static int poplen_1();

   static int set_selection_0();
   static int set_selection_1();

   static int add_before_0();
   static int add_before_1();
   static int add_before_2();
   static int add_before_3();

   static int add_after_0();
   static int add_after_1();
   static int add_after_2();
   static int add_after_3();

   static int initialize_0();

   static int perform_evolution_0();
   static int perform_evolution_1();
   static int perform_evolution_2();
   static int perform_evolution_3();
   static int perform_evolution_4();
   static int perform_evolution_5();

   static int simulate_0();
   static int simulate_1();
   static int simulate_2();
   static int simulate_3();
   static int simulate_4();
   static int simulate_5();
   static int simulate_6();
   static int simulate_7();
   static int simulate_8();

   static int tp_simulate_0();
   static int tp_simulate_1();
   static int tp_simulate_2();
   static int tp_simulate_3();
   static int tp_simulate_4();
   static int tp_simulate_5();
   static int tp_simulate_6();
   static int tp_simulate_7();
   static int tp_simulate_8();

   static int reset_0();

   static int initialize_1();

};

}

#endif
