#include "random.hpp"

namespace tetris {

RandomGenerator::RandomGenerator(int maxNumber)
    : random_distribution_(1, maxNumber), rng_(std::random_device()()) {}

int RandomGenerator::generateRandomInteger() {
  return random_distribution_(rng_);
}

} // namespace tetris
