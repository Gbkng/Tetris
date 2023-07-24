#pragma once

#include <array>

#include "color.hpp"

namespace tetris {

struct Level {
  Color backgroundColor;
  int clockTick;
  float scoreMultiplier;

  Level(Color = Color::Black, int = 300, float = 1.);
};
struct LevelTable {
  static const std::array<Level, 20> levelTable;
};
} // namespace tetris
