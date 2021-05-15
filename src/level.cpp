#include "level.hpp"

namespace tetris
{
  Level::Level(sf::Color backgroundColor_,
               int clockTick_,
               float scoreMultiplier_) : backgroundColor(backgroundColor_),
                                         clockTick(clockTick_),
                                         scoreMultiplier(scoreMultiplier_) {}

  const std::array<Level, 20> LevelTable::levelTable = {
      Level(sf::Color(0, 0, 0, 0),   600, 1.),       // level 1
      Level(sf::Color(0, 0, 0, 20),  500, 1.5),     // level 2
      Level(sf::Color(0, 0, 0, 40),  400, 2.),      // level 3
      Level(sf::Color(0, 0, 0, 60),  350, 2.5),     // level 4
      Level(sf::Color(0, 0, 0, 80),  300, 3.),      // level 5
      Level(sf::Color(0, 0, 0, 100), 280, 3.5),    // level 6
      Level(sf::Color(0, 0, 0, 120), 250, 4.),     // level 7
      Level(sf::Color(0, 0, 0, 140), 210, 4.5),    // level 8
      Level(sf::Color(0, 0, 0, 160), 200, 5.),     // level 9
      Level(sf::Color(0, 0, 0, 180), 190, 5.5),    // level 10
      Level(sf::Color(0, 0, 0, 200), 180, 6.),     // level 11
      Level(sf::Color(0, 0, 0, 220), 170, 6.5),    // level 12
      Level(sf::Color(0, 0, 0, 240), 160, 7.),     // level 13
      Level(sf::Color(0, 0, 0, 255), 150, 7.5),    // level 14
      Level(sf::Color(0, 0, 0, 255), 140, 8.),    // level 15
      Level(sf::Color(0, 0, 0, 255), 130, 8.5),  // level 16
      Level(sf::Color(0, 0, 0, 255), 120, 9.),   // level 17
      Level(sf::Color(0, 0, 0, 255), 110, 9.5),  // level 18
      Level(sf::Color(0, 0, 0, 255), 100, 10.),  // level 19
      Level(sf::Color(0, 0, 0, 255), 100, 15.)}; // level 20

      // Level(sf::Color(0, 0, 0, 0),   210, 1.),       // level 1
      // Level(sf::Color(0, 0, 0, 20),  210, 1.5),     // level 2
      // Level(sf::Color(0, 0, 0, 40),  210, 2.),      // level 3
      // Level(sf::Color(0, 0, 0, 60),  210, 2.5),     // level 4
      // Level(sf::Color(0, 0, 0, 80),  210, 3.),      // level 5
      // Level(sf::Color(0, 0, 0, 100), 210, 3.5),    // level 6
      // Level(sf::Color(0, 0, 0, 120), 210, 4.),     // level 7
      // Level(sf::Color(0, 0, 0, 140), 210, 4.5),    // level 8
      // Level(sf::Color(0, 0, 0, 160), 200, 5.),     // level 9
      // Level(sf::Color(0, 0, 0, 180), 190, 5.5),    // level 10
      // Level(sf::Color(0, 0, 0, 200), 180, 6.),     // level 11
      // Level(sf::Color(0, 0, 0, 220), 170, 6.5),    // level 12
      // Level(sf::Color(0, 0, 0, 240), 160, 7.),     // level 13
      // Level(sf::Color(0, 0, 0, 255), 150, 7.5),    // level 14
      // Level(sf::Color(0, 0, 0, 255), 140, 8.),    // level 15
      // Level(sf::Color(0, 0, 0, 255), 130, 8.5),  // level 16
      // Level(sf::Color(0, 0, 0, 255), 120, 9.),   // level 17
      // Level(sf::Color(0, 0, 0, 255), 110, 9.5),  // level 18
      // Level(sf::Color(0, 0, 0, 255), 100, 10.),  // level 19
      // Level(sf::Color(0, 0, 0, 255), 100, 15.)}; // level 20

}