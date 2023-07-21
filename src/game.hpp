#pragma once

#include "SFML/Graphics.hpp"
#include "game_display.hpp"
#include "level.hpp"
#include "logic_map.hpp"
#include "tetromino.hpp"

namespace tetris
{
  template <int xDim_, int yDim_>
  class TetrisGame
  {
  public:
    static constexpr int blockX = 30;
    static constexpr int blockY = 30;
    static constexpr int xDim = xDim_;
    static constexpr int yDim = yDim_;
    static constexpr int x0 = xDim_ / 2;
    static constexpr int y0 = -2;

    static constexpr auto &levelTable = LevelTable::levelTable;
    TetrisGame() : gameDisplay_(*this), // open the window
                   window_(gameDisplay_.getWindow()),
                   // init game status
                   gameOver_(false),
                   score_(0),          // init score
                   lineCount_(0),      // init line count
                   totalLineCount_(0), // init total line count
                   level_(0),          // start at level 0
                   // fetch level parameters
                   scoreMultiplier_(levelTable.at(0).scoreMultiplier),
                   clockTick_(levelTable.at(0).clockTick),
                   // starting tetromino and reset position
                   coord0_(x0, y0),
                   tetromino_(randomShape(), coord0_)
    {
    }
    bool isOpen_() const { return window_.isOpen(); }
    void run()
    {
      while(isOpen_()){
        sf::Event event;
        while (gameDisplay_.pollEvent(event))
        {
          update_(event);
          switch (event.type)
          {
          case sf::Event::Closed:
            closeGame_();
            break;
          case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
              closeGame_();
              break;
            default:
              break;
            }
            break;
          default:
            break;
          }
        }

        const sf::Time elapsed = clock_.getElapsedTime();
        if (elapsed.asMilliseconds() > clockTick_)
        {
          tick_();
          clock_.restart();
        }

        gameDisplay_.display();
      }
    }
    const LogicMap<xDim, yDim> &getMap() const { return logicMap_; }
    const Tetromino &getTetromino() const { return tetromino_; }
    const int getScore() const { return score_; }
    bool isGameOver() const
    {
      return gameOver_;
    }

  private:
    GameDisplay<TetrisGame<xDim, yDim>> gameDisplay_;
    sf::Clock clock_;
    bool gameOver_;
    int score_;
    int lineCount_;
    int totalLineCount_;
    unsigned int level_;
    int clockTick_; // [ms]
    float scoreMultiplier_;
    const sf::RenderWindow &window_;
    LogicMap<xDim, yDim> logicMap_;
    const Coord coord0_;
    Tetromino tetromino_;

    enum CollisionType
    {
      Wall,
      Bottom,
      Tetro,
      GameOver,
      OutOfBound,
      None
    };

    void closeGame_()
    {
      gameDisplay_.closeWindow();
    }

    void update_(const sf::Event &event)
    {
      if (event.type == sf::Event::KeyPressed)
      {
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
          moveWithCheck_(Coord::Left);
          break;
        case sf::Keyboard::Right:
          moveWithCheck_(Coord::Right);
          break;
        case sf::Keyboard::Down:
          moveWithCheck_(Coord::Down);
          break;
        case sf::Keyboard::Z:
          rotateWithCheck_();
          break;
        case sf::Keyboard::Space:
          drop_();
          break;
        default:
          break;
        }
      }
    }

    void tick_()
    {
      moveWithCheck_(Coord::Down);
    }

    void setGameOver_()
    {
      gameOver_ = true;
    }

    void levelUp_()
    {
      if (this->level_ < 20)
      {
        this->level_ += 1;
      }
      const Level &level = levelTable.at(level_);
      clockTick_ = level.clockTick;
      gameDisplay_.setBackgroundColor(level.backgroundColor);
      scoreMultiplier_ = level.scoreMultiplier;
    }

    void drop_()
    {
      CollisionType collision;
      do
      {
        tetromino_.addPosition(Coord::Down); // move one step down
        collision = checkCollision_();
      } while (collision != CollisionType::Bottom && collision != CollisionType::Tetro);

      if (collision == CollisionType::GameOver)
      {
        setGameOver_();
      }

      tetromino_.addPosition(Coord::Up); // move one step up to cancel the last forbidden move
      fixAndResetTetromino_(randomShape());
    }

    void fixAndResetTetromino_(const LogicType &type)
    {
      fixTetromino_();
      tetromino_.reset(type, coord0_);
      lineRoutine_();
    }

    void updateScore_(const int lineNb)
    {
      // lineNb represents number of lines formed at a same time
      score_ += static_cast<int>((10 + 20 * (lineNb - 1)) * scoreMultiplier_);
      if (lineNb == 4) // if tetris
      {
        score_ += static_cast<int>(50 * scoreMultiplier_);
      }
    }

    void fixTetromino_()
    {
      const auto &globalCoord = tetromino_.getPosition(); // tetromino position
      Coord localCoord(0, 0);
      for (localCoord.x = 0; localCoord.x < 4; localCoord.x++)
      {
        for (localCoord.y = 0; localCoord.y < 4; localCoord.y++)
        {
          const auto mapType = logicMap_.get(localCoord + globalCoord); // logical type of the map
          if (mapType == LogicType::Void)                               // skip if out of bound (if a coordinate of tetromino's map is one block away from walls)
          {
            logicMap_.set(tetromino_.get(localCoord), localCoord + globalCoord);
          }
        }
      }
    }

    void rotateWithCheck_()
    {
      const auto currentPosition = tetromino_.getPosition();
      tetromino_.rotateClockwise();
      const CollisionType collision = checkCollision_();
      switch (collision)
      {
      case CollisionType::GameOver:
        break;
      case CollisionType::None:
        break;
      default:
        tetromino_.rotateCounterClockwise(); // go back because forbidden
        break;
      }
    }

    void moveWithCheck_(const Coord &coord)
    {
      const auto currentPosition = tetromino_.getPosition();
      tetromino_.addPosition(coord);
      const CollisionType collision = checkCollision_();
      switch (collision)
      {
      case CollisionType::GameOver:
        setGameOver_();
        break;
      case CollisionType::Wall:
        tetromino_.addPosition(-coord); // go back before draw
        break;
      case CollisionType::Tetro:
        tetromino_.addPosition(-coord); // go back before fix
        if (coord.y > 0)
        { // to avoid fix on lateral move
          fixAndResetTetromino_(randomShape());
        }
        break;
      case CollisionType::Bottom:
        tetromino_.addPosition(-coord); // go back before fix
        fixAndResetTetromino_(randomShape());
        break;
      default:
        break;
      }
    }

    /** 
     * @brief check if a line exists. If so, returns rank of the line.
     * Note it returns a vector and not only a single rank, as multiple
     * lines can be obtained at the same time.
     */
    std::vector<int> checkLine_() const
    {
      std::vector<int> lineRanks;
      for (int y = 0; y < yDim; y++) // line of rank y
      {
        bool isGap = false;
        for (int x = 0; x < xDim; x++)
        {
          if (logicMap_.get(x, y) == LogicType::Void)
          {
            isGap = true;
            break;
          }
        }
        if (!isGap)
        {
          lineRanks.push_back(y);
        }
      }
      return lineRanks;
    }

    /**
     * @brief erase line at a certain rank. Move all blocks above.
     **/
    void eraseLine_(int lineRank)
    {
      // no buffer issue since the line must be deleted
      for (int y = lineRank; y >= 1; y--)
      {
        for (int x = 0; x < xDim; x++)
        {
          const auto &blockAbove = logicMap_.get(x, y - 1);
          logicMap_.set(blockAbove, x, y);
        }
      }
    }
    void lineRoutine_()
    {
      std::vector<int> lineRanksToErase = checkLine_();

      if (!lineRanksToErase.empty())
      {
        const int lineNb = lineRanksToErase.size();
        updateScore_(lineNb);
        std::cout << "score : " << score_ << std::endl;
        for (const auto &lineRank : lineRanksToErase)
        {
          eraseLine_(lineRank);
          lineCount_ += 1;
          totalLineCount_ += 1;
        }
        std::cout << "line count : " << totalLineCount_ << std::endl;
      }
      if (lineCount_ >= 10) // level up every 10 lines
      {
        levelUp_();
        lineCount_ = 0;
      }
    }
    CollisionType checkCollision_()
    {
      // the tetromino in a candidate new position can collide with three types of block (aside from void)
      bool gameOver = false;
      bool wall = false;
      bool tetro = false;
      bool bottom = false;
      // let collect all those collision, by looping on all the tetromino's map
      const auto &tPos = tetromino_.getPosition(); // tetromino position
      for (int x = 0; x < 4; x++)
      {
        for (int y = 0; y < 4; y++)
        {
          localCheck_(x, y, tPos, gameOver, wall, tetro, bottom);
        }
      }
      // decide what collision type it is
      if (gameOver && tetro)
      {
        return CollisionType::GameOver;
      }
      else if (wall)
      {
        if (tetro)
        {
          // TO DO --> wall + tetro : is possible ? what to do ?
        }
        return CollisionType::Wall;
      }
      else if (tetro) // so no wall here
      {
        return CollisionType::Tetro;
      }
      else if (bottom)
      {
        return CollisionType::Bottom;
      }
      else
      {
        return CollisionType::None;
      }

      return CollisionType::OutOfBound; // never happens
    }

    void localCheck_(int x, int y, const Coord &tPos, bool &gameOver, bool &wall, bool &tetro, bool &bottom)
    {
      const auto mapType = logicMap_.get(x + tPos.x, y + tPos.y); // logical type of the map
      if (mapType != LogicType::OutOfBound)                       // skip if out of bound (if a coordinate of tetromino's map is one block away from walls)
      {
        const auto tType = tetromino_.get(x, y);
        if (mapType == LogicType::GameOver)
        {
          gameOver = true;
        }
        if (tType != LogicType::Void && mapType != LogicType::Void) // If one is void, nothing to test
        {
          switch (mapType)
          {
          case LogicType::Wall:
            wall = true;
            break;
          case LogicType::Bottom:
            bottom = true;
            break;
          case LogicType::GameOver:
            break;
          default: // not void, not a wall, not game over, then tetro
            tetro = true;
            break;
          }
        }
      }
    }
  };
}
