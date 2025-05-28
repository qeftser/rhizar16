
#ifndef __RHIZAR16_POPULATION_OPTIONS__

#define __RHIZAR16_POPULATION_OPTIONS__
#include <stdint.h>

namespace Rhizar16 {

namespace PopulationOption {

   enum OperationMode {
      OPERATION_MODE_MANUAL,
      OPERATION_MODE_AUTOMATIC,
   };

   enum TrackingMode {
      TRACKING_MODE_NONE,
   };

};

/* the various options that can be passed 
 * to a population class to determine it's
 * behavior during simulation             */
struct PopulationOptions {

   /* Modifiable during runtime */
   uint32_t population_size;
   uint32_t maximum_generation;
   double maximum_elapsed;
   uint16_t elitism_count;
   uint8_t tracking_mode;
   uint8_t operation_mode;
   double min_fitness_change;
   double max_fitness;
   uint8_t finish;

   /* Constant after initialization */

};

}

#endif


