#include <array>

#include "color.hpp"
#include "level.hpp"

namespace tetris {

Level::Level(Color backgroundColor_, int clockTick_, float scoreMultiplier_)
    : backgroundColor(backgroundColor_), clockTick(clockTick_),
      scoreMultiplier(scoreMultiplier_) {}

const std::array<Level, 20> LevelTable::levelTable = {
    // clang-format off
    Level(Color(0, 0, 0, 0)  , 600,  1.0),     
    Level(Color(0, 0, 0, 20) , 500,  1.5),
    Level(Color(0, 0, 0, 40) , 400,  2.0),
    Level(Color(0, 0, 0, 60) , 350,  2.5),
    Level(Color(0, 0, 0, 80) , 300,  3.0), // ...5
    Level(Color(0, 0, 0, 100), 280,  3.5),
    Level(Color(0, 0, 0, 120), 250,  4.0),
    Level(Color(0, 0, 0, 140), 210,  4.5),
    Level(Color(0, 0, 0, 160), 200,  5.0),
    Level(Color(0, 0, 0, 180), 190,  5.5), // ...10
    Level(Color(0, 0, 0, 200), 180,  6.0),
    Level(Color(0, 0, 0, 220), 170,  6.5),
    Level(Color(0, 0, 0, 240), 160,  7.0),
    Level(Color(0, 0, 0, 255), 150,  7.5),
    Level(Color(0, 0, 0, 255), 140,  8.0), // ...15
    Level(Color(0, 0, 0, 255), 130,  8.5),
    Level(Color(0, 0, 0, 255), 120,  9.0), 
    Level(Color(0, 0, 0, 255), 110,  9.5),
    Level(Color(0, 0, 0, 255), 100, 10.0),
    Level(Color(0, 0, 0, 255), 100, 15.0)  // ...20
};
// clang-format on
} // namespace tetris
