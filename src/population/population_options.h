
#ifndef __RHIZAR16_POPULATION_OPTIONS__

#define __RHIZAR16_POPULATION_OPTIONS__
#include <stdint.h>
#include <string.h>
#include <string>
#include <vector>

namespace Rhizar16 {

struct PopulationOptions;
struct MasterSlaveOptions;
struct DistributedOptions;

namespace PopulationOption {

   const std::string ADDRESS_ANY = "*";

   enum TrackingMode {
      TRACKING_MODE_NONE    = 0,
      TRACKING_MODE_VERBOSE = 1,
      TRACKING_MODE_LIVE    = 2,
   };

   enum ThreadCount {
      THREAD_COUNT_NONE = 0,
      THREAD_COUNT_AUTO = 0xffff,
   };

   /* use the given file to population the passed structure.
    * Return true if the operation succeeded, and false otherwise */
   bool from_file(std::string path, struct Rhizar16::PopulationOptions * opts, bool print_failure = false,
                  std::string section = "Population");
   bool from_file(std::string path, struct Rhizar16::MasterSlaveOptions * opts, bool print_failure = false);
   bool from_file(std::string path, struct Rhizar16::DistributedOptions * opts, bool print_failure = false);

   /* print all relevant configuration for the given options */
   void print_configuration(struct Rhizar16::PopulationOptions * opts);
   void print_configuration(struct Rhizar16::MasterSlaveOptions * opts);
   void print_configuration(struct Rhizar16::DistributedOptions * opts);

   /* deallocate the given structures 
    * Note: the pointer passed in will be invalidated by this function */
   void free_configuration(struct Rhizar16::MasterSlaveOptions * opts);
   void free_configuration(struct Rhizar16::DistributedOptions * opts);

}

/* the various options that can be passed 
 * to a population class to determine it's
 * behavior during simulation             */
struct PopulationOptions {

   /* whether to call free on the pointer
    * to this struct when destroying the
    * population. This should not be set
    * by the user, but will be set internally
    * if a file is used to generate the 
    * options for the population.            */
   uint8_t free_on_exit = 0;

   /* size of the population at the current
    * generation. This variable can be modified
    * to change the population size as the system
    * runs, enabling the population to be varied
    * based on external metrics.                */
   uint32_t population_size = 0;

   /* the maximum generation to evolve the 
    * population to.                       */
   uint32_t maximum_generation = 0;

   /* maximum time the system is allowed to
    * run for in seconds. Note that this value
    * will only be checked at the end of each
    * cycle, so the actual runtime of the system
    * will be more than the value listed.        */
   double maximum_elapsed = 0.0;

   /* number of best chromosomes to copy over to
    * the next generation when performing the 
    * reproduction operation. The top N, where
    * N is elitism_count, will be swapped into
    * the next generation.                      */
   uint16_t elitism_count = 0;

   /* statistics to track during the operation of
    * the system. Can be set to verbose to print 
    * minimal statistics about the runtime, and
    * can be set to live to display substantial
    * information about the system during it's runtime */
   uint8_t tracking_mode = PopulationOption::TrackingMode::TRACKING_MODE_NONE;

   /* a minimum set fitness change. If the change in
    * the average fitness of the population is below
    * this value, it will exit.                     */ 
   double min_fitness_change = 0;

   /* the maximum fitness a chromosome can reach. If
    * this value is reached the system exits.       */
   double max_fitness = 0;

   /* whether to end the system. This value can be
    * set mid-run and the system will stop at the
    * end of the next cycle.                      */
   uint8_t finish = 0;

   /* number of threads to run the fitness function 
    * in parallel on for each generation. Setting to
    * a value less than 2 disables this option, and
    * setting to PopulationOption::THREAD_COUNT_AUTO
    * will choose the number based on the reported
    * hardware concurrency.                        */
   uint16_t thread_count = PopulationOption::ThreadCount::THREAD_COUNT_NONE;
};

/* the options avaliable for configuring
 * the master-slave genetic algorithm. Note
 * that there are two ways to configure this
 * system. Either a single slave can be configured,
 * or multiple slaves can be configured individually.
 * If only one slave is given, it must have it's
 * name set to the kleen star (*), as it will match
 * all processes that start up. If each slave is individually
 * designated, a process that starts up and is not the master
 * will proceed down the list of slaves. If it does not find 
 * itself it will exit. The list can be ended with the kleen
 * star to match any devices that do not need to be explicitly
 * configured.                                                 */
struct MasterSlaveOptions {

   /* whether to free the structure on exit. Note
    * that this applies to both this structure
    * and all of the slaves attached to it.     */
   uint8_t free_on_exit = 0;

   /* the address of the master. Will be used
    * to verify which device the master is, and
    * also by slaves to connect.                */
   std::string master_address = "";

   /* the port for the master to listen on. Will
    * be used by slaves to connect to the master. */
   uint16_t master_port = 0;

   /* set of population options to use for the master.
    * Because the only use of the slaves is to evaluate
    * the fitness function, the options here will have
    * the same behavior they do in the standalone
    * PopulationOptions structure.                    */
   struct PopulationOptions master_options;

   /* all slaves on the system. */
   struct SlaveOptions * slaves = NULL;
};

/* options for configuring each slave 
 * Note: see PopulationOptions for a 
 * discussion of the thread_count parameter */
struct SlaveOptions {

   /* address of the slave. Will be used by
    * slaves to identify themselves.      */
   std::string slave_address = "";

   /* number of threads to run the 
    * fitness evaluations with. This value
    * also corresponds to the number of 
    * chromosomes that will be sent by the
    * master at a time for evaluation.    */
   uint32_t thread_count = PopulationOption::ThreadCount::THREAD_COUNT_NONE;

   /* pointer to the next slave. NULL marks
    * the end of the list.                */
   struct SlaveOptions * next = NULL;
};

/* Collection of options for all elements of the 
 * distributed system. Each device will find it's
 * address, open the corresponding connections, and
 * then proceed with the evaluation of it's genetic
 * algorithm, periodically exchanging chromosomes
 * as dictated by the settings listed. */
struct DistributedOptions {

   /* whether to call free on this structure
    * when destroying the distributed population.
    * This option applies to all demes attached to
    * this structure as well.                     */
   uint8_t free_on_exit = 0;

   /* list of demes associated with the population */
   struct Deme * demes = NULL;
};

/* a single device in the distributed system. Specifies
 * which address it sits at as well as which port it
 * is accepting. This is used to start the deme's own
 * server, as well as for any other deme to connect
 * to another's server. Also specifies internal parameters
 * relative to how often to exchange chromosomes.        */
struct Deme {

   /* optional name to identify the deme by */
   std::string nickname = "";

   /* the address of the deme. Will be used for 
    * self-identification.                     */
   std::string address = "";

   /* the port for the deme to run it's server on */
   uint16_t    port = 0;

   /* list of connections this deme has to other demes */
   std::vector<struct DemeConnection *> connections;

   /* options for the runtime of this deme */
   struct PopulationOptions options;

   /* NULL terminated linked-list of demes */
   struct Deme * next = NULL;
};

/* describes the behavior of the connection
 * of a host deme to another.              */
struct DemeConnection {

   /* name of the deme to connect to. Can
    * either be the address or nickname of
    * the other deme.                     */
   std::string name = "";

   /* the interval on which to transfer chromosomes
    * to the deme. This is every N generations where
    * N is the given number. If this value is 0 then
    * the default will be used.                    */
   uint32_t transfer_interval = 0;

   /* the number of chromosomes to transfer at 
    * transfer time.                          */
   uint32_t transfer_count = 0;
};

}

#endif


