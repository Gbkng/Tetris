#include "game.hpp"

int main() {
  tetris::TetrisGame<10, 20> game;
  game.run();

  return 0;
}
