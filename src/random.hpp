#pragma once

#include <random>

namespace tetris {

class RandomGenerator {
public:
  RandomGenerator(int);
  int generateRandomInteger();

private:
  std::mt19937 rng_;
  std::uniform_int_distribution<std::mt19937::result_type> random_distribution_;
};
} // namespace tetris
