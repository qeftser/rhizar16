
#include "population_options.h"
#include "population_options_test.h"
#include <thread>

namespace Rhizar16 {

namespace TestPopulationOptions {

int population_from_file_0() {
   PopulationOptions opts;

   bool res = PopulationOption::from_file("poptions/empty.ini",&opts);

   int retval = 1;

   if (res == true)
      retval = 0;

   return retval;
}

int population_from_file_1() {
   PopulationOptions opts;

   bool res = PopulationOption::from_file("poptions/pop0.ini",&opts);

   int retval = 1;

   if (res == true)
      retval = 0;

   return retval;
}

int population_from_file_2() {
   PopulationOptions opts;

   bool res = PopulationOption::from_file("poptions/pop1.ini",&opts);

   int retval = 1;

   if (res == false)
      retval = 0;
   if (opts.population_size != 100)
      retval = 0;

   return retval;
}

int population_from_file_3() {
   PopulationOptions opts;

   bool res = PopulationOption::from_file("poptions/pop2.ini",&opts,false,"abcde");

   int retval = 1;

   if (res == false)
      retval = 0;
   if (opts.population_size != 100)
      retval = 0;

   return retval;
}

int population_from_file_4() {
   PopulationOptions opts;

   bool res = PopulationOption::from_file("poptions/pop3.ini",&opts);

   int retval = 1;

   if (res == false)
      retval = 0;
   if (opts.population_size != 888)
      retval = 0;
   if (opts.maximum_generation != 22432)
      retval = 0;
   if (opts.maximum_elapsed != 123.343)
      retval = 0;
   if (opts.elitism_count != 23)
      retval = 0;
   if (opts.tracking_mode != PopulationOption::TrackingMode::TRACKING_MODE_VERBOSE)
      retval = 0;
   if (opts.min_fitness_change != 0.313)
      retval = 0;
   if (opts.max_fitness != 42.42)
      retval = 0;
   if (opts.thread_count != 3)
      retval = 0;

   return retval;
}

int population_from_file_5() {
   PopulationOptions opts;

   bool res = PopulationOption::from_file("poptions/pop4.ini",&opts);

   int retval = 1;

   if (res == false)
      retval = 0;
   if (opts.population_size != 23094)
      retval = 0;
   if (opts.maximum_generation != 72034)
      retval = 0;
   if (opts.maximum_elapsed != 234.42)
      retval = 0;
   if (opts.elitism_count != 724)
      retval = 0;
   if (opts.tracking_mode != PopulationOption::TrackingMode::TRACKING_MODE_LIVE)
      retval = 0;
   if (opts.min_fitness_change != 2.54)
      retval = 0;
   if (opts.max_fitness != 68.70)
      retval = 0;
   if (opts.thread_count != std::thread::hardware_concurrency())
      retval = 0;

   return retval;
}

int population_from_file_6() {
   PopulationOptions opts;

   bool res = PopulationOption::from_file("poptions/pop5.ini",&opts);

   int retval = 1;

   if (res == false)
      retval = 0;
   if (opts.population_size != 0)
      retval = 0;
   if (opts.maximum_generation != 0)
      retval = 0;
   if (opts.maximum_elapsed != 0)
      retval = 0;
   if (opts.elitism_count != 0)
      retval = 0;
   if (opts.tracking_mode != 0)
      retval = 0;
   if (opts.min_fitness_change != 0)
      retval = 0;
   if (opts.max_fitness != 0)
      retval = 0;
   if (opts.thread_count != 0)
      retval = 0;

   return retval;
}

int ms_from_file_0() {
   MasterSlaveOptions * opts = new MasterSlaveOptions();

   bool res = PopulationOption::from_file("poptions/empty.ini",opts);

   int retval = 1;

   if (res != false)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int ms_from_file_1() {
   MasterSlaveOptions * opts = new MasterSlaveOptions();

   bool res = PopulationOption::from_file("poptions/ms0.ini",opts);

   int retval = 1;

   if (res != false)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int ms_from_file_2() {
   MasterSlaveOptions * opts = new MasterSlaveOptions();

   bool res = PopulationOption::from_file("poptions/ms1.ini",opts);

   int retval = 1;

   if (res != false)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int ms_from_file_3() {
   MasterSlaveOptions * opts = new MasterSlaveOptions();

   bool res = PopulationOption::from_file("poptions/ms2.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->master_address != "Master")
      retval = 0;
   if (opts->master_port != 8888)
      retval = 0;
   if (opts->master_options.population_size != 100)
      retval = 0;
   if (opts->slaves != NULL)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int ms_from_file_4() {
   MasterSlaveOptions * opts = new MasterSlaveOptions();

   bool res = PopulationOption::from_file("poptions/ms3.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->master_address != "172.16.0.23")
      retval = 0;
   if (opts->master_port != 34023)
      retval = 0;
   if (opts->master_options.population_size != 203438)
      retval = 0;
   if (opts->master_options.maximum_generation != 2948203)
      retval = 0;
   if (opts->master_options.maximum_elapsed != 24.542)
      retval = 0;
   if (opts->master_options.elitism_count != 234)
      retval = 0;
   if (opts->master_options.tracking_mode != PopulationOption::TrackingMode::TRACKING_MODE_LIVE)
      retval = 0;
   if (opts->master_options.min_fitness_change != 123.9)
      retval = 0;
   if (opts->master_options.max_fitness != 432)
      retval = 0;
   if (opts->master_options.thread_count != std::thread::hardware_concurrency())
      retval = 0;
   if (opts->slaves != NULL)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int ms_from_file_5() {
   MasterSlaveOptions * opts = new MasterSlaveOptions();

   bool res = PopulationOption::from_file("poptions/ms4.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->master_address != "127.0.0.1")
      retval = 0;
   if (opts->master_port != 8232)
      retval = 0;
   if (opts->master_options.population_size != 892338)
      retval = 0;
   if (opts->master_options.maximum_generation != 8423)
      retval = 0;
   if (opts->master_options.maximum_elapsed != 2043.2)
      retval = 0;
   if (opts->master_options.elitism_count != 7834)
      retval = 0;
   if (opts->master_options.tracking_mode != PopulationOption::TrackingMode::TRACKING_MODE_NONE)
      retval = 0;
   if (opts->master_options.min_fitness_change != 23.4)
      retval = 0;
   if (opts->master_options.max_fitness != 0.234)
      retval = 0;
   if (opts->master_options.thread_count != 12)
      retval = 0;
   if (opts->slaves != NULL)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int ms_from_file_6() {
   MasterSlaveOptions * opts = new MasterSlaveOptions();

   bool res = PopulationOption::from_file("poptions/ms5.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->master_address != "127.0.0.1")
      retval = 0;
   if (opts->master_port != 0)
      retval = 0;
   if (opts->master_options.population_size != 0)
      retval = 0;
   if (opts->master_options.maximum_generation != 0)
      retval = 0;
   if (opts->master_options.maximum_elapsed != 0)
      retval = 0;
   if (opts->master_options.elitism_count != 0)
      retval = 0;
   if (opts->master_options.tracking_mode != 0)
      retval = 0;
   if (opts->master_options.min_fitness_change != 0)
      retval = 0;
   if (opts->master_options.max_fitness != 0)
      retval = 0;
   if (opts->master_options.thread_count != 0)
      retval = 0;
   if (opts->slaves != NULL)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int ms_from_file_7() {
   MasterSlaveOptions * opts = new MasterSlaveOptions();

   bool res = PopulationOption::from_file("poptions/ms6.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->master_address != "192.168.0.1")
      retval = 0;
   if (opts->master_port != 8888)
      retval = 0;
   if (opts->master_options.population_size != 100)
      retval = 0;
   if (opts->slaves == NULL)
      retval = 0;
   if (opts->slaves->slave_address != "slave0")
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int ms_from_file_8() {
   MasterSlaveOptions * opts = new MasterSlaveOptions();

   bool res = PopulationOption::from_file("poptions/ms7.ini",opts,true);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->master_address != "192.168.0.1")
      retval = 0;
   if (opts->master_port != 8888)
      retval = 0;
   if (opts->master_options.population_size != 100)
      retval = 0;
   if (opts->slaves == NULL)
      retval = 0;
   if (opts->slaves->slave_address != "127.0.0.1")
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int ms_from_file_9() {
   MasterSlaveOptions * opts = new MasterSlaveOptions();

   bool res = PopulationOption::from_file("poptions/ms8.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->master_address != "192.168.0.1")
      retval = 0;
   if (opts->master_port != 8888)
      retval = 0;
   if (opts->master_options.population_size != 100)
      retval = 0;
   if (opts->slaves == NULL)
      retval = 0;
   if (opts->slaves->slave_address != "172.16.0.34")
      retval = 0;
   if (opts->slaves->thread_count != std::thread::hardware_concurrency())
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int ms_from_file_a() {
   MasterSlaveOptions * opts = new MasterSlaveOptions();

   bool res = PopulationOption::from_file("poptions/ms9.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->master_address != "172.16.0.1")
      retval = 0;
   if (opts->master_port != 8888)
      retval = 0;
   if (opts->master_options.population_size != 100)
      retval = 0;
   if (opts->slaves == NULL)
      retval = 0;
   if (opts->slaves->slave_address != "172.16.0.5")
      retval = 0;
   if (opts->slaves->thread_count != 4)
      retval = 0;
   if (opts->slaves->next->slave_address != "172.16.0.4")
      retval = 0;
   if (opts->slaves->next->thread_count != 3)
      retval = 0;
   if (opts->slaves->next->next->slave_address != "172.16.0.3")
      retval = 0;
   if (opts->slaves->next->next->thread_count != 2)
      retval = 0;
   if (opts->slaves->next->next->next->slave_address != "172.16.0.2")
      retval = 0;
   if (opts->slaves->next->next->next->thread_count != 1)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int ms_from_file_b() {
   MasterSlaveOptions * opts = new MasterSlaveOptions();

   bool res = PopulationOption::from_file("poptions/ms10.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->master_address != "172.16.0.1")
      retval = 0;
   if (opts->master_port != 0)
      retval = 0;
   if (opts->master_options.population_size != 0)
      retval = 0;
   if (opts->slaves == NULL)
      retval = 0;
   if (opts->slaves->slave_address != "172.16.0.5")
      retval = 0;
   if (opts->slaves->thread_count != 0)
      retval = 0;
   if (opts->slaves->next->slave_address != "172.16.0.4")
      retval = 0;
   if (opts->slaves->next->thread_count != 0)
      retval = 0;
   if (opts->slaves->next->next->slave_address != "172.16.0.3")
      retval = 0;
   if (opts->slaves->next->next->thread_count != 0)
      retval = 0;
   if (opts->slaves->next->next->next->slave_address != "172.16.0.2")
      retval = 0;
   if (opts->slaves->next->next->next->thread_count != 0)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int distributed_from_file_0() {
   DistributedOptions * opts = new DistributedOptions();

   bool res = PopulationOption::from_file("poptions/empty.ini",opts);

   int retval = 1;

   if (res == false)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int distributed_from_file_1() {
   DistributedOptions * opts = new DistributedOptions();

   bool res = PopulationOption::from_file("poptions/d0.ini",opts);

   int retval = 1;

   if (res == true)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int distributed_from_file_2() {
   DistributedOptions * opts = new DistributedOptions();

   bool res = PopulationOption::from_file("poptions/d1.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->demes->address != "zero")
      retval = 0;
   if (opts->demes->nickname != "")
      retval = 0;
   if (opts->demes->port != 9999)
      retval = 0;
   if (opts->demes->options.population_size != 100)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int distributed_from_file_3() {
   DistributedOptions * opts = new DistributedOptions();

   bool res = PopulationOption::from_file("poptions/d2.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->demes->address != "127.0.0.1")
      retval = 0;
   if (opts->demes->nickname != "zero_zero")
      retval = 0;
   if (opts->demes->port != 8943)
      retval = 0;
   if (opts->demes->options.population_size != 89524)
      retval = 0;
   if (opts->demes->options.maximum_generation != 2834)
      retval = 0;
   if (opts->demes->options.maximum_elapsed != 289.24)
      retval = 0;
   if (opts->demes->options.elitism_count != 123)
      retval = 0;
   if (opts->demes->options.tracking_mode != PopulationOption::TrackingMode::TRACKING_MODE_VERBOSE)
      retval = 0;
   if (opts->demes->options.min_fitness_change != 4.23)
      retval = 0;
   if (opts->demes->options.max_fitness != 89.23)
      retval = 0;
   if (opts->demes->options.thread_count != 4)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int distributed_from_file_4() {
   DistributedOptions * opts = new DistributedOptions();

   bool res = PopulationOption::from_file("poptions/d3.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->demes->address != "127.0.0.1")
      retval = 0;
   if (opts->demes->nickname != "zero_zero")
      retval = 0;
   if (opts->demes->port != 14343)
      retval = 0;
   if (opts->demes->options.population_size != 2934)
      retval = 0;
   if (opts->demes->options.maximum_generation != 23)
      retval = 0;
   if (opts->demes->options.maximum_elapsed != 8293.324)
      retval = 0;
   if (opts->demes->options.elitism_count != 184)
      retval = 0;
   if (opts->demes->options.tracking_mode != PopulationOption::TrackingMode::TRACKING_MODE_LIVE)
      retval = 0;
   if (opts->demes->options.min_fitness_change != 34.234)
      retval = 0;
   if (opts->demes->options.max_fitness != 4823.0)
      retval = 0;
   if (opts->demes->options.thread_count != std::thread::hardware_concurrency())
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int distributed_from_file_5() {
   DistributedOptions * opts = new DistributedOptions();

   bool res = PopulationOption::from_file("poptions/d4.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->demes->address != "127.0.0.1")
      retval = 0;
   if (opts->demes->nickname != "zero_zero")
      retval = 0;
   if (opts->demes->port != 0)
      retval = 0;
   if (opts->demes->options.population_size != 0)
      retval = 0;
   if (opts->demes->options.maximum_generation != 0)
      retval = 0;
   if (opts->demes->options.maximum_elapsed != 0)
      retval = 0;
   if (opts->demes->options.elitism_count != 0)
      retval = 0;
   if (opts->demes->options.tracking_mode != 0)
      retval = 0;
   if (opts->demes->options.min_fitness_change != 0)
      retval = 0;
   if (opts->demes->options.max_fitness != 0)
      retval = 0;
   if (opts->demes->options.thread_count != 0)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int distributed_from_file_6() {
   DistributedOptions * opts = new DistributedOptions();

   bool res = PopulationOption::from_file("poptions/d5.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->demes->address != "127.0.0.1")
      retval = 0;
   if (opts->demes->port != 9999)
      retval = 0;
   if (opts->demes->options.population_size != 100)
      retval = 0;
   if (opts->demes->connections[0]->name != "127.0.0.2")
      retval = 0;
   if (opts->demes->connections[0]->transfer_interval != 1)
      retval = 0;
   if (opts->demes->connections[0]->transfer_count != 9)
      retval = 0;
   if (opts->demes->connections[1]->name != "127.0.0.3")
      retval = 0;
   if (opts->demes->connections[1]->transfer_interval != 2)
      retval = 0;
   if (opts->demes->connections[1]->transfer_count != 8)
      retval = 0;
   if (opts->demes->connections[2]->name != "127.0.0.4")
      retval = 0;
   if (opts->demes->connections[2]->transfer_interval != 3)
      retval = 0;
   if (opts->demes->connections[2]->transfer_count != 7)
      retval = 0;
   if (opts->demes->connections[3]->name != "127.0.0.5")
      retval = 0;
   if (opts->demes->connections[3]->transfer_interval != 4)
      retval = 0;
   if (opts->demes->connections[3]->transfer_count != 6)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int distributed_from_file_7() {
   DistributedOptions * opts = new DistributedOptions();

   bool res = PopulationOption::from_file("poptions/d6.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->demes->address != "127.0.0.1")
      retval = 0;
   if (opts->demes->port != 10000)
      retval = 0;
   if (opts->demes->options.population_size != 1000)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int distributed_from_file_8() {
   DistributedOptions * opts = new DistributedOptions();

   bool res = PopulationOption::from_file("poptions/d7.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->demes->address != "127.0.0.2")
      retval = 0;
   if (opts->demes->port != 10000)
      retval = 0;
   if (opts->demes->options.population_size != 1000)
      retval = 0;
   if (opts->demes->next->address != "127.0.0.1")
      retval = 0;
   if (opts->demes->next->port != 10000)
      retval = 0;
   if (opts->demes->next->options.population_size != 1000)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int distributed_from_file_9() {
   DistributedOptions * opts = new DistributedOptions();

   bool res = PopulationOption::from_file("poptions/d8.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->demes->address != "127.0.0.2")
      retval = 0;
   if (opts->demes->port != 10000)
      retval = 0;
   if (opts->demes->options.population_size != 999)
      retval = 0;
   if (opts->demes->next->address != "127.0.0.1")
      retval = 0;
   if (opts->demes->next->port != 9999)
      retval = 0;
   if (opts->demes->next->options.population_size != 1000)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int distributed_from_file_a() {
   DistributedOptions * opts = new DistributedOptions();

   bool res = PopulationOption::from_file("poptions/d9.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->demes->address != "127.0.0.1")
      retval = 0;
   if (opts->demes->port != 10000)
      retval = 0;
   if (opts->demes->options.population_size != 2934)
      retval = 0;
   if (opts->demes->options.maximum_generation != 23)
      retval = 0;
   if (opts->demes->options.maximum_elapsed != 8293.324)
      retval = 0;
   if (opts->demes->options.elitism_count != 184)
      retval = 0;
   if (opts->demes->options.tracking_mode != PopulationOption::TrackingMode::TRACKING_MODE_LIVE)
      retval = 0;
   if (opts->demes->options.min_fitness_change != 34.234)
      retval = 0;
   if (opts->demes->options.max_fitness != 4823.0)
      retval = 0;
   if (opts->demes->options.thread_count != std::thread::hardware_concurrency())
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int distributed_from_file_b() {
   DistributedOptions * opts = new DistributedOptions();

   bool res = PopulationOption::from_file("poptions/d10.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;
   if (opts->demes != NULL)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

int distributed_from_file_c() {
   DistributedOptions * opts = new DistributedOptions();

   bool res = PopulationOption::from_file("poptions/d11.ini",opts);

   int retval = 1;

   if (res != true)
      retval = 0;

   Deme * one = opts->demes->next->next;
   Deme * two = opts->demes->next;
   Deme * three = opts->demes;

   if (one->nickname != "one")
      retval = 0;
   if (one->address != "127.0.0.1")
      retval = 0;
   if (one->port != 10000)
      retval = 0;
   if (one->options.population_size != 1000)
      retval = 0;
   if (one->connections[0]->name != "two")
      retval = 0;
   if (one->connections[0]->transfer_interval != 5)
      retval = 0;
   if (one->connections[0]->transfer_count != 10)
      retval = 0;
   if (one->connections[1]->name != "127.0.0.3")
      retval = 0;
   if (one->connections[1]->transfer_interval != 10)
      retval = 0;
   if (one->connections[1]->transfer_count != 20)
      retval = 0;

   if (two->nickname != "two")
      retval = 0;
   if (two->address != "127.0.0.2")
      retval = 0;
   if (two->port != 10000)
      retval = 0;
   if (two->options.population_size != 1000)
      retval = 0;
   if (two->connections[0]->name != "127.0.0.1")
      retval = 0;
   if (two->connections[0]->transfer_interval != 20)
      retval = 0;
   if (two->connections[0]->transfer_count != 30)
      retval = 0;
   if (two->connections[1]->name != "three")
      retval = 0;
   if (two->connections[1]->transfer_interval != 30)
      retval = 0;
   if (two->connections[1]->transfer_count != 40)
      retval = 0;

   if (three->nickname != "three")
      retval = 0;
   if (three->address != "127.0.0.3")
      retval = 0;
   if (three->port != 10000)
      retval = 0;
   if (three->options.population_size != 1000)
      retval = 0;
   if (three->connections[0]->name != "one")
      retval = 0;
   if (three->connections[0]->transfer_interval != 40)
      retval = 0;
   if (three->connections[0]->transfer_count != 50)
      retval = 0;
   if (three->connections[1]->name != "127.0.0.2")
      retval = 0;
   if (three->connections[1]->transfer_interval != 50)
      retval = 0;
   if (three->connections[1]->transfer_count != 60)
      retval = 0;

   PopulationOption::free_configuration(opts);
   return retval;
}

}

}
