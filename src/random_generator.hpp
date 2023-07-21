#pragma once

#include "tetromino.hpp"
#include <random>

namespace tetris {

class RandomGenerator {
public:
  RandomGenerator() {
    std::random_device dev;
    std::mt19937 rng_(dev());
    std::uniform_int_distribution<std::mt19937::result_type>
        random_distribution_(1, Tetromino::shapeNb);
  }
  int generateRandomInteger() { return random_distribution_(rng_); }

private:
  std::mt19937 rng_;
  std::uniform_int_distribution<std::mt19937::result_type>
      random_distribution_; // distribution in range [1, shapeNb]
};
} // namespace tetris

