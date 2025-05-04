
#include "uniform_rand_test.h"
#include "uniform_rand.h"

namespace Rhizar16 {

int TestUniformRand::initialization() {
   UniformRand r;

   if (r.seed() != 0)
      return 1;
   return 0;
}

int TestUniformRand::initialization_seed0() {
   UniformRand r(0);

   if (r.seed() != 0)
      return 0;
   return 1;
}

int TestUniformRand::initialization_seed_0x43022432() {
   UniformRand r(0x43022432);

   if (r.seed() != 0x43022432)
      return 0;
   return 1;
}

int TestUniformRand::random() {
   UniformRand r;

   if (r.random() != r.random())
      return 1;
   return 0;
}

int TestUniformRand::random_seed0() {
   UniformRand r1(0);
   UniformRand r2(0);

   if (r1.random() != r2.random())
      return 0;
   return 1;
}

int TestUniformRand::random_seed_0x43022432() {
   UniformRand r1(0x43022432);
   UniformRand r2(0x43022432);

   if (r1.random() != r2.random())
      return 0;
   return 1;
}

}
