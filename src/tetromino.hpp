#pragma once

#include <cassert>
#include <iostream>
#include <memory>

#include "SFML/Graphics.hpp"

#include "map.hpp"
#include "random_generator.hpp"

namespace tetris {

class Tetromino : public Map<Tetromino, LogicType, 4, 4> {
public:
  static constexpr unsigned int shapeNb = 7;
  Tetromino(const LogicType &type, const int x = 0, const int y = 0)
      : type_(type), discretePosition_(x, y) {
    setShape_(type);
  }
  Tetromino(const LogicType &type, const Coord &coord)
      : type_(type), discretePosition_(coord) {
    setShape_(type);
  }
  void reset(const LogicType &type, const Coord &coord) {
    setShape_(type);
    updatePosition(coord);
  }
  void rotateClockwise() {
    // (X, Y) --(rotation clock)--> ((L - 1) - Y, X), with L the length of the
    // square map. data that was at rank X + Y * L is now at rank ((L - 1) - Y)
    // + X * L

    std::array<LogicType, 16> buffer;
    for (int x = 0; x < 4; ++x) {
      for (int y = 0; y < 4; ++y) {
        buffer.at(3 - y + 4 * x) = this->get(x, y);
      }
    }
    this->swapData(buffer);
  }
  void rotateCounterClockwise() {
    // (X, Y) --(rotation clock)--> ((L - 1) - Y, X), with L the length of the
    // square map. data that was at rank X + Y * L is now at rank ((L - 1) - Y)
    // + X * L

    std::array<LogicType, 16> buffer;
    for (int x = 0; x < 4; ++x) {
      for (int y = 0; y < 4; ++y) {
        buffer.at(y + 4 * (3 - x)) = this->get(x, y);
      }
    }
    this->swapData(buffer);
  }

  void updatePosition(const Coord &coord) { discretePosition_ = coord; }
  void addPosition(const Coord &coord) { discretePosition_ += coord; }

  int coordToRank(const int x, const int y) const {
    assert((x >= 0 && y >= 0) && "coords must be >= 0");
    assert((x < 4 && y < 4) && "coords must be < 4");
    return x + y * 4;
  }

  // position of tetromino in the global frame (ie. in the logicMap frame)
  const Coord &getPosition() const { return discretePosition_; }

private:
  const LogicType type_;
  std::array<bool, 16> localShape_;
  Coord discretePosition_;

  void setShape_(const LogicType &type) {
    this->set(LogicType::Void); // reset the map to void
    // fill the map, depending of the provided LogicType
    switch (type) {
    case LogicType::Square:
      // TODO : allow the convenient syntax below.
      // set(LogicType::Square, static_cast<std::vector<Coord>>( { {1,1}, {1,2},
      // {2,1}, {2,2} } ));
      this->set(LogicType::Square, 1, 1);
      this->set(LogicType::Square, 1, 2);
      this->set(LogicType::Square, 2, 1);
      this->set(LogicType::Square, 2, 2);
      break;
    case LogicType::Bar:
      this->set(LogicType::Bar, 0, 1);
      this->set(LogicType::Bar, 1, 1);
      this->set(LogicType::Bar, 2, 1);
      this->set(LogicType::Bar, 3, 1);
      break;
    case LogicType::Vince:
      this->set(LogicType::Vince, 0, 0);
      this->set(LogicType::Vince, 0, 1);
      this->set(LogicType::Vince, 0, 2);
      this->set(LogicType::Vince, 1, 2);
      this->set(LogicType::Vince, 2, 2);
      this->set(LogicType::Vince, 2, 1);
      this->set(LogicType::Vince, 2, 0);
      break;
    case LogicType::T:
      this->set(LogicType::T, 0, 1);
      this->set(LogicType::T, 1, 1);
      this->set(LogicType::T, 2, 1);
      this->set(LogicType::T, 1, 2);
      break;
    case LogicType::S:
      this->set(LogicType::S, 1, 1);
      this->set(LogicType::S, 2, 1);
      this->set(LogicType::S, 0, 2);
      this->set(LogicType::S, 1, 2);
      break;
    case LogicType::Z:
      this->set(LogicType::Z, 1, 1);
      this->set(LogicType::Z, 2, 1);
      this->set(LogicType::Z, 2, 2);
      this->set(LogicType::Z, 3, 2);
      break;
    case LogicType::L:
      this->set(LogicType::L, 1, 1);
      this->set(LogicType::L, 2, 1);
      this->set(LogicType::L, 3, 1);
      this->set(LogicType::L, 1, 2);
      break;
    case LogicType::InversedL:
      this->set(LogicType::InversedL, 0, 1);
      this->set(LogicType::InversedL, 1, 1);
      this->set(LogicType::InversedL, 2, 1);
      this->set(LogicType::InversedL, 2, 2);
      break;
    default:
      assert(false && "a tetromino shape cannot be set with this LogicType.");
      break;
    }
  }
};
LogicType randomShape() {
  static constexpr int shapeNb = Tetromino::shapeNb;
  static const std::array<LogicType, shapeNb> shapeArray = {
      LogicType::Bar, LogicType::InversedL, LogicType::L, LogicType::S,
      LogicType::Z,   LogicType::Square,    LogicType::T,
      // LogicType::Vince
  };
  static RandomGenerator randomGen(shapeNb);
  const int randomShapeRk =
      randomGen.generateRandomInteger(shapeNb - 1); // range [0, shapeNb - 1]
  return shapeArray.at(randomShapeRk);
}

} // namespace tetris
