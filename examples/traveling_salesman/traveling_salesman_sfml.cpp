
#include "population.h"
#include "chromosome.h"
#include "selection.h"
#include "roulette_selection.h"
#include "rank_selection.h"
#include "random_selection.h"
#include "tournament_selection.h"
#include "num_string.h"
#include "utils.h"
#include <math.h>
#include <limits.h>
#include <stdint.h>
#include <unordered_map>
#include <functional>

#include <SFML/Graphics.hpp>

#define __RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__ 50

typedef Rhizar16::NumString<unsigned int,__RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__> gene;

struct node {
   double x;
   double y;
};

struct visual {
   std::unordered_map<int,node> * nodes;
   sf::RenderWindow             * window;
   sf::View                     * view;
};

int draw_function(Rhizar16::Chromosome<gene> ** pop, int length, void * arg) {

   struct visual * vis = (struct visual *)arg;

   Rhizar16::Chromosome<gene> * best = pop[0];

   for (int i = 1; i < length; ++i)
      if (pop[i]->fitness > best->fitness)
         best = pop[i];

   vis->window->clear();
   vis->window->setView(*vis->view);

   sf::Vertex point[2];
   for (int i = 0; i < __RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__ - 1; ++i) {

      point[0].position = sf::Vector2f(vis->nodes->at(best->value->values[i  ]).x,
                                       vis->nodes->at(best->value->values[i  ]).y);
      point[1].position = sf::Vector2f(vis->nodes->at(best->value->values[i+1]).x,
                                       vis->nodes->at(best->value->values[i+1]).y);
      vis->window->draw(point,2,sf::Lines);
   }

   vis->window->display();

   return 0;
}

double dist(struct node & a, struct node & b) {
   return ((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double fitness(std::unordered_map<int,node> * nodes, const gene * g) {
   double dist_sum = 0;

   for (int i = 0; i < __RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__ - 1; ++i)
      dist_sum += dist((*nodes)[g->values[i]],(*nodes)[g->values[i+1]]);

   return 100000.0 / dist_sum;
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

   sf::RenderWindow window;
   sf::View view = sf::View();
   window.create(sf::VideoMode(1500,1200),"traveling salesman");
   window.setFramerateLimit(30);
   view.setCenter(0,0);
   view.setSize(window.getSize().x,window.getSize().y);
   view.zoom(0.075);

   struct visual vis;
   vis.nodes = &nodes;
   vis.window = &window;
   vis.view = &view;

   for (int i = 0; i < __RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__; ++i)
      nodes[i] = node{randfloat(-50,50),randfloat(-30,30)};

   auto ff = std::bind(fitness,&nodes,std::placeholders::_1);
   auto mute = gene::interchange(0.075);

   Rhizar16::RankSelector<gene,2,1> 
      selector(gene::precedence_preservative_crossover,mute);

   Rhizar16::PopulationOptions opts;

   opts.population_size = 150;
   opts.elitism_count = 0;
   opts.maximum_generation = 1000000;
   opts.min_fitness_change = 1e-10;
   opts.tracking_mode = 1;
   //opts.thread_count = 8;

   Rhizar16::Population<gene> p(&opts);

   p.set_fitness(ff);
   p.set_evolution(selector.as_function());
   p.add_after(0,draw_function,(void *)&vis);
   p.initialize(initializer);

   p.simulate();
   printf("\n");

   p.sort_population();
   printf("best after: %f\n",p.population()[0]->fitness);
   for (int i = 0; i < __RHIZAR16_TRAVELING_SALESMAN_GRAPH_SIZE__; ++i)
      printf("%d,",p.population()[0]->value->values[i]);
   printf("\n");

   getchar();

   window.close();

   return 0;
}
