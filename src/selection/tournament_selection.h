
#ifndef __RHIZAR16_TOURNAMENT_SELECTION__

#define __RHIZAR16_TOURNAMENT_SELECTION__
#include "selection.h"
#include "population.h"
#include "util.h"

template<typename T, unsigned TournamentSize, unsigned Parents, unsigned Children>
class TournamentSelector : public Selector<T,Parents,Children> {
private:

   UniformRand r;

public:

   TournamentSelector(void (* reproduction)(T ** const parents, T ** children),
                      void (* mutation)(T * chromosome) = NULL) :
         Selector<T,Parents,Children>(reproduction,mutation) {}

   void select(const Chromosome<T> ** const population, int poplen,
               Population<T> & pop, int new_poplen) override {

      unsigned int collected = 0;

      while (collected < new_poplen) {

         for (int i = 0; i < Children; ++i) {
            this->children[i] = pop.retrieve()->value;
         }

         for (int i = 0; i < Parents; ++i) {

            Chromosome<T> * best = population[r.random() % poplen];
            for (int i = 0; i < TournamentSize-1; ++i) {
               Chromosome<T> * canidate = population[r.random() % poplen];
               if (canidate->fitness > best->fitness)
                  best = canidate;
            }

            this->parents[i] = best->value;
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

}

#endif
