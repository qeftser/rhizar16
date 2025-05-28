
#ifndef __RHIZAR16_SELECTION_TEST__

#define __RHIZAR16_SELECTION_TEST__
#include "selection.h"
#include "chromosome.h"
#include "population.h"
#include <stdlib.h>

namespace Rhizar16 {

template<typename T, unsigned Parents, unsigned Children>
class FirstOnlySelection : public Selector<T,Parents,Children> {
public:

   FirstOnlySelection(void (* reproduction)(T ** const parents, T ** children),
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

            this->parents[i] = (population[0])->value;

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

template<typename T, unsigned Parents, unsigned Children>
class LastOnlySelection : public Selector<T,Parents,Children> {
public:

   LastOnlySelection(void (* reproduction)(T ** const parents, T ** children),
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

            this->parents[i] = (population[poplen-1])->value;

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

void test_selection_reproduction_dummy_func_1_1(int ** const parents, int ** children); 
void test_selection_reproduction_dummy_func_1_2(int ** const parents, int ** children);
void test_selection_reproduction_dummy_func_2_1(int ** const parents, int ** children);
void test_selection_reproduction_dummy_func_5_1(int ** const parents, int ** children);
void test_selection_reproduction_dummy_func_1_5(int ** const parents, int ** children);
void test_selection_reproduction_dummy_func_2_3(int ** const parents, int ** children);
void test_selection_mutation_dummy_func(int * chromosome);

class TestSelection {
public:

   static int intialization_0();
   static int intialization_1();

   static int selection_0();
   static int selection_1();
   static int selection_2();
   static int selection_3();
   static int selection_4();
   static int selection_5();

   static int as_function_0();
   static int as_function_1();
   static int as_function_2();
   static int as_function_3();
   static int as_function_4();
   static int as_function_5();

};

}

#endif
