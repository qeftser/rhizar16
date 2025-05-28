
#ifndef __RHIZAR16_CHROMOSOME__

#define __RHIZAR16_CHROMOSOME__

namespace Rhizar16 {

/* a simple struct that allows custom selection
 * algorithms to be swapped out pretty easily  */
template<typename T>
struct Chromosome {
   T * value;
   double fitness;
};

}

#endif
