#pragma once

#include <cassert>
#include <iostream>
#include <memory>

#include "SFML/Graphics.hpp"

#include "map.hpp"

namespace tetris
{

  /**
 * The logicMap essentially consists in an 2D array with each case representing the status
 * of the corresponding block.
 * 
 * The tricky part here is that the origin is not in the top-left corner, in order to have a
 * convenient coordinate system for tetrominos.
 * 
 *     -1  0   1   2   3   4
 *    |---|---|---|---|---|---|
 * -1 | 0 | 1 | 2 | 3 | 4 | 5 |
 *    |---|---|---|---|---|---|
 *  0 | 6 ||7|| 8 | 9 |10 |11 |
 *    |---|---|---|---|---|---|
 *  1 |12 |.. |   |   |   |   |
 *    |---|---|---|---|---|---|
 *  2 |   |   |   |   |   |   |
 *    |---|---|---|---|---|---|
 *  3 |   |   |   |   |   |   |
 *    |---|---|---|---|---|---|
 * 
 * On the example above, |7| is the origin in tetromino coordinates.
 * The valid tetromino range is x \in [0 - 3], y \in [0- 2]
 * 
 * Domains with equation x = -1, x = 4, and y = 2 are filled with Wall type (W).
 * The top domain of equation (y = -1 and x!=4 and x!=-1) is filled with GameOver type (G).
 * 
 *     -1  0   1   2   3   4
 *    |---|---|---|---|---|---|
 * -1 | W | G | G | G | G | W |
 *    |---|---|---|---|---|---|
 *  0 | W |   |   |   |   | W |
 *    |---|---|---|---|---|---|
 *  1 | W |   |   |   |   | W |
 *    |---|---|---|---|---|---|
 *  2 | W |   |   |   |   | W |
 *    |---|---|---|---|---|---|
 *  3 | W | W | W | W | W | W |
 *    |---|---|---|---|---|---|
 * 
 */
  template <int xDim, int yDim>
  class LogicMap : public Map<LogicMap<xDim, yDim>, LogicType, xDim + 2, yDim + 2>
  {
  public:
    static constexpr int xDimTot = xDim + 2; // x dimension of the total domain
    static constexpr int yDimTot = yDim + 2; // y dimension of the total domain

    LogicMap() : Map<LogicMap<xDim, yDim>, LogicType, xDimTot, yDimTot>()
    {
      this->set(LogicType::Void);
      initBoundaries_();
    }

    template <bool verbose = false>
    int coordToRank(const int x, const int y) const
    {
      const auto rank = (xDimTot + 1) + x + y * xDimTot;
      if constexpr (verbose)
      {
        if (x < -1 || y < -1)
        {
          std::cout << "coords must be >= -1." << std::endl;
        }
        if (x == -1 || x == xDimTot - 1 || y == -1 || y == yDimTot - 1)
        {
          std::cout << "Careful, requesting an out of tetromino's domain area." << std::endl;
          std::cout << "rank : " << rank << std::endl;
        }
      }
      return rank;
    }

  private:
    void initBoundaries_()
    {
      for (int x = -1; x < xDimTot - 1; x++)
      {
        this->set(LogicType::GameOver, x, -1); // game over on top line
      }
      for (int y = -1; y < yDimTot - 1; y++)
      {
        this->set(LogicType::Wall, -1, y);          // wall on left side
        this->set(LogicType::Wall, xDimTot - 2, y); // wall on right side
      }
      for (int x = -1; x < xDimTot - 1; x++)
      {
        this->set(LogicType::Bottom, x, yDimTot - 2); // bottom on bottom line
      }
    }

    void printRanksDebug_() const
    {
      for (int y = -1; y < yDimTot - 1; y++)
      {
        for (int x = -1; x < xDimTot - 1; x++)
        {
          const auto rank = this->coordToRank(x, y);
          if (rank % xDimTot == 0)
          {
            std::cout << std::endl;
          }
          std::cout << rank << "\t";
        }
      }
      std::cout << std::endl;
    }
  };

}

