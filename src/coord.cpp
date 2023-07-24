#include "coord.hpp"

namespace tetris {

const Coord Coord::Down = Coord(0, 1);
const Coord Coord::Up = Coord(0, -1);
const Coord Coord::Left = Coord(-1, 0);
const Coord Coord::Right = Coord(1, 0);

Coord::Coord(int x_, int y_) : x(x_), y(y_) {}

void Coord::operator*=(const int coeff) {
  this->x *= coeff;
  this->y *= coeff;
}
void Coord::operator=(const Coord &c2) {
  this->x = c2.x;
  this->y = c2.y;
}
void Coord::operator+=(const Coord &c2) {
  this->x += c2.x;
  this->y += c2.y;
}

Coord Coord::operator+(const Coord &c2) {
  return Coord(this->x + c2.x, this->y + c2.y);
}
Coord Coord::operator-(const Coord &c2) {
  return Coord(this->x - c2.x, this->y - c2.y);
}

Coord operator+(const Coord &c1, const Coord &c2) {
  return Coord(c1.x + c2.x, c1.y + c2.y);
}
Coord operator-(const Coord &c1, const Coord &c2) {
  return Coord(c1.x - c2.x, c1.y - c2.y);
}

Coord operator-(const Coord &c) { return Coord(-c.x, -c.y); }
Coord operator+(const Coord &c) { return Coord(c.x, c.y); }
} // namespace tetris
