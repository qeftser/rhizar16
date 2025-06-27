
#include "population.h"
#include "chromosome.h"
#include "selection.h"
#include "roulette_selection.h"
#include "num_string.h"
#include "utils.h"
#include <math.h>
#include <limits.h>
#include <stdint.h>
#include <unordered_map>
#include <functional>

#define __RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__ 1000

typedef Rhizar16::NumString<unsigned int,__RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__> gene;

struct node {
   double x;
   double y;
};

double dist(struct node & a, struct node & b) {
   return std::sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double fitness(std::unordered_map<int,node> * nodes, const gene * g) {
   double dist_sum = 0;

   for (int i = 0; i < __RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__ - 1; ++i)
      dist_sum += dist((*nodes)[g->values[i]],(*nodes)[g->values[i+1]]);

   return 1000.0 / dist_sum;
}

double randfloat(double min, double max) {
   static Rhizar16::UniformRand rnd;
   double step = max - min;

   double raw = (double)rnd.random() / ULLONG_MAX;
   raw *= step;
   raw += min;

   return raw;
}

void initializer(gene * g) {
   static Rhizar16::UniformRand rnd;

   for (int i = 0; i < __RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__; ++i)
      g->values[i] = i;

   int toswap = 0;
   while (rnd.random() > (ULLONG_MAX >> 3)) toswap += 1;

   for (int i = 0; i < toswap; ++i) {
      uint64_t pos0 = rnd.random() % __RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__;
      uint64_t pos1 = rnd.random() % __RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__;
      if (pos0 == pos1) continue;

      g->values[pos0] ^= g->values[pos1];
      g->values[pos1] ^= g->values[pos0];
      g->values[pos0] ^= g->values[pos1];
   }
}

int main(void) {

   std::unordered_map<int,node> nodes;

   for (int i = 0; i < __RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__; ++i)
      nodes[i] = node{randfloat(-50,50),randfloat(-30,30)};

   auto ff = std::bind(fitness,&nodes,std::placeholders::_1);

   Rhizar16::RouletteSelector<gene,2,2> selector(gene::ordered_crossover);

   Rhizar16::PopulationOptions opts;

   opts.population_size = 250;
   opts.elitism_count = 10;
   opts.maximum_generation = 10000;
   opts.min_average_fitness_change = 1e-10;
   opts.tracking_mode = 1;

   Rhizar16::Population<gene> p(&opts);

   p.set_fitness(ff);
   p.set_evolution(selector.as_function());
   p.initialize(initializer);

   p.sort_population();
   printf("best before: %f\n",p.population()[0]->fitness);
   for (int i = 0; i < __RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__; ++i)
      printf("%d,",p.population()[0]->value->values[i]);
   printf("\n");

   p.simulate();
   printf("\n");

   p.sort_population();
   printf("best after: %f\n",p.population()[0]->fitness);
   for (int i = 0; i < __RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__; ++i)
      printf("%d,",p.population()[0]->value->values[i]);
   printf("\n");

   return 0;
}
