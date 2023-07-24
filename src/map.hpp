#pragma once

#include <cassert>
#include <iostream>
#include <memory>

#include "coord.hpp"

namespace tetris {

/**
 * Status of a pixel of a LogicMap
 */
enum LogicType {
  Void,
  Wall,
  GameOver,
  Bottom,
  Square,
  T,
  L,
  InversedL,
  Bar,
  S,
  Z,
  OutOfBound
};

template <class Derived, typename T, int xDim, int yDim> // CRTP
class Map {
public:
  static constexpr int mapSize = xDim * yDim;

  int size() const { return mapSize; }
  void set(const T &value) {
    for (auto &element : map_) {
      element = value;
    }
  }
  void set(const T &value, const Coord &coord) {
    this->set(value, coord.x, coord.y);
  }
  void set(const T &value, const int x, const int y) {
    const auto rank = static_cast<Derived *>(this)->coordToRank(x, y);
    isRankValid_(rank); // throw error if out of bound rank
    map_.at(rank) = value;
  }
  void swapData(std::array<T, xDim * yDim> data) { map_.swap(data); }

  const T get(const int x, const int y) const {
    const auto rank = static_cast<const Derived *>(this)->coordToRank(x, y);
    return get_(rank);
  }
  const T get(const Coord &coord) const { return this->get(coord.x, coord.y); }

  // Debug tool
  void printMap() const {
    for (int k = 0; k < map_.size(); k++) {
      if ((k) % xDim == 0) {
        std::cout << std::endl;
      }
      std::cout << map_.at(k) << "\t";
    }
    std::cout << std::endl;
  }

protected:
  T get_(const int rank) const {
    if (isRankValid_(rank)) {
      return map_.at(rank);
    } else {
      return LogicType::OutOfBound;
    }
  }

private:
  std::array<T, mapSize> map_;
  template <bool verbose = false>
  inline bool isRankValid_(const int rank) const {
    if ((rank >= mapSize) || (rank < 0)) {
      if constexpr (verbose) {
        std::cout << "rank : " << rank << std::endl;
        std::cout << "map rank out of bound !" << std::endl;
      }
      return false;
    }
    return true;
  }
};

} // namespace tetris
