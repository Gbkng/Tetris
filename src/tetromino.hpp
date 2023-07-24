#pragma once

#include <array>

#include "map.hpp"

namespace tetris {

class Tetromino : public Map<Tetromino, LogicType, 4, 4> {
public:
  static constexpr unsigned int shapeNb = 7;
  Tetromino(const LogicType &type, const int x = 0, const int y = 0);
  Tetromino(const LogicType &type, const Coord &coord);
  void reset(const LogicType &type, const Coord &coord);
  void rotateClockwise();
  void rotateCounterClockwise();
  inline void updatePosition(const Coord &coord) { discretePosition_ = coord; }
  inline void addPosition(const Coord &coord) { discretePosition_ += coord; }

  int coordToRank(const int x, const int y) const;

  // position of tetromino in the global frame (ie. in the logicMap frame)
  inline const Coord &getPosition() const { return discretePosition_; }

private:
  const LogicType type_;
  std::array<bool, 16> localShape_;
  Coord discretePosition_;

  void setShape_(const LogicType &type);
};

LogicType randomShape();

} // namespace tetris
