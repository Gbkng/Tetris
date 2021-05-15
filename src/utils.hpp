#ifndef GUYTETRIS_UTILS_HPP_
#define GUYTETRIS_UTILS_HPP_

#include <random>

class RandomGenerator
{
public:
  RandomGenerator()
  {
    srand(time(NULL)); // random seed
  }
  int generateRandomInteger(int N)
  {
    int randInt = rand() % (N + 1); // predefined pseudo-random based on seed
    return randInt;
  }
};

#endif