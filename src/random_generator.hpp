#pragma once

#include <random>

namespace tetris {

class RandomGenerator {
public:
  RandomGenerator(int maxNumber) {
    std::random_device dev;
    std::mt19937 rng_(dev());
    std::uniform_int_distribution<std::mt19937::result_type>
        random_distribution_(1, maxNumber);
  }
  int generateRandomInteger() { return random_distribution_(rng_); }

private:
  std::mt19937 rng_;
  std::uniform_int_distribution<std::mt19937::result_type>
      random_distribution_; // distribution in range [1, shapeNb]
};
} // namespace tetris
