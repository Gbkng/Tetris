#include <iostream>

#include "SFML/Graphics.hpp"
#include "tetromino.hpp"
#include "game.hpp"
#include "game_display.hpp"

int main()
{
  tetris::TetrisGame<10, 20> game;
  game.run();
  return 0;
}
