
#ifndef __RHIZAR16_SELECTION__

#define __RHIZAR16_SELECTION__
#include <string.h>
#include "chromosome.h"
#include "population.h"
#include <functional>

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;

namespace Rhizar16 {

/* not exactly sure why I need this... */
template<typename T>
class Population;

/* a method of selection used to fill another generation of a
 * population. This is tightly coupled with the reproduction
 * method in hopes of increasing the efficiency of the operations */
template <typename T, unsigned Parents, unsigned Children>
class Selector {

   /* for testing */
   friend class TestSelection;

protected: 

   std::function<void(T * chromosome)> mutation;
   std::function<void(T ** const parents, T ** children)> reproduction;
   T * parents[Parents];
   T * children[Children];

public:

   Selector(std::function<void(T ** const parents, T ** children)> reproduction,
            std::function<void(T * chromosome)> mutation = nullptr);

   virtual void select(const Chromosome<T> ** const population, int poplen,
                       Population<T> & pop, int new_poplen) = 0;

   auto as_function();

};

template<typename T, unsigned P, unsigned C>
Selector<T,P,C>::Selector(std::function<void(T ** const parents, T ** children)> reproduction,
                          std::function<void(T * chromosome)> mutation) {
   this->reproduction = reproduction;
   this->mutation = mutation;
}

template<typename T, unsigned P, unsigned C>
auto Selector<T,P,C>::as_function() {
   return std::bind(&Selector<T,P,C>::select, this, _1, _2, _3, _4);
}

}

#endif

