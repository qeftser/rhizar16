
#ifndef __RHIZAR16_ROULETTE_SELECTION__

#define __RHIZAR16_ROULETTE_SELECTION__

#include "selector.h"
#include "population.h"
#include "uniform_rand.h"
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

namespace Rhizar16 {

template<typename T, unsigned Parents, unsigned Children>
class RouletteSelector : public Selector<T,Parents,Children> {
private:

   UniformRand r;

public:

   RouletteSelector(void (* reproduction)(T ** const parents, T ** children),
                    void (* mutation)(T * chromosome) = NULL) :
         Selector<T,Parents,Children>(reproduction,mutation) {}

   void select(const Chromosome<T> ** const population, int poplen,
               Population<T> & pop, int new_poplen) override {

      unsigned int collected = 0;

      uint64_t slots[poplen];
      slots[poplen-1] = ULLONG_MAX;

      double fitness_sum = 0.0;
      for (int i = 0; i < poplen; ++i) {
         fitness_sum += population[i]->fitness;
      }

      if (poplen != 1)
         slots[0] = ((double)ULLONG_MAX * (population[0]->fitness / fitness_sum));
      for (int i = 1; i < poplen - 1; ++i) {
         slots[i] = slots[i-1] + ((double)ULLONG_MAX * (population[i]->fitness / fitness_sum));
      }

      while (collected < new_poplen) {

         for (int i = 0; i < Children; ++i) {
            this->children[i] = pop.retrieve()->value;
         }

         for (int i = 0; i < Parents; ++i) {

            uint64_t val = r.random();
            int pos = 0;

            while (slots[pos] < val) ++pos;

            this->parents[i] = population[pos]->value;

         }

         this->reproduction(this->parents,this->children);

         if (this->mutation) {
            for (int i = 0; i < Children; ++i) {

               this->mutation(this->children[i]);

            }
         }

         collected += Children;
      }

   }

};

}

#endif
