
#include "uniform_rand.h"
#include <ctime>

namespace Rhizar16 {

UniformRand::UniformRand() {
   seed_value = time(NULL) * clock();
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
