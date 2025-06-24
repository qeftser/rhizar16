
#ifndef __RHIZAR16_RANK_SELECTION__

#define __RHIZAR16_RANK_SELECTION__
#include "selection.h"
#include "population.h"
#include "utils.h"

namespace Rhizar16 {

template<typename T, unsigned Parents, unsigned Children>
class RankSelector : public Selector<T,Parents,Children> {
private:

   UniformRand r;

public:

   RankSelector(std::function<void(T ** const parents, T ** children)> reproduction,
                std::function<void(T * chromosome)> mutation = nullptr) :
         Selector<T,Parents,Children>(reproduction,mutation) {}

   void select(const Chromosome<T> ** const population, int poplen,
               Population<T> & pop, int new_poplen) override {

      unsigned int collected = 0;

      while (collected < new_poplen) {

         for (int i = 0; i < Children; ++i) {
            this->children[i] = pop.retrieve()->value;
         }

         for (int i = 0; i < Parents; ++i) {
            const Chromosome<T> * opt0 = population[r.random() % poplen];
            const Chromosome<T> * opt1 = population[r.random() % poplen];

            if (opt0->fitness < opt1->fitness)
               this->parents[i] = opt1->value;
            else
               this->parents[i] = opt0->value;

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
