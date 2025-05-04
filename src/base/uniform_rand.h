
#ifndef __RHIZAR16_UNIFORM_RAND__

#define __RHIZAR16_UNIFORM_RAND__

#include <random>

namespace Rhizar16 {

/* A wrapper over the c++ random stuff so I don't
 * have to write the same thing repeatedly in a
 * bunch of places.                              */
class UniformRand {

private:

   uint64_t seed_value;
   std::mt19937_64 generator;

public:

   UniformRand();

   UniformRand(uint64_t seed);

   /* return the seed used */
   uint64_t seed();

   /* return the next random value */
   uint64_t random();

};

}

#endif
