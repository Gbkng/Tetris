#pragma once

#include "SFML/Graphics.hpp"

namespace tetris
{

  struct Level
  {
    sf::Color backgroundColor;
    int clockTick;
    float scoreMultiplier;

    Level(sf::Color backgroundColor_ = sf::Color::Black,
          int clockTick_ = 300,
          float scoreMultiplier_ = 1.);
  };
  struct LevelTable
  {
    static const std::array<Level, 20> levelTable;
  };
}

