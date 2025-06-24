
#include "selection_test.h"
#include "population.h"
#include "population_options.h"

namespace Rhizar16 {

void test_selection_reproduction_dummy_func_1_1(int ** const parents, int ** children) {
   *(children)[0] = *(parents[0]); 
}

void test_selection_reproduction_dummy_func_1_2(int ** const parents, int ** children) {
   *(children)[0] = *(parents[0]); 
   *(children)[1] = -1 * *(parents[0]); 
}

void test_selection_reproduction_dummy_func_2_1(int ** const parents, int ** children) {
   *(children)[0] = *(parents[0]) + *(parents[1]);
}

void test_selection_reproduction_dummy_func_5_1(int ** const parents, int ** children) {
   *(children)[0] = *(parents[0]) + *(parents[1]) + *(parents[2]) + *(parents[3]) + *(parents[4]);
}

void test_selection_reproduction_dummy_func_1_5(int ** const parents, int ** children) {
   *(children)[0] = 1 * *(parents[0]);
   *(children)[1] = 2 * *(parents[0]);
   *(children)[2] = 3 * *(parents[0]);
   *(children)[3] = 4 * *(parents[0]);
   *(children)[4] = 5 * *(parents[0]);
}

void test_selection_reproduction_dummy_func_2_3(int ** const parents, int ** children) {
   *(children[0]) = *(parents[0]) + *(parents[1]);
   *(children[1]) = *(parents[0]) - *(parents[1]);
   *(children[2]) = *(parents[1]) - *(parents[0]);
}

void test_selection_mutation_dummy_func(int * chromosome) {
   if (*chromosome % 2)
      *chromosome /= 2;
}

int TestSelection::intialization_0() {

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_selection_mutation_dummy_func);

   int retval = 1;

   /*
   if (s.mutation != test_selection_mutation_dummy_func)
      retval = 0;

   if (s.reproduction != test_selection_reproduction_dummy_func_1_1) 
      retval = 0;
   */

   if (sizeof(s.parents) != sizeof(int *) * 1)
      retval = 0;

   if (sizeof(s.children) != sizeof(int *) * 1)
      retval = 0;

   return retval;
}

int TestSelection::intialization_1() {

   FirstOnlySelection<int,2,3> s(test_selection_reproduction_dummy_func_2_3,
                                 test_selection_mutation_dummy_func);

   int retval = 1;

   /*
   if (s.mutation != test_selection_mutation_dummy_func)
      retval = 0;

   if (s.reproduction != test_selection_reproduction_dummy_func_2_3) 
      retval = 0;
   */

   if (sizeof(s.parents) != sizeof(int *) * 2)
      retval = 0;

   if (sizeof(s.children) != sizeof(int *) * 3)
      retval = 0;

   return retval;
}

int TestSelection::selection_0() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_selection_mutation_dummy_func);
   p.next_generation->end = 0;

   s.select((const Chromosome<int> ** const)p.population(), 10, p, 5);

   int retval = 1;

   for (int i = 0; i < 5; ++i) {
      if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != 1) {
         retval = 0;
         break;
      }
   }

   return retval;
}

int TestSelection::selection_1() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,1,2> s(test_selection_reproduction_dummy_func_1_2,
                                 test_selection_mutation_dummy_func);
   p.next_generation->end = 0;

   s.select((const Chromosome<int> ** const)p.population(), 10, p, 20);

   int retval = 1;

   for (int i = 0; i < 20; ++i) {
      if (i % 2) {
         if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != -1) {
            retval = 0;
            break;
         }
      }
      else {
         if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != 1) {
            retval = 0;
            break;
         }
      }
   }

   return retval;
}

int TestSelection::selection_2() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,2,1> s(test_selection_reproduction_dummy_func_2_1,
                                 test_selection_mutation_dummy_func);
   p.next_generation->end = 0;

   s.select((const Chromosome<int> ** const)p.population(), 10, p, 7);

   int retval = 1;

   for (int i = 0; i < 7; ++i) {
      if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != 6) {
         retval = 0;
         break;
      }
   }

   return retval;
}

int TestSelection::selection_3() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,5,1> s(test_selection_reproduction_dummy_func_5_1,
                                 test_selection_mutation_dummy_func);
   p.next_generation->end = 0;

   s.select((const Chromosome<int> ** const)p.population(), 10, p, 12);

   int retval = 1;

   for (int i = 0; i < 12; ++i) {
      if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != 7) {
         retval = 0;
         break;
      }
   }

   return retval;
}

int TestSelection::selection_4() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,1,5> s(test_selection_reproduction_dummy_func_1_5,
                                 test_selection_mutation_dummy_func);
   p.next_generation->end = 0;

   s.select((const Chromosome<int> ** const)p.population(), 10, p, 33);

   int retval = 1;

   for (int i = 0; i < 33; ++i) {
      if ((((i % 5) + 1) * 3) % 2) {
         if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != ((((i % 5) + 1) * 3)) / 2) {
            retval = 0;
            break;
         }
      }
      else {
         if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != ((((i % 5) + 1) * 3))) {
            retval = 0;
            break;
         }
      }
   }

   return retval;
}

int TestSelection::selection_5() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,2,3> s(test_selection_reproduction_dummy_func_2_3,
                                 test_selection_mutation_dummy_func);
   p.next_generation->end = 0;

   s.select((const Chromosome<int> ** const)p.population(), 10, p, 1000);

   int retval = 1;

   for (int i = 0; i < 1000; ++i) {
      if (i % 3) {
         if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != 0) {
            retval = 0;
            break;
         }
      }
      else {
         if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != 6) {
            retval = 0;
            break;
         }
      }
   }

   return retval;
}

int TestSelection::as_function_0() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,1,1> s(test_selection_reproduction_dummy_func_1_1,
                                 test_selection_mutation_dummy_func);
   p.next_generation->end = 0;

   auto func = s.as_function();

   func((const Chromosome<int> ** const)p.population(), 10, p, 5);

   int retval = 1;

   for (int i = 0; i < 5; ++i) {
      if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != 1) {
         retval = 0;
         break;
      }
   }

   return retval;
}

int TestSelection::as_function_1() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,1,2> s(test_selection_reproduction_dummy_func_1_2,
                                 test_selection_mutation_dummy_func);
   p.next_generation->end = 0;

   auto func = s.as_function();

   func((const Chromosome<int> ** const)p.population(), 10, p, 20);

   int retval = 1;

   for (int i = 0; i < 20; ++i) {
      if (i % 2) {
         if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != -1) {
            retval = 0;
            break;
         }
      }
      else {
         if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != 1) {
            retval = 0;
            break;
         }
      }
   }

   return retval;
}

int TestSelection::as_function_2() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,2,1> s(test_selection_reproduction_dummy_func_2_1,
                                 test_selection_mutation_dummy_func);
   p.next_generation->end = 0;

   auto func = s.as_function();

   func((const Chromosome<int> ** const)p.population(), 10, p, 7);

   int retval = 1;

   for (int i = 0; i < 7; ++i) {
      if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != 6) {
         retval = 0;
         break;
      }
   }

   return retval;
}

int TestSelection::as_function_3() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,5,1> s(test_selection_reproduction_dummy_func_5_1,
                                 test_selection_mutation_dummy_func);
   p.next_generation->end = 0;

   auto func = s.as_function();

   func((const Chromosome<int> ** const)p.population(), 10, p, 12);

   int retval = 1;

   for (int i = 0; i < 12; ++i) {
      if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != 7) {
         retval = 0;
         break;
      }
   }

   return retval;
}

int TestSelection::as_function_4() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,1,5> s(test_selection_reproduction_dummy_func_1_5,
                                 test_selection_mutation_dummy_func);
   p.next_generation->end = 0;

   auto func = s.as_function();

   func((const Chromosome<int> ** const)p.population(), 10, p, 33);

   int retval = 1;

   for (int i = 0; i < 33; ++i) {
      if ((((i % 5) + 1) * 3) % 2) {
         if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != ((((i % 5) + 1) * 3)) / 2) {
            retval = 0;
            break;
         }
      }
      else {
         if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != ((((i % 5) + 1) * 3))) {
            retval = 0;
            break;
         }
      }
   }

   return retval;
}

int TestSelection::as_function_5() {

   PopulationOptions pop;
   pop.population_size = 10;

   Population<int> p = Population<int>(&pop);

   for (int i = 0; i < 10; ++i) {
      *(p.population()[i])->value = 3;
   }

   FirstOnlySelection<int,2,3> s(test_selection_reproduction_dummy_func_2_3,
                                 test_selection_mutation_dummy_func);
   p.next_generation->end = 0;

   auto func = s.as_function();

   func((const Chromosome<int> ** const)p.population(), 10, p, 1000);

   int retval = 1;

   for (int i = 0; i < 1000; ++i) {
      if (i % 3) {
         if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != 0) {
            retval = 0;
            break;
         }
      }
      else {
         if (*(((Chromosome<int> **)p.next_generation->data)[i])->value != 6) {
            retval = 0;
            break;
         }
      }
   }

   return retval;
}

}

