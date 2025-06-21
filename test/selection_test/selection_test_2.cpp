
#include "selection_test.h"
#include <limits.h>

namespace Rhizar16 {

namespace TestSelection2 {

void simulate_random_selection(Chromosome<int> * values, int length, int count,
                               std::vector<Chromosome<int> *> & collected, uint64_t * rnd) {

   for (int i = 0; i < count; ++i) {

      collected.push_back(&values[*(rnd++) % length]);

   }

}


void simulate_rank_selection(Chromosome<int> * values, int length, int count,
                             std::vector<Chromosome<int> *> & collected, uint64_t * rnd) {

   for (int i = 0; i < count; ++i) {

      Chromosome<int> * opt0 = &values[*(rnd++) % length];
      Chromosome<int> * opt1 = &values[*(rnd++) % length];

      if (opt0->fitness < opt1->fitness)
         collected.push_back(opt1);
      else
         collected.push_back(opt0);

   }

}

void simulate_roulette_selection(Chromosome<int> * values, int length, int count,
                                 std::vector<Chromosome<int> *> & collected, uint64_t * rnd) {

   uint64_t slots[length];
   slots[length-1] = ULLONG_MAX;

   double fitness_sum = 0.0;
   for (int i = 0; i < length; ++i)
      fitness_sum += values[i].fitness;

   if (length != 1)
      slots[0] = ((double)ULLONG_MAX * (values[0].fitness / fitness_sum));
   for (int i = 1; i < length - 1; ++i)
      slots[i] = slots[i-1] + ((double)ULLONG_MAX * (values[i].fitness / fitness_sum));

   for (int i = 0; i < count; ++i) {

      uint64_t val = *(rnd++);
      int pos = 0;

      while (slots[pos] < val) ++pos;

      collected.push_back(&values[pos]);

   }

}

void simulate_stochastic_selection(Chromosome<int> * values, int length, int count,
                                   std::vector<Chromosome<int> *> & collected, uint64_t * rnd) {

   uint64_t pstep = ULLONG_MAX / count;

   unsigned int pos = 0;
   uint64_t ppos = 0;

   uint64_t slots[length];
   slots[length-1] = ULLONG_MAX;

   double fitness_sum = 0.0;
   for (int i = 0; i < length; ++i) {
      fitness_sum += values[i].fitness;
   }

   if (length != 1)
      slots[0] = ((double)ULLONG_MAX * (values[0].fitness / fitness_sum));
   for (int i = 1; i < length - 1; ++i) {
      slots[i] = slots[i-1] + ((double)ULLONG_MAX * (values[i].fitness / fitness_sum));
   }

   for (int i = 0; i < count; ++i) {

      collected.push_back(&values[pos]);

      ppos += pstep;
      while (ppos > slots[pos])
         pos += 1;
   }
}

void simulate_tournament_selection(int t_size, Chromosome<int> * values, int length, int count,
                                   std::vector<Chromosome<int> *> & collected, uint64_t * rnd) {

   for (int i = 0; i < count; ++i) {

      Chromosome<int> * best = &values[*(rnd++) % length];
      for (int i = 0; i < t_size-1; ++i) {
         Chromosome<int> * canidate = &values[*(rnd++) % length];
         if (canidate->fitness > best->fitness)
            best = canidate;
      }

      collected.push_back(best);
   }

}

int random_selection_0() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[1] = { 3 };

   simulate_random_selection(choices,20,1,collected,rnd);

   int retval = 1;

   if (collected.size() != 1)
      retval = 0;

   if (*(collected[0]->value) != 3)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

int random_selection_1() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[3] = { 40, 60, 80 };

   simulate_random_selection(choices,20,3,collected,rnd);

   int retval = 1;

   if (collected.size() != 3)
      retval = 0;

   if (*(collected[0]->value) != 0)
      retval = 0;
   if (*(collected[1]->value) != 0)
      retval = 0;
   if (*(collected[2]->value) != 0)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

int random_selection_2() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[7] = { 1, 3, 5, 7, 11, 13, 17 };

   simulate_random_selection(choices,20,7,collected,rnd);

   int retval = 1;

   if (collected.size() != 7)
      retval = 0;

   if (*(collected[0]->value) != 1)
      retval = 0;
   if (*(collected[1]->value) != 3)
      retval = 0;
   if (*(collected[2]->value) != 5)
      retval = 0;
   if (*(collected[3]->value) != 7)
      retval = 0;
   if (*(collected[4]->value) != 11)
      retval = 0;
   if (*(collected[5]->value) != 13)
      retval = 0;
   if (*(collected[6]->value) != 17)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

int rank_selection_0() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = i;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[2] = { 1, 3 };

   simulate_rank_selection(choices,20,1,collected,rnd);

   int retval = 1;

   if (collected.size() != 1)
      retval = 0;

   if (*(collected[0]->value) != 3)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

int rank_selection_1() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = i;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[6] = { 1, 2, 4, 3, 7, 5 };

   simulate_rank_selection(choices,20,3,collected,rnd);

   int retval = 1;

   if (collected.size() != 3)
      retval = 0;

   if (*(collected[0]->value) != 2)
      retval = 0;
   if (*(collected[1]->value) != 4)
      retval = 0;
   if (*(collected[2]->value) != 7)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

int rank_selection_2() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = i;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[6] = { 1, 1, 1, 1, 1, 1 };

   simulate_rank_selection(choices,20,3,collected,rnd);

   int retval = 1;

   if (collected.size() != 3)
      retval = 0;

   if (*(collected[0]->value) != 1)
      retval = 0;
   if (*(collected[1]->value) != 1)
      retval = 0;
   if (*(collected[2]->value) != 1)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

int rank_selection_3() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = i;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[6] = { 21, 42, 64, 80, 105, 103 };

   simulate_rank_selection(choices,20,3,collected,rnd);

   int retval = 1;

   if (collected.size() != 3)
      retval = 0;

   if (*(collected[0]->value) != 2)
      retval = 0;
   if (*(collected[1]->value) != 4)
      retval = 0;
   if (*(collected[2]->value) != 5)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

int rank_selection_4() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = i;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[6] = { 42, 21, 80, 64, 103, 105 };

   simulate_rank_selection(choices,20,3,collected,rnd);

   int retval = 1;

   if (collected.size() != 3)
      retval = 0;

   if (*(collected[0]->value) != 2)
      retval = 0;
   if (*(collected[1]->value) != 4)
      retval = 0;
   if (*(collected[2]->value) != 5)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

int roulette_selection_0() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = 1;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t step = ULLONG_MAX / 20 + 0xff;
   uint64_t rnd[6] = { 0, step, step*2, step*3, step*4, step*5 };

   simulate_roulette_selection(choices,20,6,collected,rnd);

   int retval = 1;

   if (collected.size() != 6)
      retval = 0;

   if (*(collected[0]->value) != 0)
      retval = 0;
   if (*(collected[1]->value) != 1)
      retval = 0;
   if (*(collected[2]->value) != 2)
      retval = 0;
   if (*(collected[3]->value) != 3)
      retval = 0;
   if (*(collected[4]->value) != 4)
      retval = 0;
   if (*(collected[5]->value) != 5)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

int roulette_selection_1() {
   Chromosome<int> choices[5];
   for (int i = 0; i < 5; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = 1;
   }
   choices[0].fitness = 4;

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[6] = { 0, ULLONG_MAX / 2, ULLONG_MAX / 2 + 0xff, ULLONG_MAX };

   simulate_roulette_selection(choices,5,4,collected,rnd);

   int retval = 1;

   if (collected.size() != 4)
      retval = 0;

   if (*(collected[0]->value) != 0)
      retval = 0;
   if (*(collected[1]->value) != 0)
      retval = 0;
   if (*(collected[2]->value) != 1)
      retval = 0;
   if (*(collected[3]->value) != 4)
      retval = 0;

   for (int i = 0; i < 5; ++i)
      delete choices[i].value;

   return retval;
}

int roulette_selection_2() {
   Chromosome<int> choices[5];
   for (int i = 0; i < 5; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = 1;
   }
   choices[0].fitness = 3;
   choices[4].fitness = 3;

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[6] = { 0, ULLONG_MAX / 3 - 0xfff, ULLONG_MAX / 3 + 0xff, (ULLONG_MAX / 3) * 2, 
                       ((ULLONG_MAX / 3) * 2) + 0xfff, ULLONG_MAX };

   simulate_roulette_selection(choices,5,6,collected,rnd);

   int retval = 1;

   if (collected.size() != 6)
      retval = 0;

   if (*(collected[0]->value) != 0)
      retval = 0;
   if (*(collected[1]->value) != 0)
      retval = 0;
   if (*(collected[2]->value) != 1)
      retval = 0;
   if (*(collected[3]->value) != 3)
      retval = 0;
   if (*(collected[4]->value) != 4)
      retval = 0;
   if (*(collected[5]->value) != 4)
      retval = 0;

   for (int i = 0; i < 5; ++i)
      delete choices[i].value;

   return retval;
}

int roulette_selection_3() {
   Chromosome<int> choices[5];
   for (int i = 0; i < 5; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = -0.2;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[5] = { 0, ULLONG_MAX / 5 + 0xfff, ((ULLONG_MAX / 5)*2) + 0xfff,
                       ((ULLONG_MAX / 5)*3) + 0xfff, ((ULLONG_MAX / 5)*4) + 0xfff  };

   simulate_roulette_selection(choices,5,5,collected,rnd);

   int retval = 1;

   if (collected.size() != 5)
      retval = 0;

   if (*(collected[0]->value) != 0)
      retval = 0;
   if (*(collected[1]->value) != 1)
      retval = 0;
   if (*(collected[2]->value) != 2)
      retval = 0;
   if (*(collected[3]->value) != 3)
      retval = 0;
   if (*(collected[4]->value) != 4)
      retval = 0;

   for (int i = 0; i < 5; ++i)
      delete choices[i].value;

   return retval;
}

int roulette_selection_4() {
   Chromosome<int> choices[5];
   for (int i = 0; i < 5; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = 0;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[5] = { 0, ULLONG_MAX, 0, ULLONG_MAX, 0 };
                       

   simulate_roulette_selection(choices,5,5,collected,rnd);

   int retval = 1;

   if (collected.size() != 5)
      retval = 0;

   if (*(collected[0]->value) != 0)
      retval = 0;
   if (*(collected[1]->value) != 4)
      retval = 0;
   if (*(collected[2]->value) != 0)
      retval = 0;
   if (*(collected[3]->value) != 4)
      retval = 0;
   if (*(collected[4]->value) != 0)
      retval = 0;

   for (int i = 0; i < 5; ++i)
      delete choices[i].value;

   return retval;
}

int stochastic_selection_0() {
   Chromosome<int> choices[5];
   for (int i = 0; i < 5; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = 1;
   }

   std::vector<Chromosome<int> *> collected;

   simulate_stochastic_selection(choices,5,5,collected,NULL);

   int retval = 1;

   if (collected.size() != 5)
      retval = 0;

   if (*(collected[0]->value) != 0)
      retval = 0;
   if (*(collected[1]->value) != 0)
      retval = 0;
   if (*(collected[2]->value) != 1)
      retval = 0;
   if (*(collected[3]->value) != 2)
      retval = 0;
   if (*(collected[4]->value) != 3)
      retval = 0;

   for (int i = 0; i < 5; ++i)
      delete choices[i].value;

   return retval;
}

int stochastic_selection_1() {
   Chromosome<int> choices[5];
   for (int i = 0; i < 5; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = 1;
   }

   std::vector<Chromosome<int> *> collected;

   simulate_stochastic_selection(choices,5,10,collected,NULL);

   int retval = 1;

   if (collected.size() != 10)
      retval = 0;

   if (*(collected[0]->value) != 0)
      retval = 0;
   if (*(collected[1]->value) != 0)
      retval = 0;
   if (*(collected[2]->value) != 0)
      retval = 0;
   if (*(collected[3]->value) != 1)
      retval = 0;
   if (*(collected[4]->value) != 1)
      retval = 0;
   if (*(collected[5]->value) != 2)
      retval = 0;
   if (*(collected[6]->value) != 2)
      retval = 0;
   if (*(collected[7]->value) != 3)
      retval = 0;
   if (*(collected[8]->value) != 3)
      retval = 0;
   if (*(collected[9]->value) != 4)
      retval = 0;

   for (int i = 0; i < 5; ++i)
      delete choices[i].value;

   return retval;
}

int stochastic_selection_2() {
   Chromosome<int> choices[5];
   for (int i = 0; i < 5; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = 1;
   }
   choices[0].fitness = 4;

   std::vector<Chromosome<int> *> collected;

   simulate_stochastic_selection(choices,5,5,collected,NULL);

   int retval = 1;

   if (collected.size() != 5)
      retval = 0;

   if (*(collected[0]->value) != 0)
      retval = 0;
   if (*(collected[1]->value) != 0)
      retval = 0;
   if (*(collected[2]->value) != 0)
      retval = 0;
   if (*(collected[3]->value) != 1)
      retval = 0;
   if (*(collected[4]->value) != 3)
      retval = 0;

   for (int i = 0; i < 5; ++i)
      delete choices[i].value;

   return retval;
}

int stochastic_selection_3() {
   Chromosome<int> choices[5];
   for (int i = 0; i < 5; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = -0.2;
   }

   std::vector<Chromosome<int> *> collected;

   simulate_stochastic_selection(choices,5,5,collected,NULL);

   int retval = 1;

   if (collected.size() != 5)
      retval = 0;

   if (*(collected[0]->value) != 0)
      retval = 0;
   if (*(collected[1]->value) != 0)
      retval = 0;
   if (*(collected[2]->value) != 1)
      retval = 0;
   if (*(collected[3]->value) != 2)
      retval = 0;
   if (*(collected[4]->value) != 3)
      retval = 0;

   for (int i = 0; i < 5; ++i)
      delete choices[i].value;

   return retval;
}

int stochastic_selection_4() {
   Chromosome<int> choices[5];
   for (int i = 0; i < 5; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = 0;
   }

   std::vector<Chromosome<int> *> collected;

   simulate_stochastic_selection(choices,5,5,collected,NULL);

   int retval = 1;

   if (collected.size() != 5)
      retval = 0;

   if (*(collected[0]->value) != 0)
      retval = 0;
   if (*(collected[1]->value) != 0)
      retval = 0;
   if (*(collected[2]->value) != 0)
      retval = 0;
   if (*(collected[3]->value) != 4)
      retval = 0;
   if (*(collected[4]->value) != 4)
      retval = 0;

   for (int i = 0; i < 5; ++i)
      delete choices[i].value;

   return retval;
}

int tournament_selection_0() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = i;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[2] = { 1, 3 };

   simulate_tournament_selection(2,choices,20,1,collected,rnd);

   int retval = 1;

   if (collected.size() != 1)
      retval = 0;

   if (*(collected[0]->value) != 3)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

int tournament_selection_1() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = i;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[4] = { 1, 3, 5, 7 };

   simulate_tournament_selection(4,choices,20,1,collected,rnd);

   int retval = 1;

   if (collected.size() != 1)
      retval = 0;

   if (*(collected[0]->value) != 7)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

int tournament_selection_2() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = i;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[4] = { 7, 5, 3, 1 };

   simulate_tournament_selection(4,choices,20,1,collected,rnd);

   int retval = 1;

   if (collected.size() != 1)
      retval = 0;

   if (*(collected[0]->value) != 7)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

int tournament_selection_3() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = i;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[15] = { 7, 5, 3, 1, 0, 6, 13, 12, 8, 17, 4, 3, 9, 7, 12 };

   simulate_tournament_selection(5,choices,20,3,collected,rnd);

   int retval = 1;

   if (collected.size() != 3)
      retval = 0;

   if (*(collected[0]->value) != 7)
      retval = 0;
   if (*(collected[1]->value) != 17)
      retval = 0;
   if (*(collected[2]->value) != 12)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

int tournament_selection_4() {
   Chromosome<int> choices[20];
   for (int i = 0; i < 20; ++i) {
      choices[i].value = new int;
      *(choices[i].value) = i;
      choices[i].fitness = i;
   }

   std::vector<Chromosome<int> *> collected;
   uint64_t rnd[15] = { 12, 7, 9, 3, 4, 17, 8, 12, 13, 6, 0, 1, 3, 5, 7 };

   simulate_tournament_selection(5,choices,20,3,collected,rnd);

   int retval = 1;

   if (collected.size() != 3)
      retval = 0;

   if (*(collected[0]->value) != 12)
      retval = 0;
   if (*(collected[1]->value) != 17)
      retval = 0;
   if (*(collected[2]->value) != 7)
      retval = 0;

   for (int i = 0; i < 20; ++i)
      delete choices[i].value;

   return retval;
}

}

}
