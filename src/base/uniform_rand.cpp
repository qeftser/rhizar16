
#include "uniform_rand.h"
#include <cstdint>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#include <bcrypt.h>
#endif

namespace Rhizar16 {

UniformRand::UniformRand() {
#ifdef _WIN32
   BCryptGenRandom(NULL,(uint8_t *)&seed_value,sizeof(seed_value),BCRYPT_USE_SYSTEM_PREFERRED_RNG);
#elif defined(__unix__)
   seed_value = arc4random();
#else
#error operating system not supported
#endif
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
