
#include "population_options.h"
#include "file_opts.h"
#include "wired_misc.h"
#include "utils.h"
#include <algorithm>
#include <thread>

namespace Rhizar16 {

namespace PopulationOption {

bool from_file(std::string path, struct Rhizar16::PopulationOptions * opts, bool print_failure, std::string section) {

   FileOptions file = FileOptions(path);

   if (file.status() != FileOptions::Status::SUCCESS) {
      if (print_failure)
         RHIZAR16_ERROR("Loading PopulationOptions%s\n",file.perror("").c_str());
      return false;
   }

   if (!file.has_section(section)) {
      if (print_failure)
         RHIZAR16_ERROR("Loading PopulationOptions: "
                        "Expected section \"%s\" not found\n",section.c_str());
      return false;
   }

   if (!file.has_key(section,"Size")) {
      if (print_failure)
         RHIZAR16_ERROR("Loading PopulationOptions in section %s: "
                        "Required key \"Size\" not found\n",section.c_str());
      return false;
   }

   opts->population_size = file.getopt_int(section,"Size");
   if (file.status() != FileOptions::Status::SUCCESS && print_failure)
      RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                    "Unable to parse value for field \"Size\"\n",section.c_str());

   if (file.has_key(section,"MaximumGeneration")) {
      opts->maximum_generation = file.getopt_int(section,"MaximumGeneration");
      if (file.status() != FileOptions::Status::SUCCESS && print_failure)
         RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                       "Unable to parse value for field \"MaximumGeneration\"\n",section.c_str());
   }

   if (file.has_key(section,"MaximumElapsed")) {
      opts->maximum_elapsed = file.getopt_flt(section,"MaximumElapsed");
      if (file.status() != FileOptions::Status::SUCCESS && print_failure)
         RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                       "Unable to parse value for field \"MaximumElapsed\"\n",section.c_str());
   }

   if (file.has_key(section,"ElitismCount")) {
      opts->elitism_count = file.getopt_int(section,"ElitismCount");
      if (file.status() != FileOptions::Status::SUCCESS && print_failure)
         RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                       "Unable to parse value for field \"ElitismCount\"\n",section.c_str());
   }

   if (file.has_key(section,"TrackingMode")) {

      if (file.getopt_str(section,"TrackingMode") == std::string("live") ||
          file.getopt_int(section,"TrackingMode") == 2) {

         opts->tracking_mode = PopulationOption::TrackingMode::TRACKING_MODE_LIVE;
      }

      else if (file.getopt_str(section,"TrackingMode") == std::string("verbose") ||
               file.getopt_int(section,"TrackingMode") == 1) {

         opts->tracking_mode = PopulationOption::TrackingMode::TRACKING_MODE_VERBOSE;
      }

      else if (file.getopt_str(section,"TrackingMode") == std::string("none") ||
               file.getopt_int(section,"TrackingMode") == 0) {

         if (file.status() != FileOptions::Status::SUCCESS && print_failure)
            RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                          "Unable to parse value for field \"TrackingMode\"\n",section.c_str());

         opts->tracking_mode = PopulationOption::TrackingMode::TRACKING_MODE_NONE;
      }
   }

   if (file.has_key(section,"MinFitnessChange")) {
      opts->min_fitness_change = file.getopt_flt(section,"MinFitnessChange");
      if (file.status() != FileOptions::Status::SUCCESS && print_failure)
         RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                       "Unable to parse value for field \"MinFitnessChange\"\n",section.c_str());
   }

   if (file.has_key(section,"MaxFitness")) {
      opts->max_fitness = file.getopt_flt(section,"MaxFitness");
      if (file.status() != FileOptions::Status::SUCCESS && print_failure)
         RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                       "Unable to parse value for field \"MaxFitness\"\n",section.c_str());
   }

   if (file.has_key(section,"ThreadCount")) {
      if (file.getopt_str(section,"ThreadCount") == "auto") {
         opts->thread_count = std::thread::hardware_concurrency();
      }
      else {
         opts->thread_count = file.getopt_int(section,"ThreadCount");
         if (file.status() != FileOptions::Status::SUCCESS && print_failure)
            RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                          "Unable to parse value for field \"ThreadCount\"\n",section.c_str());
      }
   }

   return true;
}

void print_configuration(struct Rhizar16::PopulationOptions * opts) {
   printf("PopulationOptions:\n");
   printf("\tFreeOnExit:        %s\n",opts->free_on_exit ? "TRUE" : "FALSE");
   printf("\tPopulationSize:    %u\n",opts->population_size);
   printf("\tMaximumGeneration: %u\n",opts->maximum_generation);
   printf("\tMaximumElapsed:    %f\n",opts->maximum_elapsed);
   printf("\tElitismCount:      %u\n",opts->elitism_count);
   switch (opts->tracking_mode) {
      case PopulationOption::TrackingMode::TRACKING_MODE_NONE:
         printf("\tTrackingMode:      NONE\n");
         break;
      case PopulationOption::TrackingMode::TRACKING_MODE_VERBOSE:
         printf("\tTrackingMode:      VERBOSE\n");
         break;
      case PopulationOption::TrackingMode::TRACKING_MODE_LIVE:
         printf("\tTrackingMode:      LIVE\n");
         break;
      default:
         printf("\tTrackingMode:      UNKNOWN\n");
         break;
   }
   printf("\tMinFitnessChange:  %f\n",opts->min_fitness_change);
   printf("\tMaxFitness:        %f\n",opts->max_fitness);
   printf("\tThreadCount:       %u\n",opts->thread_count);
   printf("\tFinished:          %s\n",opts->finish ? "TRUE" : "FALSE");
}

bool from_file(std::string path, struct Rhizar16::MasterSlaveOptions * opts, bool print_failure) {

   FileOptions file = FileOptions(path);

   if (file.status() != FileOptions::Status::SUCCESS) {
      if (print_failure)
         RHIZAR16_ERROR("Loading MasterSlaveOptions%s\n",file.perror("").c_str());
      return false;
   }

   std::vector<std::string> sections;
   file.collect_sections(sections);

   bool master_found = false;
   std::string master_section;

   if (file.has_section("Master")) {

      master_section = "Master";
      master_found = true;
   }
   else {
      for (std::string & section : sections) {
         if (file.has_key(section,"Designation") &&
             file.getopt_str(section,"Designation") == "master") {

            master_section = section;
            master_found = true;
         }
      }
   }

   if (!master_found) {
      if (print_failure) {
         RHIZAR16_ERROR("Loading MasterSlaveOptions: "
                        "Failed to find section labled \"Master\" "
                        "or section with \"Designation\" key set to \"master\"\n");
      }
      return false;
   }

   if (!from_file(path,&opts->master_options,print_failure,master_section))
      return false;

   if (file.has_key(master_section,"Address")) {
      opts->master_address = file.getopt_str(master_section,"Address");
   }
   else {
      if (master_section == "Master" && print_failure)
         RHIZAR16_WARN("Loading MasterSlaveOptions: "
                       "No \"Address\" field found in master section, "
                       "setting address to \"Master\" per parsing rules\n");
      opts->master_address = master_section;
   }

   if (file.has_key(master_section,"Port")) {
      opts->master_port = file.getopt_int(master_section,"Port");
      if (file.status() != FileOptions::Status::SUCCESS && print_failure)
         RHIZAR16_WARN("Loading MasterSlaveOptions: "
                       "in section %s: Unable to parse value for field \"Port\"\n",master_section.c_str());
   }
   else {
      if (print_failure)
         RHIZAR16_ERROR("Loading MasterSlaveOptions: "
                        "Required Master Field \"Port\" not found in section %s\n",master_section.c_str());
      return false;
   }

   sections.erase(std::remove(sections.begin(), sections.end(), master_section), sections.end());

   for (std::string & section : sections) {

      struct SlaveOptions * s_opts = new SlaveOptions;

      if (file.has_key(section,"Address")) {
         s_opts->slave_address = file.getopt_str(section,"Address");
      }
      else {
         s_opts->slave_address = section;
      }

      if (file.has_key(section,"ThreadCount")) {
         if (file.getopt_str(section,"ThreadCount") == "auto") {
            s_opts->thread_count = std::thread::hardware_concurrency();
         }
         else {
            s_opts->thread_count = file.getopt_int(section,"ThreadCount");
            if (file.status() != FileOptions::Status::SUCCESS && print_failure)
               RHIZAR16_WARN("Loading MasterSlaveOptions in section %s: "
                             "Unable to parse value for field \"ThreadCount\"\n",section.c_str());
         }
      }

      s_opts->next = opts->slaves;
      opts->slaves = s_opts;
   }

   return true;
}

void print_configuration(struct Rhizar16::MasterSlaveOptions * opts) {

   if (Rhizar16::Wired::is_self(opts->master_address)) {

      printf("MasterSlaveOptions [MASTER]:\n");
      printf("\tAddress:           %s\n",opts->master_address.c_str());
      printf("\tPort:              %u\n",opts->master_port);
      printf("\tFreeOnExit:        %s\n",opts->free_on_exit ? "TRUE" : "FALSE");
      printf("\tPopulationSize:    %u\n",opts->master_options.population_size);
      printf("\tMaximumGeneration: %u\n",opts->master_options.maximum_generation);
      printf("\tMaximumElapsed:    %f\n",opts->master_options.maximum_elapsed);
      printf("\tElitismCount:      %u\n",opts->master_options.elitism_count);
      switch (opts->master_options.tracking_mode) {
         case PopulationOption::TrackingMode::TRACKING_MODE_NONE:
            printf("\tTrackingMode:      NONE\n");
            break;
         case PopulationOption::TrackingMode::TRACKING_MODE_VERBOSE:
            printf("\tTrackingMode:      VERBOSE\n");
            break;
         case PopulationOption::TrackingMode::TRACKING_MODE_LIVE:
            printf("\tTrackingMode:      LIVE\n");
            break;
         default:
            printf("\tTrackingMode:      UNKNOWN\n");
            break;
      }
      printf("\tMinFitnessChange:  %f\n",opts->master_options.min_fitness_change);
      printf("\tMaxFitness:        %f\n",opts->master_options.max_fitness);
      printf("\tThreadCount:       %u\n",opts->master_options.thread_count);
      printf("\tFinished:          %s\n",opts->master_options.finish ? "TRUE" : "FALSE");

   }
   else {

      struct Rhizar16::SlaveOptions * curr = opts->slaves;

      while (curr) {

         if (Rhizar16::Wired::is_self(curr->slave_address) ||
             curr->slave_address == Rhizar16::PopulationOption::ADDRESS_ANY) {

            printf("MasterSlaveOptions [SLAVE]:\n");
            printf("\tAddress:     %s\n",curr->slave_address.c_str());
            printf("\tThreadCount: %u\n",curr->thread_count);
            printf("\tFreeOnExit:  %s\n",opts->free_on_exit ? "TRUE" : "FALSE");
            printf("\t[MASTER]:\n");
            printf("\t\tAddress: %s\n",opts->master_address.c_str());
            printf("\t\tPort:    %u\n",opts->master_port);
            return;

         }

         curr = curr->next;
      }

      printf("MasterSlaveOptions: Device Not Configured\n");

   }

}

void free_configuration(struct Rhizar16::MasterSlaveOptions * opts) {

   struct SlaveOptions * next, * curr = opts->slaves;

   while (curr) {

      next = curr->next;
      delete curr;
      curr = next;
   }

   delete opts;
}

bool from_file(std::string path, struct Rhizar16::DistributedOptions * opts, bool print_failure) {

   FileOptions file = FileOptions(path);

   if (file.status() != FileOptions::Status::SUCCESS) {
      if (print_failure)
         RHIZAR16_ERROR("Loading DistributedOptions%s\n",file.perror("").c_str());
      return false;
   }

   std::vector<std::string> sections;
   file.collect_sections(sections);

   struct Rhizar16::PopulationOptions default_options;
   uint16_t default_port = 0;

   struct Rhizar16::Deme * d_opts = NULL;

   if (file.has_section("Default")) {

      from_file(path,&default_options,print_failure,"Default");

      if (file.has_key("Default","Port")) {

         default_port = file.getopt_int("Default","Port");

         if (file.status() != FileOptions::Status::SUCCESS && print_failure)
            RHIZAR16_WARN("Loading DistributedOptions: "
                          "Unable to parse value for \"Port\" in section \"Default\"\n");
      }

      sections.erase(std::remove(sections.begin(), sections.end(), "Default"), sections.end());
   }

   for (std::string & section : sections) {

      d_opts = new Rhizar16::Deme();

      std::vector<std::string> keys;
      file.collect_keys(section,keys);

      if (file.has_key(section,"Address")) {
         d_opts->address = file.getopt_str(section,"Address");
         d_opts->nickname = section;

         keys.erase(std::remove(keys.begin(), keys.end(), "Address"), keys.end());
      }
      else {
         d_opts->address = section;
         d_opts->nickname = "";
      }

      if (file.has_key(section,"Nickname")) {
         d_opts->nickname = file.getopt_str(section,"Nickname");

         keys.erase(std::remove(keys.begin(), keys.end(), "Nickname"), keys.end());
      }

      if (file.has_key(section,"Port")) {

         d_opts->port = file.getopt_int(section,"Port");

         if (file.status() != FileOptions::Status::SUCCESS && print_failure)
            RHIZAR16_WARN("Loading DistributedOptions: "
                          "Unable to parse field \"Port\" in section %s\n",section.c_str());

         keys.erase(std::remove(keys.begin(), keys.end(), "Port"), keys.end());
      }
      else if (default_port != 0)
         d_opts->port = default_port;
      else {
         if (print_failure)
            RHIZAR16_ERROR("Loading DistributedOptions: "
                           "Required field \"Port\" not provided in section %s, "
                           "no default specified\n",section.c_str());
         goto cleanup;
      }

      if (!file.has_key(section,"Size")) {

         if (default_options.population_size != 0) 
            d_opts->options.population_size = default_options.population_size;
         else {
            if (print_failure)
               RHIZAR16_ERROR("Loading PopulationOptions in section %s: "
                              "Required key \"Size\" not found, and default not set\n",section.c_str());
            goto cleanup;
         }
      }
      else {
         d_opts->options.population_size = file.getopt_int(section,"Size");
         if (file.status() != FileOptions::Status::SUCCESS && print_failure)
            RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                          "Unable to parse value for field \"Size\"\n",section.c_str());

         keys.erase(std::remove(keys.begin(), keys.end(), "Size"), keys.end());
      }

      if (file.has_key(section,"MaximumGeneration")) {
         d_opts->options.maximum_generation = file.getopt_int(section,"MaximumGeneration");
         if (file.status() != FileOptions::Status::SUCCESS && print_failure)
            RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                          "Unable to parse value for field \"MaximumGeneration\"\n",section.c_str());

         keys.erase(std::remove(keys.begin(), keys.end(), "MaximumGeneration"), keys.end());
      }
      else if (default_options.maximum_generation != 0)
         d_opts->options.maximum_generation = default_options.maximum_generation;

      if (file.has_key(section,"MaximumElapsed")) {
         d_opts->options.maximum_elapsed = file.getopt_flt(section,"MaximumElapsed");
         if (file.status() != FileOptions::Status::SUCCESS && print_failure)
            RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                          "Unable to parse value for field \"MaximumElapsed\"\n",section.c_str());

         keys.erase(std::remove(keys.begin(), keys.end(), "MaximumElapsed"), keys.end());
      }
      else if (default_options.maximum_elapsed != 0.0)
         d_opts->options.maximum_elapsed = default_options.maximum_elapsed;

      if (file.has_key(section,"ElitismCount")) {
         d_opts->options.elitism_count = file.getopt_int(section,"ElitismCount");
         if (file.status() != FileOptions::Status::SUCCESS && print_failure)
            RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                          "Unable to parse value for field \"ElitismCount\"\n",section.c_str());

         keys.erase(std::remove(keys.begin(), keys.end(), "ElitismCount"), keys.end());
      }
      else if (default_options.elitism_count != 0)
         d_opts->options.elitism_count = default_options.elitism_count;

      if (file.has_key(section,"TrackingMode")) {

         if (file.getopt_str(section,"TrackingMode") == std::string("live") ||
             file.getopt_int(section,"TrackingMode") == 2) {

            d_opts->options.tracking_mode = PopulationOption::TrackingMode::TRACKING_MODE_LIVE;
         }

         else if (file.getopt_str(section,"TrackingMode") == std::string("verbose") ||
                  file.getopt_int(section,"TrackingMode") == 1) {

            d_opts->options.tracking_mode = PopulationOption::TrackingMode::TRACKING_MODE_VERBOSE;
         }

         else if (file.getopt_str(section,"TrackingMode") == std::string("none") ||
                  file.getopt_int(section,"TrackingMode") == 0) {

            if (file.status() != FileOptions::Status::SUCCESS && print_failure)
               RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                             "Unable to parse value for field \"TrackingMode\"\n",section.c_str());

            d_opts->options.tracking_mode = PopulationOption::TrackingMode::TRACKING_MODE_NONE;
         }

         keys.erase(std::remove(keys.begin(), keys.end(), "TrackingMode"), keys.end());
      }
      else if (default_options.tracking_mode != 0)
         d_opts->options.tracking_mode = default_options.tracking_mode;

      if (file.has_key(section,"MinFitnessChange")) {
         d_opts->options.min_fitness_change = file.getopt_flt(section,"MinFitnessChange");
         if (file.status() != FileOptions::Status::SUCCESS && print_failure)
            RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                          "Unable to parse value for field \"MinFitnessChange\"\n",section.c_str());

         keys.erase(std::remove(keys.begin(), keys.end(), "MinFitnessChange"), keys.end());
      }
      else if (default_options.min_fitness_change != 0.0)
         d_opts->options.min_fitness_change = default_options.min_fitness_change;

      if (file.has_key(section,"MaxFitness")) {
         d_opts->options.max_fitness = file.getopt_flt(section,"MaxFitness");
         if (file.status() != FileOptions::Status::SUCCESS && print_failure)
            RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                          "Unable to parse value for field \"MaxFitness\"\n",section.c_str());

         keys.erase(std::remove(keys.begin(), keys.end(), "MaxFitness"), keys.end());
      }
      else if (default_options.max_fitness != 0.0)
         d_opts->options.max_fitness = default_options.max_fitness;

      if (file.has_key(section,"ThreadCount")) {
         if (file.getopt_str(section,"ThreadCount") == "auto") {
            d_opts->options.thread_count = std::thread::hardware_concurrency();
         }
         else {
            d_opts->options.thread_count = file.getopt_int(section,"ThreadCount");
            if (file.status() != FileOptions::Status::SUCCESS && print_failure)
               RHIZAR16_WARN("Loading PopulationOptions in section %s: "
                             "Unable to parse value for field \"ThreadCount\"\n",section.c_str());
         }

         keys.erase(std::remove(keys.begin(), keys.end(), "ThreadCount"), keys.end());
      }
      else if (default_options.thread_count != 0)
         d_opts->options.thread_count = default_options.thread_count;

      for (std::string & key : keys) {

         struct Rhizar16::DemeConnection * c_opts = new Rhizar16::DemeConnection();

         c_opts->name = key;

         std::string values = file.getopt_str(section,key);

         size_t split_pos = values.find_first_of('@');

         if (split_pos == std::string::npos) {
            if (print_failure)
               RHIZAR16_WARN("Loading DemeConnection: "
                             "Unable to parse values for connection %s in "
                             "section %s, no seperator '@' found\n",key.c_str(),section.c_str());
            delete c_opts;
            continue;
         }

         std::string interval = values.substr(0,split_pos);
         std::string count    = values.substr(split_pos+1,std::string::npos);

         {
            errno = 0;
            char * endpos;
            const char * str = interval.c_str();
            long res = strtol(str,&endpos,0);
            if (errno || str == endpos) {

               if (print_failure)
                  RHIZAR16_WARN("Loading DemeConnection: "
                                "Unable to parse transfer interval for connection %s in "
                                "section %s, bad number format\n",key.c_str(),section.c_str());
               delete c_opts;
               continue;
            }
            else {
               c_opts->transfer_interval = res;
            }
         }

         {
            errno = 0;
            char * endpos;
            const char * str = count.c_str();
            long res = strtol(str,&endpos,0);
            if (errno || str == endpos) {

               if (print_failure)
                  RHIZAR16_WARN("Loading DemeConnection: "
                                "Unable to parse transfer count for connection %s in "
                                "section %s, bad number format\n",key.c_str(),section.c_str());
               delete c_opts;
               continue;
            }
            else {
               c_opts->transfer_count = res;
            }
         }

         d_opts->connections.push_back(c_opts);
      }

      d_opts->next = opts->demes;
      opts->demes = d_opts;
      d_opts = NULL;
   }

   return true;

cleanup:
   {

      Rhizar16::Deme * next, * curr = opts->demes;

      while (curr) {
         next = curr->next;

         for (Rhizar16::DemeConnection * conn : curr->connections)
            delete conn;

         delete curr;

         curr = next;
      }

      delete d_opts;
      opts->demes = NULL;
   }
   return false;
}

void print_configuration(struct Rhizar16::DistributedOptions * opts) {

   struct Rhizar16::Deme * curr = opts->demes;

   while (curr) {

      if (Rhizar16::Wired::is_self(curr->address)) {

         printf("DistributedOptions:\n");
         printf("\tNickname:          %s\n",curr->nickname.c_str());
         printf("\tAddress:           %s\n",curr->address.c_str());
         printf("\tPort:              %u\n",curr->port);
         printf("\tFreeOnExit:        %s\n",opts->free_on_exit ? "TRUE" : "FALSE");
         printf("\tPopulationSize:    %u\n",curr->options.population_size);
         printf("\tMaximumGeneration: %u\n",curr->options.maximum_generation);
         printf("\tMaximumElapsed:    %f\n",curr->options.maximum_elapsed);
         printf("\tElitismCount:      %u\n",curr->options.elitism_count);
         switch (curr->options.tracking_mode) {
            case PopulationOption::TrackingMode::TRACKING_MODE_NONE:
               printf("\tTrackingMode:      NONE\n");
               break;
            case PopulationOption::TrackingMode::TRACKING_MODE_VERBOSE:
               printf("\tTrackingMode:      VERBOSE\n");
               break;
            case PopulationOption::TrackingMode::TRACKING_MODE_LIVE:
               printf("\tTrackingMode:      LIVE\n");
               break;
            default:
               printf("\tTrackingMode:      UNKNOWN\n");
               break;
         }
         printf("\tMinFitnessChange:  %f\n",curr->options.min_fitness_change);
         printf("\tMaxFitness:        %f\n",curr->options.max_fitness);
         printf("\tThreadCount:       %u\n",curr->options.thread_count);
         printf("\tFinished:          %s\n",curr->options.finish ? "TRUE" : "FALSE");
         printf("\t[OUTGOING CONNECTIONS]:\n");

         for (Rhizar16::DemeConnection * conn : curr->connections) {

            struct Rhizar16::Deme * curr2 = opts->demes;

            bool found_outgoing = false;
            while (curr2) {

               if (curr2->address == curr->address) {
                  curr2 = curr2->next;
                  continue;
               }

               if (curr2->address  == conn->name ||
                   curr2->nickname == conn->name   ) {

                  printf("\t\t%s:\n",conn->name.c_str());
                  printf("\t\t\tAddress:          %s\n",curr2->address.c_str());
                  printf("\t\t\tPort:             %u\n",curr2->port);
                  printf("\t\t\tTransferInterval: %u\n",conn->transfer_interval);
                  printf("\t\t\tTransferCount:    %u\n",conn->transfer_count);

                  found_outgoing = true;
                  break;
               }

               curr2 = curr2->next;
            }

            if (!found_outgoing) {
               printf("\t\t%s: No Deme Found With Given Address\n",conn->name.c_str());
            }
         }

         printf("\t[INCOMING CONNECTIONS]:\n");

         struct Rhizar16::Deme * curr3 = opts->demes;

         while (curr3) {

            for (Rhizar16::DemeConnection * conn2 : curr3->connections) {

               if (conn2->name == curr->address ||
                   conn2->name == curr->nickname  ) {

                  printf("\t\t%s:\n",curr3->nickname == "" ? curr3->address.c_str() : curr3->nickname.c_str());
                  printf("\t\t\tAddress:          %s\n",curr3->address.c_str());
                  printf("\t\t\tPort:             %u\n",curr3->port);
                  printf("\t\t\tTransferInterval: %u\n",conn2->transfer_interval);
                  printf("\t\t\tTransferCount:    %u\n",conn2->transfer_count);

                  break;
               }
            }
            
            curr3 = curr3->next;
         }

         return;
      }

      curr = curr->next;
   }

   printf("DistributedOptions: Device Not Configured\n");
}

void free_configuration(struct Rhizar16::DistributedOptions * opts) {

   Rhizar16::Deme * next, * curr = opts->demes;

   while (curr) {
      next = curr->next;

      for (Rhizar16::DemeConnection * conn : curr->connections)
         delete conn;

      delete curr;

      curr = next;
   }

   delete opts;
}

}

}

