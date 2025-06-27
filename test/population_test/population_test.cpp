
#include "population_test.h"
#include "selection_test.h"
#include "population.h"
#include "population_options.h"
#include "uniform_rand.h"
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

namespace Rhizar16 {

int TestPopulation::initialization() {

   PopulationOptions pop;
   pop.population_size = 100;
   pop.maximum_generation = 100;
   pop.maximum_elapsed = 100;
   pop.tracking_mode = PopulationOption::TrackingMode::TRACKING_MODE_NONE;
   pop.elitism_count = 0;

   Population<int> p = Population<int>(&pop);

   int retval = 1;

   if (p.time_elapsed != 0.0)
      retval = 0;

   if (p.generation != 0)
      retval = 0;

   if (p.generation_A.end != 100)
      retval = 0;

   if (p.generation_A.length != 110)
      retval = 0;

   if (p.generation_B.end != 100)
      retval = 0;

   if (p.generation_B.length != 110)
      retval = 0;

   if (p.curr_generation != &p.generation_A)
      retval = 0;

   if (p.next_generation != &p.generation_B)
      retval = 0;

   if (p.before.end != 0)
      retval = 0;

   if (p.before.data != 0)
      retval = 0;

   if (p.after.end != 0)
      retval = 0;

   if (p.after.data != 0)
      retval = 0;

   if (p.evolution != NULL)
      retval = 0;

   if (p.fitness != NULL)
      retval = 0;

   if (p.options != &pop)
      retval = 0;

   return retval;
}

int TestPopulation::population_0() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   int retval = 1;

   if (p.population() != p.curr_generation->data)
      retval = 0;

   return retval;
}

int TestPopulation::poplen_0() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   int retval = 1;

   if (p.poplen() != 100)
      retval = 0;

   return retval;
}

int TestPopulation::poplen_1() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   int retval = 1;

   pop.population_size = 200;

   if (p.poplen() != 200)
      retval = 0;

   return retval;
}


int TestPopulation::grow_population_0() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.grow_population(p.curr_generation,200);

   int retval = 1;

   if (p.curr_generation->length != 200)
      retval = 0;

   for (int i = 0; i < 200; ++i) {

      if (!p.population()[i] || 
          !p.population()[i]->value ||
           p.population()[i]->fitness != 0.0)
         retval = 0;
   }

   return retval;
}

int TestPopulation::grow_population_1() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.grow_population(p.curr_generation,20);

   int retval = 1;

   if (p.curr_generation->length != 110)
      retval = 0;

   if (p.curr_generation->end != 100)
      retval = 0;

   for (int i = 0; i < 110; ++i) {

      if (!p.population()[i] || 
          !p.population()[i]->value ||
           p.population()[i]->fitness != 0.0)
         retval = 0;
   }

   return retval;
}

int TestPopulation::grow_population_2() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.grow_population(p.curr_generation,200);

   int retval = 1;

   if (p.curr_generation->length != 200)
      retval = 0;

   for (int i = 0; i < 200; ++i) {

      if (!p.population()[i] || 
          !p.population()[i]->value ||
           p.population()[i]->fitness != 0.0)
         retval = 0;
   }

   return retval;
}

int TestPopulation::try_expand_vector_0() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.try_expand_vector(&p.before,1,sizeof(Population<int>::manipulator));

   int retval = 1;

   if (p.before.length != 1)
      retval = 0;

   if (p.before.data == NULL)
      retval = 0;

   return retval;
}

int TestPopulation::try_expand_vector_1() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.try_expand_vector(&p.before,1,sizeof(Population<int>::manipulator));
   p.try_expand_vector(&p.before,20,sizeof(Population<int>::manipulator));

   int retval = 1;

   if (p.before.length != 1)
      retval = 0;

   if (p.before.data == NULL)
      retval = 0;

   return retval;
}

int TestPopulation::try_expand_vector_2() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.try_expand_vector(&p.before,20,sizeof(Population<int>::manipulator));
   p.before.end = 20;
   p.try_expand_vector(&p.before,10,sizeof(Population<int>::manipulator));

   int retval = 1;

   if (p.before.length != 20)
      retval = 0;

   if (p.before.data == NULL)
      retval = 0;

   p.before.end = 0;

   return retval;
}

int TestPopulation::try_expand_vector_3() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.try_expand_vector(&p.before,20,sizeof(Population<int>::manipulator));
   p.before.end = 20;
   p.try_expand_vector(&p.before,40,sizeof(Population<int>::manipulator));

   int retval = 1;

   if (p.before.length != 40)
      retval = 0;

   if (p.before.data == NULL)
      retval = 0;

   p.before.end = 0;

   return retval;
}

int TestPopulation::try_expand_vector_4() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.try_expand_vector(&p.before,0,sizeof(Population<int>::manipulator));

   int retval = 1;

   if (p.before.length != 0)
      retval = 0;

   if (p.before.data != NULL)
      retval = 0;

   return retval;
}

int TestPopulation::sort_population_0() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 100; ++i) {
      ((Chromosome<int> **)p.curr_generation->data)[i]->fitness = i;
   }

   p.sort_population();

   int retval = 1;

   int last = 101;

   for (int i = 0; i < 100; ++i) {
      int curr = ((Chromosome<int> **)p.curr_generation->data)[i]->fitness;
      if (last < curr) {
         retval = 0;
         break;
      }
      last = curr;
   }

   return retval;
}

int TestPopulation::sort_population_1() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 100; ++i) {
      ((Chromosome<int> **)p.curr_generation->data)[i]->fitness = 100 - i;
   }

   p.sort_population();

   int retval = 1;

   int last = 101;

   for (int i = 0; i < 100; ++i) {
      int curr = ((Chromosome<int> **)p.curr_generation->data)[i]->fitness;
      if (last < curr) {
         retval = 0;
         break;
      }
      last = curr;
   }

   return retval;
}

int TestPopulation::sort_population_2() {

   UniformRand r;

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 100; ++i) {
      ((Chromosome<int> **)p.curr_generation->data)[i]->fitness = r.random() % 1000;
   }

   p.sort_population();

   int retval = 1;

   unsigned long last = ULONG_MAX;

   for (int i = 0; i < 100; ++i) {
      unsigned long curr = ((Chromosome<int> **)p.curr_generation->data)[i]->fitness;
      if (last < curr) {
         retval = 0;
         break;
      }
      last = curr;
   }

   return retval;
}

double test_population_dummy_fitness_eval(const int * chromosome) {

   return (double)(*chromosome * 10.0);

}

int TestPopulation::set_fitness_0() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.set_fitness(test_population_dummy_fitness_eval);

   int retval = 1;

   if (p.fitness == nullptr)
      retval = 0;

   return retval;
}

int TestPopulation::set_fitness_1() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_fitness(nullptr);

   int retval = 1;

   if (p.fitness != nullptr)
      retval = 0;

   return retval;
}

int TestPopulation::evaluate_fitness_0() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 100; ++i)
      *(p.population()[i]->value) = 0.0;

   p.set_fitness(test_population_dummy_fitness_eval);
   p.evaluate_fitness();

   int retval = 1;

   for (uint32_t i = 0; i < p.poplen(); ++i) {
      if (p.population()[i]->fitness != 0.0)
         retval = 0;
   }

   return retval;
}

int TestPopulation::evaluate_fitness_1() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   for (uint32_t i = 0; i < p.poplen(); ++i) {
      *(p.population()[i]->value) = i;
   }

   p.set_fitness(test_population_dummy_fitness_eval);
   p.evaluate_fitness();

   int retval = 1;

   for (uint32_t i = 0; i < p.poplen(); ++i) {
      if (p.population()[i]->fitness != i * 10)
         retval = 0;
   }

   return retval;
}

int TestPopulation::evaluate_fitness_2() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   for (uint32_t i = 0; i < p.poplen(); ++i) {
      *(p.population()[i]->value) = 100 - i;
   }

   p.set_fitness(test_population_dummy_fitness_eval);
   p.evaluate_fitness();

   int retval = 1;

   for (uint32_t i = 0; i < p.poplen(); ++i) {
      if ((fabs(p.population()[i]->fitness - ((100 - i) * 10))) > 0.01)
         retval = 0;
   }

   return retval;
}

int TestPopulation::advance_0() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   int retval = 1;

   p.advance();

   if (p.generation != 1)
      retval = 0;

   if (p.time_elapsed <= 0.0)
      retval = 0;

   if (p.curr_generation != &p.generation_B)
      retval = 0;
   
   if (p.next_generation != &p.generation_A)
      retval = 0;

   return retval;
}

int TestPopulation::advance_1() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   int retval = 1;

   p.advance();
   p.advance();

   if (p.generation != 2)
      retval = 0;

   if (p.time_elapsed <= 0.0)
      retval = 0;

   if (p.curr_generation != &p.generation_A)
      retval = 0;
   
   if (p.next_generation != &p.generation_B)
      retval = 0;

   return retval;
}

int TestPopulation::retrieve_0() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.next_generation->end = 0;

   Chromosome<int> * ret = p.retrieve();

   int retval = 1;

   if (ret != ((Chromosome<int> **)p.next_generation->data)[0])
      retval = 0;

   if (p.next_generation->end != 1)
      retval = 0;

   return retval;
}

int TestPopulation::retrieve_1() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.next_generation->end = 0;

   p.retrieve();
   p.retrieve();
   p.retrieve();
   Chromosome<int> * ret = p.retrieve();

   int retval = 1;

   if (ret != ((Chromosome<int> **)p.next_generation->data)[3])
      retval = 0;

   if (p.next_generation->end != 4)
      retval = 0;

   return retval;
}

int TestPopulation::retrieve_2() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.next_generation->end = 0;

   for (int i = 0; i < 120; ++i)
      p.retrieve();

   Chromosome<int> * ret = p.retrieve();

   int retval = 1;

   if (p.next_generation->length != 130)
      retval = 0;

   if (p.next_generation->end != 121)
      retval = 0;

   if (ret != ((Chromosome<int> **)p.next_generation->data)[120])
      retval = 0;

   return retval;
}

int TestPopulation::finished_0() {

   PopulationOptions pop;
   pop.population_size = 100;
   pop.maximum_generation = 10;
   pop.maximum_elapsed = 1;

   Population<int> p = Population<int>(&pop);

   int retval = 1;

   if (p.finished())
      retval = 0;

   return retval;
}

int TestPopulation::finished_1() {

   PopulationOptions pop;
   pop.population_size = 100;
   pop.maximum_generation = 10;
   pop.maximum_elapsed = 1;

   Population<int> p = Population<int>(&pop);

   int retval = 1;

   p.generation = 11;

   if (!p.finished())
      retval = 0;

   return retval;
}

int TestPopulation::finished_2() {

   PopulationOptions pop;
   pop.population_size = 100;
   pop.maximum_generation = 10;
   pop.maximum_elapsed = 1;

   Population<int> p = Population<int>(&pop);

   int retval = 1;

   p.time_elapsed = 2.0;

   if (!p.finished())
      retval = 0;

   return retval;
}

int test_population_add_before_dummy_func(Chromosome<int> ** pop, int length, void * arg) {

   long addr = (long long)(arg);

   Chromosome<int> ** head = pop;

   for (int i = 0; i < length; ++i)
      *((*head)->value) += addr;

   return 0;
}

int TestPopulation::add_before_0() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   int addr = 5;

   p.add_before(0,test_population_add_before_dummy_func,(void *)&addr);

   int retval = 1;

   if (p.before.end != 1)
      retval = 0;

   if (p.before.length != __RHIZAR16_POPULATION_BORDERFUNC_EXPANSION_STEP__)
      retval = 0;

   if (p.before.data == NULL)
      retval = 0;

   if (((Population<int>::manipulator **)p.before.data)[0]->func !=
       test_population_add_before_dummy_func)
      retval = 0;

   return retval;
}

int TestPopulation::add_before_1() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   int addr0 = 8, addr5 = 0, addr8 = 5;

   p.add_before(0,test_population_add_before_dummy_func,(void *)&addr0);
   p.add_before(5,test_population_add_before_dummy_func,(void *)&addr5);
   p.add_before(8,test_population_add_before_dummy_func,(void *)&addr8);

   int retval = 1;

   if (p.before.end != 3)
      retval = 0;

   if (p.before.length != __RHIZAR16_POPULATION_BORDERFUNC_EXPANSION_STEP__)
      retval = 0;

   if (p.before.data == NULL)
      retval = 0;

   if (((Population<int>::manipulator **)p.before.data)[0]->weight != 8)
      retval = 0;

   if (((Population<int>::manipulator **)p.before.data)[1]->weight != 5)
      retval = 0;

   if (((Population<int>::manipulator **)p.before.data)[2]->weight != 0)
      retval = 0;

   return retval;
}

int TestPopulation::add_before_2() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   int addr = 5;

   for (int i = 0; i < 20; ++i) {

      p.add_before(i,test_population_add_before_dummy_func,(void *)&addr);

   }

   int retval = 1;

   if (p.before.end != 20)
      retval = 0;

   if (p.before.length != 20)
      retval = 0;

   if (p.before.data == NULL)
      retval = 0;

   for (int i = 0; i < 20; ++i) {

      if (((Population<int>::manipulator **)p.before.data)[i]->weight != 19 - i) {
         retval = 0;
         break;
      }
   }

   return retval;
}

int TestPopulation::add_before_3() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   int addr = 5;

   for (int i = 0; i < 20; ++i) {

      p.add_before(20 - i,test_population_add_before_dummy_func,(void *)&addr);

   }

   int retval = 1;

   if (p.before.end != 20)
      retval = 0;

   if (p.before.length != 20)
      retval = 0;

   if (p.before.data == NULL)
      retval = 0;

   for (int i = 0; i < 20; ++i) {

      if (((Population<int>::manipulator **)p.before.data)[i]->weight != 20 - i) {
         retval = 0;
         break;
      }
   }

   return retval;
}

int TestPopulation::add_after_0() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   int addr = 5;

   p.add_after(0,test_population_add_before_dummy_func,(void *)&addr);

   int retval = 1;

   if (p.after.end != 1)
      retval = 0;

   if (p.after.length != __RHIZAR16_POPULATION_BORDERFUNC_EXPANSION_STEP__)
      retval = 0;

   if (p.after.data == NULL)
      retval = 0;

   if (((Population<int>::manipulator **)p.after.data)[0]->func !=
       test_population_add_before_dummy_func)
      retval = 0;

   return retval;
}

int TestPopulation::add_after_1() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   int addr0 = 8, addr5 = 0, addr8 = 5;

   p.add_after(0,test_population_add_before_dummy_func,(void *)&addr0);
   p.add_after(5,test_population_add_before_dummy_func,(void *)&addr5);
   p.add_after(8,test_population_add_before_dummy_func,(void *)&addr8);

   int retval = 1;

   if (p.after.end != 3)
      retval = 0;

   if (p.after.length != __RHIZAR16_POPULATION_BORDERFUNC_EXPANSION_STEP__)
      retval = 0;

   if (p.after.data == NULL)
      retval = 0;

   if (((Population<int>::manipulator **)p.after.data)[0]->weight != 8)
      retval = 0;

   if (((Population<int>::manipulator **)p.after.data)[1]->weight != 5)
      retval = 0;

   if (((Population<int>::manipulator **)p.after.data)[2]->weight != 0)
      retval = 0;

   return retval;
}

int TestPopulation::add_after_2() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   int addr = 5;

   for (int i = 0; i < 20; ++i) {

      p.add_after(i,test_population_add_before_dummy_func,(void *)&addr);

   }

   int retval = 1;

   if (p.after.end != 20)
      retval = 0;

   if (p.after.length != 20)
      retval = 0;

   if (p.after.data == NULL)
      retval = 0;

   for (int i = 0; i < 20; ++i) {

      if (((Population<int>::manipulator **)p.after.data)[i]->weight != 19 - i) {
         retval = 0;
         break;
      }
   }

   return retval;
}

int TestPopulation::add_after_3() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   int addr = 5;

   for (int i = 0; i < 20; ++i) {

      p.add_after(20 - i,test_population_add_before_dummy_func,(void *)&addr);

   }

   int retval = 1;

   if (p.after.end != 20)
      retval = 0;

   if (p.after.length != 20)
      retval = 0;

   if (p.after.data == NULL)
      retval = 0;

   for (int i = 0; i < 20; ++i) {

      if (((Population<int>::manipulator **)p.after.data)[i]->weight != 20 - i) {
         retval = 0;
         break;
      }
   }

   return retval;
}

void test_population_dummy_setup_func(int * chromosome) {

   *chromosome = 5;

}

int TestPopulation::initialize_0() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   p.set_fitness(test_population_dummy_fitness_eval);
   p.initialize(test_population_dummy_setup_func);

   int retval = 1;

   for (uint32_t i = 0; i < p.poplen(); ++i) {
      if (p.population()[i]->fitness != 50.0) {
         retval = 0;
         break;
      }
   }

   return retval;
}

int TestPopulation::set_selection_0() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,2,3> s(test_selection_reproduction_dummy_func_2_3,
                                 test_selection_mutation_dummy_func);

   p.set_selection(s.as_function());

   int retval = 1;

   if (p.evolution == nullptr)
      retval = 0;

   return retval;
}

int TestPopulation::set_selection_1() {

   PopulationOptions pop;
   pop.population_size = 100;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,2,3> s(test_selection_reproduction_dummy_func_2_3,
                                 test_selection_mutation_dummy_func);

   p.set_selection(s.as_function());
   p.set_selection(nullptr);

   int retval = 1;

   if (p.evolution != nullptr)
      retval = 0;

   return retval;
}

int TestPopulation::perform_evolution_0() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_selection_mutation_dummy_func);

   p.set_selection(s.as_function());

   p.perform_evolution(10);
   p.advance();

   int retval = 1;

   for (int i = 0; i < 5; ++i) {
      if (*(p.population()[i])->value != 1) {
         retval = 0;
         break;
      }
   }

   return retval;
}

int TestPopulation::perform_evolution_1() {
   
   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,1,2> s(test_selection_reproduction_dummy_func_1_2,
                                 test_selection_mutation_dummy_func);

   p.set_selection(s.as_function());

   pop.population_size = 20;
   p.perform_evolution(10);
   p.advance();

   int retval = 1;

   for (int i = 0; i < 20; ++i) {
      if (i % 2) {
         if (*(p.population()[i])->value != -1) {
            retval = 0;
            break;
         }
      }
      else {
         if (*(p.population()[i])->value != 1) {
            retval = 0;
            break;
         }
      }
   }

   return retval;
}

int TestPopulation::perform_evolution_2() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,2,1> s(test_selection_reproduction_dummy_func_2_1,
                                 test_selection_mutation_dummy_func);

   pop.population_size = 7;
   p.set_selection(s.as_function());
   p.perform_evolution(10);
   p.advance();

   int retval = 1;

   for (int i = 0; i < 7; ++i) {
      if (*(p.population()[i])->value != 6) {
         retval = 0;
         break;
      }
   }

   return retval;
}

int TestPopulation::perform_evolution_3() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,5,1> s(test_selection_reproduction_dummy_func_5_1,
                                 test_selection_mutation_dummy_func);

   pop.population_size = 12;
   p.set_evolution(s.as_function());
   p.perform_evolution(10);
   p.advance();

   int retval = 1;

   for (int i = 0; i < 12; ++i) {
      if (*(p.population()[i])->value != 7) {
         retval = 0;
         break;
      }
   }

   return retval;
}

int TestPopulation::perform_evolution_4() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,1,5> s(test_selection_reproduction_dummy_func_1_5,
                                 test_selection_mutation_dummy_func);
   
   pop.population_size = 33;
   p.set_evolution(s.as_function());
   p.perform_evolution(10);
   p.advance();

   int retval = 1;

   for (int i = 0; i < 33; ++i) {
      if ((((i % 5) + 1) * 3) % 2) {
         if (*(p.population()[i])->value != ((((i % 5) + 1) * 3)) / 2) {
            retval = 0;
            break;
         }
      }
      else {
         if (*(p.population()[i])->value != ((((i % 5) + 1) * 3))) {
            retval = 0;
            break;
         }
      }
   }

   return retval;
}

int TestPopulation::perform_evolution_5() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,2,3> s(test_selection_reproduction_dummy_func_2_3,
                                 test_selection_mutation_dummy_func);

   pop.population_size = 1000;
   p.set_evolution(s.as_function());
   p.perform_evolution(10);
   p.advance();

   int retval = 1;

   for (int i = 0; i < 1000; ++i) {
      if (i % 3) {
         if (*(p.population()[i])->value != 0) {
            retval = 0;
            break;
         }
      }
      else {
         if (*(p.population()[i])->value != 6) {
            retval = 0;
            break;
         }
      }
   }

   return retval;
}

void test_population_count_10(int * chromosome) {
   static int count = 0;
   *chromosome = count;
   count = (count + 1) % 10;
}

int TestPopulation::simulate_0() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_selection_mutation_dummy_func);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.initialize(test_population_count_10);
   p.sort_population();
   p.simulate(1);

   int retval = 1;

   for (int i = 0; i < 10; ++i) {
      if (p.population()[i]->fitness != 40.0 || *(p.population()[i]->value) != 4)
         retval = 0;
   }

   return retval;
}

int TestPopulation::simulate_1() {

   PopulationOptions pop;
   pop.population_size = 10;
   pop.maximum_generation = 100;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_selection_mutation_dummy_func);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.initialize(test_population_count_10);
   p.sort_population();
   p.simulate();

   int retval = 1;

   for (int i = 0; i < 10; ++i) {
      if (p.population()[i]->fitness != 40.0 || *(p.population()[i]->value) != 4)
         retval = 0;
   }

   if (p.generation != 101)
      retval = 0;

   return retval;
}

int TestPopulation::simulate_2() {

   PopulationOptions pop;
   pop.population_size = 10;
   pop.maximum_elapsed = 0.01;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_selection_mutation_dummy_func);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.initialize(test_population_count_10);
   p.sort_population();
   p.simulate();

   int retval = 1;

   for (int i = 0; i < 10; ++i) {
      if (p.population()[i]->fitness != 40.0 || *(p.population()[i]->value) != 4)
         retval = 0;
   }

   if (p.time_elapsed < pop.maximum_elapsed)
      retval = 0;

   return retval;
}

void test_population_mutation_none(int * chromosome) {
   (void)chromosome;
}

int test_population_multiply_2(Chromosome<int> ** pop, int length, void * arg) {
   (void)arg;
   for (int i = 0; i < length; ++i) {
      *(pop[i]->value) *= 2;
   }
   return 0;
}

int test_population_add_1(Chromosome<int> ** pop, int length, void * arg) {
   (void)arg;
   for (int i = 0; i < length; ++i) {
      *(pop[i]->value) += 1;
   }
   return 0;
}

int TestPopulation::simulate_3() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_population_mutation_none);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.add_before(5,test_population_multiply_2,NULL);
   p.add_before(10,test_population_add_1,NULL);

   p.initialize(test_population_dummy_setup_func);
   p.simulate(1);

   int retval = 1;

   for (int i = 0; i < 10; ++i) {
      if (p.population()[i]->fitness != 120.0 || *(p.population()[i]->value) != 12)
         retval = 0;
   }

   return retval;
}

int TestPopulation::simulate_4() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_population_mutation_none);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.add_after(5,test_population_add_1,NULL);
   p.add_after(10,test_population_multiply_2,NULL);

   p.initialize(test_population_dummy_setup_func);
   p.simulate(1);

   int retval = 1;

   for (int i = 0; i < 10; ++i) {
      if (p.population()[i]->fitness != 110.0 || *(p.population()[i]->value) != 11)
         retval = 0;
   }

   return retval;
}

int test_population_set_poplen_5(Chromosome<int> ** pop, int length, void * arg) {
   (void)pop;
   (void)length;
   (void)arg;
   return 5;
}

int TestPopulation::simulate_5() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   LastOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                test_population_mutation_none);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.add_before(0,test_population_set_poplen_5,NULL);

   p.initialize(test_population_dummy_setup_func);

   *((Chromosome<int> **)p.curr_generation->data)[4]->value = 1;
   for (int i = 5; i < 10; ++i)
      *((Chromosome<int> **)p.curr_generation->data)[i]->value = 0;

   p.simulate(1);

   int retval = 1;

   for (int i = 0; i < 10; ++i) {
      if (p.population()[i]->fitness != 10.0 || *(p.population()[i]->value) != 1)
         retval = 0;
   }

   return retval;
}

int TestPopulation::simulate_6() {

   PopulationOptions pop;
   pop.population_size = 10;
   pop.elitism_count = 3;

   Population<int> p = Population<int>(&pop);

   LastOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                test_population_mutation_none);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.add_before(0,test_population_set_poplen_5,NULL);

   p.initialize(test_population_dummy_setup_func);

   for (int i = 4; i < 10; ++i)
      *((Chromosome<int> **)p.curr_generation->data)[i]->value = 1;

   p.simulate(1);

   int retval = 1;

   for (int i = 0; i < 3; ++i) {
      if (p.population()[i]->fitness != 50.0 || *(p.population()[i]->value) != 5)
         retval = 0;
   }

   for (int i = 3; i < 10; ++i) {
      if (p.population()[i]->fitness != 10.0 || *(p.population()[i]->value) != 1)
         retval = 0;
   }

   return retval;
}

int TestPopulation::simulate_7() {

   PopulationOptions pop;
   pop.population_size = 10;
   pop.max_fitness = 40.0;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_population_mutation_none);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.initialize(test_population_dummy_setup_func);

   p.simulate();

   int retval = 1;

   if (p.max_fitness < 40.0)
      retval = 0;

   return retval;
}

int TestPopulation::simulate_8() {

   PopulationOptions pop;
   pop.population_size = 10;
   pop.min_fitness_change = 1.0;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_population_mutation_none);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.initialize(test_population_dummy_setup_func);

   p.simulate();

   int retval = 1;

   if (p.avg_fitness != 50.0)
      retval = 0;

   return retval;
}

int TestPopulation::tp_simulate_0() {

   PopulationOptions pop;
   pop.population_size = 100;
   pop.thread_count = PopulationOption::ThreadCount::THREAD_COUNT_AUTO;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_selection_mutation_dummy_func);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.initialize(test_population_count_10);
   p.sort_population();
   p.simulate(1);

   int retval = 1;

   for (int i = 0; i < 100; ++i) {
      if (p.population()[i]->fitness != 40.0 || *(p.population()[i]->value) != 4)
         retval = 0;
   }

   return retval;
}

int TestPopulation::tp_simulate_1() {

   PopulationOptions pop;
   pop.population_size = 100;
   pop.maximum_generation = 100;
   pop.thread_count = PopulationOption::ThreadCount::THREAD_COUNT_AUTO;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_selection_mutation_dummy_func);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.initialize(test_population_count_10);
   p.sort_population();
   p.simulate();

   int retval = 1;

   for (int i = 0; i < 100; ++i) {
      if (p.population()[i]->fitness != 40.0 || *(p.population()[i]->value) != 4)
         retval = 0;
   }

   if (p.generation != 101)
      retval = 0;

   return retval;
}

int TestPopulation::tp_simulate_2() {

   PopulationOptions pop;
   pop.population_size = 100;
   pop.maximum_elapsed = 0.01;
   pop.thread_count = PopulationOption::ThreadCount::THREAD_COUNT_AUTO;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_selection_mutation_dummy_func);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.initialize(test_population_count_10);
   p.sort_population();
   p.simulate();

   int retval = 1;

   for (int i = 0; i < 100; ++i) {
      if (p.population()[i]->fitness != 40.0 || *(p.population()[i]->value) != 4)
         retval = 0;
   }

   if (p.time_elapsed < pop.maximum_elapsed)
      retval = 0;

   return retval;
}

int TestPopulation::tp_simulate_3() {

   PopulationOptions pop;
   pop.population_size = 100;
   pop.thread_count = PopulationOption::ThreadCount::THREAD_COUNT_AUTO;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_population_mutation_none);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.add_before(5,test_population_multiply_2,NULL);
   p.add_before(10,test_population_add_1,NULL);

   p.initialize(test_population_dummy_setup_func);
   p.simulate(1);

   int retval = 1;

   for (int i = 0; i < 100; ++i) {
      if (p.population()[i]->fitness != 120.0 || *(p.population()[i]->value) != 12)
         retval = 0;
   }

   return retval;
}

int TestPopulation::tp_simulate_4() {

   PopulationOptions pop;
   pop.population_size = 10000;
   pop.thread_count = PopulationOption::ThreadCount::THREAD_COUNT_AUTO;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_population_mutation_none);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.add_after(5,test_population_add_1,NULL);
   p.add_after(10,test_population_multiply_2,NULL);

   p.initialize(test_population_dummy_setup_func);
   p.simulate(1);

   int retval = 1;

   for (int i = 0; i < 10000; ++i) {
      if (p.population()[i]->fitness != 110.0 || *(p.population()[i]->value) != 11)
         retval = 0;
   }

   return retval;
}

int TestPopulation::tp_simulate_5() {

   PopulationOptions pop;
   pop.population_size = 10000;
   pop.thread_count = PopulationOption::ThreadCount::THREAD_COUNT_AUTO;

   Population<int> p = Population<int>(&pop);

   LastOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                test_population_mutation_none);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.add_before(0,test_population_set_poplen_5,NULL);

   p.initialize(test_population_dummy_setup_func);

   *((Chromosome<int> **)p.curr_generation->data)[4]->value = 1;
   for (int i = 5; i < 10000; ++i)
      *((Chromosome<int> **)p.curr_generation->data)[i]->value = 0;

   p.simulate(1);

   int retval = 1;

   for (int i = 0; i < 10000; ++i) {
      if (p.population()[i]->fitness != 10.0 || *(p.population()[i]->value) != 1)
         retval = 0;
   }

   return retval;
}

int TestPopulation::tp_simulate_6() {

   PopulationOptions pop;
   pop.population_size = 10;
   pop.elitism_count = 3;
   pop.thread_count = PopulationOption::ThreadCount::THREAD_COUNT_AUTO;

   Population<int> p = Population<int>(&pop);

   LastOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                test_population_mutation_none);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.add_before(0,test_population_set_poplen_5,NULL);

   p.initialize(test_population_dummy_setup_func);

   for (int i = 4; i < 10; ++i)
      *((Chromosome<int> **)p.curr_generation->data)[i]->value = 1;

   p.simulate(1);

   int retval = 1;

   for (int i = 0; i < 3; ++i) {
      if (p.population()[i]->fitness != 50.0 || *(p.population()[i]->value) != 5)
         retval = 0;
   }

   for (int i = 3; i < 10; ++i) {
      if (p.population()[i]->fitness != 10.0 || *(p.population()[i]->value) != 1)
         retval = 0;
   }

   return retval;
}

int TestPopulation::tp_simulate_7() {

   PopulationOptions pop;
   pop.population_size = 10;
   pop.max_fitness = 40.0;
   pop.thread_count = PopulationOption::ThreadCount::THREAD_COUNT_AUTO;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_population_mutation_none);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.initialize(test_population_dummy_setup_func);

   p.simulate();

   int retval = 1;

   if (p.max_fitness < 40.0)
      retval = 0;

   return retval;
}

int TestPopulation::tp_simulate_8() {

   PopulationOptions pop;
   pop.population_size = 10;
   pop.min_fitness_change = 1.0;
   pop.thread_count = PopulationOption::ThreadCount::THREAD_COUNT_AUTO;

   Population<int> p = Population<int>(&pop);

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_population_mutation_none);
   p.set_fitness(test_population_dummy_fitness_eval);
   p.set_evolution(s.as_function());

   p.initialize(test_population_dummy_setup_func);

   p.simulate();

   int retval = 1;

   if (p.avg_fitness != 50.0)
      retval = 0;

   return retval;
}

int TestPopulation::reset_0() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);
   p.generation = 2000;
   p.time_elapsed = 1000;
   p.avg_fitness = 234;
   p.max_fitness = 943;

   p.reset();

   int retval = 1;

   if (p.generation != 0)
      retval = 0;
   if (p.time_elapsed != 0)
      retval = 0;
   if (p.avg_fitness != DBL_MAX)
      retval = 0;
   if (p.max_fitness != -DBL_MAX)
      retval = 0;

   return retval;
}

int TestPopulation::initialize_1() {

   Population<int> p = Population<int>("poptions/pop_init.ini");

   int retval = 1;

   if (p.options->population_size != 23094)
      retval = 0;
   if (p.options->maximum_generation != 72034)
      retval = 0;
   if (p.options->maximum_elapsed != 234.42)
      retval = 0;
   if (p.options->elitism_count != 724)
      retval = 0;
   if (p.options->tracking_mode != PopulationOption::TrackingMode::TRACKING_MODE_LIVE)
      retval = 0;
   if (p.options->min_fitness_change != 2.54)
      retval = 0;
   if (p.options->max_fitness != 68.70)
      retval = 0;
   if (p.options->thread_count != std::thread::hardware_concurrency())
      retval = 0;

   if (p.time_elapsed != 0.0)
      retval = 0;

   if (p.generation != 0)
      retval = 0;

   if (p.generation_A.end != 23094)
      retval = 0;

   if (p.generation_A.length != 23104)
      retval = 0;

   if (p.generation_B.end != 23094)
      retval = 0;

   if (p.generation_B.length != 23104)
      retval = 0;

   if (p.curr_generation != &p.generation_A)
      retval = 0;

   if (p.next_generation != &p.generation_B)
      retval = 0;

   if (p.before.end != 0)
      retval = 0;

   if (p.before.data != 0)
      retval = 0;

   if (p.after.end != 0)
      retval = 0;

   if (p.after.data != 0)
      retval = 0;

   if (p.evolution != NULL)
      retval = 0;

   if (p.fitness != NULL)
      retval = 0;

   if (p.options->free_on_exit != 1)
      retval = 0;

   return retval;
}

}

