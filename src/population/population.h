
#ifndef __RHIZAR16_POPULATION__

#define __RHIZAR16_POPULATION__

#define __RHIZAR16_POPULATION_BORDERFUNC_EXPANSION_STEP__ 4
#define __RHIZAR16_POPULATION_GENERATION_GUTTER__ 10

#include <stdint.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>
#include <float.h>
#include <math.h>
#include <chrono>
#include <functional>
#include "utils.h"
#include "chromosome.h"
#include "selection.h"
#include "population_options.h"

namespace Rhizar16 {

/* A collection of chromosomes that gets manipulated 
 * and evolved on                                   */
template<typename T>
class Population {

   /* for testing */
   friend class TestPopulation;
   friend class TestSelection;

private:

   struct vector {
      uint32_t length;
      uint32_t end;
      void * data;
   };

   struct manipulator {
      int weight;
      int (* func)(Chromosome<T> ** pop, int length, void * arg);
      void * arg;
   };

   PopulationOptions * options;

   double time_elapsed;
   std::chrono::time_point<std::chrono::steady_clock> time_start;
   uint64_t generation;
   double avg_fitness =  DBL_MAX;
   double max_fitness = -DBL_MAX;

   vector generation_A;
   vector generation_B;

   vector * curr_generation;
   vector * next_generation;

   vector before;
   vector after;

   /*
   void (* evolution)(const Chromosome<T> ** const population, int poplen,
                      const Population<T> & pop, int new_poplen) = NULL;
                      */
   std::function<void(const Chromosome<T> ** const population, int poplen,
                      Population<T> & pop, int new_poplen)> evolution;
   //double (* fitness)(const T * const chromosome) = NULL;
   std::function<double(const T * const chromosome)> fitness;

   void grow_population(vector * generation, int new_len);
   void try_expand_vector(vector * vec, int new_len, size_t multiplier);
   void sort_population_helper(Chromosome<T> ** A, int lo, int hi);

public:

   Population(PopulationOptions * options);
   ~Population();

   void sort_population();
   void evaluate_fitness();
   void perform_evolution(int pool_size);

   void advance();
   Chromosome<T> * retrieve();

   bool finished();

   const Chromosome<T> ** population();
   uint32_t poplen();

   void add_before(int weight, int (* func)(Chromosome<T> ** pop, int length, void * arg), void * arg);
   void add_after(int weight, int (* func)(Chromosome<T> ** pop, int length, void * arg), void * arg);
   void set_selection(std::function<void(const Chromosome<T> ** const population, int poplen,
                                         Population<T> & new_pop, int new_poplen)> func);
   void set_evolution(std::function<void(const Chromosome<T> ** const population, int poplen,
                                         Population<T> & new_pop, int new_poplen)> func);
   void set_fitness(std::function<double(const T * const chromosome)> func);

   void initialize(void (* setup)(T * chromosome));
   void simulate(int iterations = -1);

};

template<typename T>
inline void Population<T>::grow_population(vector * generation, int new_len) {

   if (new_len < generation->length)
      return;

   int old_length = generation->length;

   generation->data = realloc(generation->data, new_len * sizeof(Chromosome<T> *));

   if (generation->data == NULL) {

      RHIZAR16_ERROR("%s, failed to expand memory to %db in Population<T>::grow_population\n",
                     strerror(errno), new_len * sizeof(Chromosome<T> *));
      exit(errno);
   }

   generation->length = new_len;

   for (int i = old_length; i < new_len; ++i) {
      Chromosome<T> * new_chromosome = (Chromosome<T> *)malloc(sizeof(struct Chromosome<T>));

      if (new_chromosome == NULL) {

         RHIZAR16_ERROR("%s, failed to allocate chromosome in Population<T>::grow_population\n",
                        strerror(errno));
         exit(errno);
      }

      bzero(new_chromosome,sizeof(struct Chromosome<T>));
      ((Chromosome<T> **)generation->data)[i] = new_chromosome;
   }

   for (int i = old_length; i < new_len; ++i) {

      T * new_value = new T;

      if (new_value == NULL) {

         RHIZAR16_ERROR("%s, failed to allocate value to chromosome in Population<T>::grow_population\n",
                        strerror(errno));
         exit(errno);
      }

      ((Chromosome<T> **)generation->data)[i]->value = new_value;
   }
}

template<typename T>
inline void Population<T>::try_expand_vector(vector * vec, int new_len, size_t multiplier) {

   if (vec->length >= new_len)
      return;

   /* yes we are handling reallocation manually */
   if (vec->length == vec->end) {

      vec->data = realloc(vec->data, new_len * multiplier);

      if (vec->data == NULL) {

         RHIZAR16_ERROR("%s, failed to expand memory to %db in Population<T>::try_expand_vector\n",
                        strerror(errno), new_len * multiplier);
         exit(errno);
      }

      vec->length = new_len;
   }
}

template<typename T>
void Population<T>::sort_population_helper(Chromosome<T> ** A, int lo, int hi) {

   if (lo >= hi || lo < 0)
      return;

   int p;

   /* partition */
   {
      Chromosome<T> * pivot = A[hi];
      Chromosome<T> * temp;

      p = lo;

      for (int i = lo; i < hi; ++i) {

         if (A[i]->fitness >= pivot->fitness) {

            temp = A[p];
            A[p] = A[i];
            A[i] = temp;

            p += 1;
         }

      }

      temp  = A[p];
      A[p]  = A[hi];
      A[hi] = temp;
   }

   sort_population_helper(A,lo,p-1);
   sort_population_helper(A,p+1,hi);
}

template<typename T>
void Population<T>::sort_population() {

   sort_population_helper((Chromosome<T> **)curr_generation->data,0,curr_generation->end-1);

}

template<typename T>
Population<T>::Population(PopulationOptions * options) {
   time_start = std::chrono::steady_clock::now();
   time_elapsed = 0.0;
   generation = 0;

   bzero(&generation_A,sizeof(vector));
   bzero(&generation_B,sizeof(vector));
   bzero(&before,sizeof(vector));
   bzero(&after,sizeof(vector));

   grow_population(&generation_A, options->population_size + __RHIZAR16_POPULATION_GENERATION_GUTTER__);
   grow_population(&generation_B, options->population_size + __RHIZAR16_POPULATION_GENERATION_GUTTER__);
   generation_A.end = options->population_size;
   generation_B.end = options->population_size;

   curr_generation = &generation_A;
   next_generation = &generation_B;

   this->options = options;
}

template<typename T>
Population<T>::~Population() {

   for (int i = 0; i < generation_A.length; ++i) {

      delete ((Chromosome<T> **)generation_A.data)[i]->value;
      free(((Chromosome<T> **)generation_A.data)[i]);

   }
   free(generation_A.data);

   for (int i = 0; i < generation_B.length; ++i) {

      delete ((Chromosome<T> **)generation_B.data)[i]->value;
      free(((Chromosome<T> **)generation_B.data)[i]);

   }
   free(generation_B.data);

   for (int i = 0; i < before.end; ++i) {

      free(((manipulator **)before.data)[i]);

   }
   free(before.data);

   for (int i = 0; i < after.end; ++i) {

      free(((manipulator **)after.data)[i]);

   }
   free(after.data);

}

template<typename T>
void Population<T>::advance() {

   generation += 1;

   {
      vector * temp = curr_generation;
      curr_generation = next_generation;
      next_generation = temp;
   }

   time_elapsed = std::chrono::duration<double>(
         std::chrono::steady_clock::now() - time_start).count();
}

template<typename T>
const Chromosome<T> ** Population<T>::population() {
   return (const Chromosome<T> **)curr_generation->data;
}

template<typename T>
uint32_t Population<T>::poplen() {
   return options->population_size;
}

template<typename T>
void Population<T>::add_before(int weight, int (* func)(Chromosome<T> ** pop, int length, void * arg), void * arg) {

   try_expand_vector(&before,before.length + __RHIZAR16_POPULATION_BORDERFUNC_EXPANSION_STEP__, 
                     sizeof(manipulator *));

   manipulator * new_func = (manipulator *)malloc(sizeof(manipulator));

   if (new_func == NULL) {

      RHIZAR16_ERROR("%s, failed to allocate memory for struct manipulator in Population::add_before\n",
                      strerror(errno));
      exit(errno);
   }

   new_func->weight = weight;
   new_func->func = func;
   new_func->arg = arg;

   {
      int i;
      for (i = before.end; i != 0 && ((manipulator **)before.data)[i-1]->weight < new_func->weight; --i);

      memmove(((manipulator **)before.data) + i + 1,
              ((manipulator **)before.data) + i,
               (before.end - i)*sizeof(manipulator *));

      ((manipulator **)before.data)[i] = new_func;
   }

   before.end += 1;
}

template<typename T>
void Population<T>::add_after(int weight, int (* func)(Chromosome<T> ** pop, int length, void * arg), void * arg) {

   try_expand_vector(&after,after.length + __RHIZAR16_POPULATION_BORDERFUNC_EXPANSION_STEP__,
                     sizeof(manipulator *));

   manipulator * new_func = (manipulator *)malloc(sizeof(manipulator));

   if (new_func == NULL) {

      RHIZAR16_ERROR("%s, failed to allocate memory for struct manipulator in Population::add_after\n",
                      strerror(errno));
      exit(errno);
   }

   new_func->weight = weight;
   new_func->func = func;
   new_func->arg = arg;

   {
      int i;
      for (i = after.end; i != 0 && ((manipulator **)after.data)[i-1]->weight < new_func->weight; --i);

      memmove(((manipulator **)after.data) + i + 1,
              ((manipulator **)after.data) + i,
               (after.end - i)*sizeof(manipulator *));

      ((manipulator **)after.data)[i] = new_func;
   }

   after.end += 1;
}

template<typename T>
void Population<T>::set_selection(std::function<void(const Chromosome<T> ** const population, int poplen,
                                                     Population<T> & new_pop, int new_poplen)> evolution) {
   this->evolution = evolution;
}

template<typename T>
void Population<T>::set_evolution(std::function<void(const Chromosome<T> ** const population, int poplen,
                                                     Population<T> & new_pop, int new_poplen)> evolution) {
   this->evolution = evolution;
}

template<typename T>
void Population<T>::set_fitness(std::function<double(const T * const chromosome)> fitness) {
   this->fitness = fitness;
}

template<typename T>
bool Population<T>::finished() {

   double l_avg_fitness = 0.0;
   max_fitness = 0.0;

   if (options->max_fitness > 0.0 || options->min_fitness_change > 0.0) {

      Chromosome<T> ** head = (Chromosome<T> **)curr_generation->data;
      for (int i = 0; i < curr_generation->end; ++i) {

         if ((*head)->fitness > max_fitness)
            max_fitness = (*head)->fitness;

         l_avg_fitness += (*head)->fitness;

         ++head;
      }

      l_avg_fitness /= curr_generation->end;
   }

   if (options->maximum_generation && generation > options->maximum_generation)
      return true;

   if (options->maximum_elapsed > 0.0 && time_elapsed > options->maximum_elapsed)
      return true;

   if (options->max_fitness > 0.0 && max_fitness >= options->max_fitness)
      return true;

   if (options->min_fitness_change > 0.0 && fabs(avg_fitness - l_avg_fitness) < options->min_fitness_change)
         return true;

   if (options->finish)
      return true;

   avg_fitness = l_avg_fitness;

   return false;
}

template<typename T>
void Population<T>::initialize(void (* setup)(T * chromosome)) {

   Chromosome<T> ** head = (Chromosome<T> **)curr_generation->data;

   for (int i = 0; i < curr_generation->end; ++i) {

      setup((*head)->value);
      (*head)->fitness = fitness((*head)->value);

      ++head;
   }

}

template<typename T>
Chromosome<T> * Population<T>::retrieve() {

   if (next_generation->end == next_generation->length)
      grow_population(next_generation,next_generation->length + __RHIZAR16_POPULATION_GENERATION_GUTTER__);

   return ((Chromosome<T> **)next_generation->data)[next_generation->end++];
}

template<typename T>
void Population<T>::evaluate_fitness() {

   Chromosome<T> ** head = (Chromosome<T> **)curr_generation->data;

   for (int i = 0; i < curr_generation->end; ++i) {

      (*head)->fitness = fitness((*head)->value);

      ++head;
   }

}

template<typename T>
void Population<T>::perform_evolution(int pool_size) {

   if (pool_size <= 0)
      pool_size = curr_generation->end;

   int elitism = options->elitism_count;
   int popsize = options->population_size;

   if (popsize + __RHIZAR16_POPULATION_GENERATION_GUTTER__ > next_generation->length)
      grow_population(next_generation,popsize + __RHIZAR16_POPULATION_GENERATION_GUTTER__);
   next_generation->end = elitism;

   evolution((const Chromosome<T> ** const)curr_generation->data, pool_size,
              *this, (int)options->population_size);

   next_generation->end = popsize;

   /* copy the best values over given elitism. Note that 
    * this assumes that values are still sorted from before */
   T * temp;
   for (int i = 0; i < elitism; ++i) {

      temp = ((Chromosome<T> **)curr_generation->data)[i]->value;
      ((Chromosome<T> **)curr_generation->data)[i]->value = ((Chromosome<T> **)next_generation->data)[i]->value;
      ((Chromosome<T> **)next_generation->data)[i]->value = temp;

   }
}

template<typename T>
void Population<T>::simulate(int iterations) {

   while (!finished() && iterations-- != 0) {

      /* ensure population is sorted */
      sort_population();

      /* call all before functions, potentially reducing the size of the mating pool */
      int pool_size = curr_generation->end;
      for (int i = 0; i < before.end; ++i) {
         int res = 
            ((manipulator **)before.data)[i]->func((Chromosome<T> **)curr_generation->data,
                                                   pool_size,
                                                   ((manipulator **)before.data)[i]->arg);
         if (res < 0) {
            RHIZAR16_WARN("before function returned error in Population<T>::simulate(): %d\n",res);
         }
         else if (res > 0) {
            pool_size = res;
         }
      }

      /* perform the operations of selection, reproduction, and mutation */
      perform_evolution(pool_size);

      /* call all after functions */
      for (int i = 0; i < after.end; ++i) {
         int res = 
            ((manipulator **)after.data)[i]->func((Chromosome<T> **)next_generation->data,
                                                   next_generation->end,
                                                   ((manipulator **)after.data)[i]->arg);
         if (res < 0) {
            RHIZAR16_WARN("after function returned error in Population<T>::simulate(): %d\n",res);
         }
      }

      advance();

      /* evaluate the fitness of our chromosomes */
      evaluate_fitness();

   }

}

}

#endif
