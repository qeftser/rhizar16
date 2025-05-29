
#include "uniform_rand.h"
#include <stdlib.h>

namespace Rhizar16 {

UniformRand::UniformRand() {
   seed_value = arc4random();
   generator = std::mt19937_64(seed_value);
}

UniformRand::UniformRand(uint64_t seed) {
   seed_value = seed;
   generator = std::mt19937_64(seed_value);
}

uint64_t UniformRand::seed() {
   return seed_value;
}

uint64_t UniformRand::random() {
   return generator();
}

}
