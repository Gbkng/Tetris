#pragma once

#include <array>
#include <filesystem>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "color.hpp"
#include "level.hpp"
#include "logic_map.hpp"
#include "map.hpp"
#include "tetromino.hpp"

namespace tetris {
class GameWindow : public sf::RenderWindow {
  GameWindow(sf::VideoMode mode, const sf::String &title)
      : sf::RenderWindow(mode, title) {}
};

/**
 * @brief This class draw on a window the logical state of a game
 **/
template <class Game> class GameDisplay {
  static constexpr int xDim = Game::xDim;
  static constexpr int yDim = Game::yDim;
  static constexpr int blockX = Game::blockX;
  static constexpr int blockY = Game::blockY;

  // window dimension and generation
  static constexpr int width = xDim * blockX;
  static constexpr int height = yDim * blockY;

public:
  GameDisplay(const Game &tetrisGame)
      : window_(sf::VideoMode(width, height), "GuyTetris"),
        tetrisGame_(tetrisGame), gameLogicMap_(tetrisGame_.getMap()),
        activeTetromino_(tetrisGame_.getTetromino()),
        backgroundColor_(LevelTable::levelTable.at(0).backgroundColor),
        gamePixel_(sf::Vector2f(blockX, blockY)) {
    // VSync, not to burn the CPU
    window_.setVerticalSyncEnabled(true);
    window_.setFramerateLimit(60);

    const std::filesystem::path fontpath =
        std::filesystem::current_path() / "font.ttf";
    std::cout << "fontpath : " << fontpath << std::endl;

    if (!font_.loadFromFile(fontpath)) {
      std::cout << "Failed to load font" << std::endl;
    }

    scoreDisplay_.setFont(font_);
    scoreDisplay_.setCharacterSize(40); // in pixels, not points!
    scoreDisplay_.setFillColor(Color(255, 255, 255, 200));
    scoreDisplay_.setStyle(sf::Text::Bold);
    scoreDisplay_.setPosition(10, 10);
  }
  const sf::RenderWindow &getWindow() const { return window_; }
  void display() {
    if (tetrisGame_.isGameOver()) {
      displayGameOver_();
      std::exit(0);
    }
    clear_();
    drawMap_();
    drawTetromino_();
    drawScore_();
    window_.display();
  }

  void setBackgroundColor(Color color) { backgroundColor_ = color; }
  void closeWindow() { window_.close(); }
  bool pollEvent(sf::Event &event) { return window_.pollEvent(event); }

private:
  sf::Clock clock_;
  sf::RenderWindow window_;
  const Game &tetrisGame_;
  const LogicMap<xDim, yDim> &gameLogicMap_;
  const Tetromino &activeTetromino_;
  Color backgroundColor_;
  sf::RectangleShape gamePixel_;
  sf::Text scoreDisplay_;
  sf::Font font_;

  void clear_() { window_.clear(backgroundColor_); }
  void displayGameOver_() {
    std::cout << "GAME OVER !" << std::endl;
    window_.clear(Color::Black);

    const std::string gameOverStr = "GAME OVER";
    scoreDisplay_.setCharacterSize(
        (window_.getSize().x - 100) /
        gameOverStr.size()); // in pixels, not points!
    scoreDisplay_.setFillColor(Color(255, 255, 255, 200));
    scoreDisplay_.setStyle(sf::Text::Bold);
    scoreDisplay_.setPosition(30, window_.getSize().y / 2.);

    scoreDisplay_.setString(gameOverStr);

    window_.draw(scoreDisplay_);
    window_.display();
    sf::Time duration = sf::seconds(3.f);
    sf::sleep(duration);
  }

  void drawScore_() {
    scoreDisplay_.setString(std::to_string(tetrisGame_.getScore()));
    window_.draw(scoreDisplay_);
  }
  void drawMap_() {
    for (int x = 0; x < xDim; x++) {
      for (int y = 0; y < yDim; y++) {
        const auto &type = gameLogicMap_.get(x, y);
        if (type != LogicType::Void) {
          const float xScreen = x * blockX;
          const float yScreen = y * blockX;
          setGamePixelColor_(type);
          setGamePixelPosition_(xScreen, yScreen);
          window_.draw(gamePixel_);
        }
      }
    }
  }

  void drawTetromino_() {
    const auto offset = activeTetromino_.getPosition();
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        const auto &type = activeTetromino_.get(x, y);
        setGamePixelColor_(type);
        if (type != LogicType::Void) {
          const float xScreen = (x + offset.x) * blockX;
          const float yScreen = (y + offset.y) * blockX;
          setGamePixelPosition_(xScreen, yScreen);
          window_.draw(gamePixel_);
        }
      }
    }
  }

  void setGamePixelPosition_(const float xScreen, const float yScreen) {
    const sf::Vector2f position(xScreen, yScreen);
    gamePixel_.setPosition(position);
  }

  void setGamePixelColor_(const LogicType &type) {
    switch (type) {
    case LogicType::Bar:
      gamePixel_.setFillColor(Color::Magenta);
      break;
    case LogicType::InversedL:
      gamePixel_.setFillColor(Color::Red);
      break;
    case LogicType::L:
      gamePixel_.setFillColor(Color::Green);
      break;
    case LogicType::S:
      gamePixel_.setFillColor(Color::White);
      break;
    case LogicType::Square:
      gamePixel_.setFillColor(Color::Cyan);
      break;
    case LogicType::T:
      gamePixel_.setFillColor(Color::Blue);
      break;
    case LogicType::Z:
      gamePixel_.setFillColor(Color::Yellow);
      break;
    default:
      break;
    }
  }
};

} // namespace tetris
