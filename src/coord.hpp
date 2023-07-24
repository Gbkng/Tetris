#pragma once

namespace tetris {

struct Coord {
  static const Coord Down;
  static const Coord Up;
  static const Coord Left;
  static const Coord Right;

  int x;
  int y;

  Coord(int, int);

  void operator*=(const int);
  void operator=(const Coord &);
  void operator+=(const Coord &);

  Coord operator+(const Coord &);
  Coord operator-(const Coord &);
};
Coord operator+(const Coord &, const Coord &);
Coord operator-(const Coord &, const Coord &);

Coord operator-(const Coord &);
Coord operator+(const Coord &);

} // namespace tetris
