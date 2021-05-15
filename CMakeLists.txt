cmake_minimum_required(VERSION 3.16)

project(GuyTetris)

set(CMAKE_CXX_STANDARD 17)
add_executable(
  tetris
  src/main.cpp
  src/level.cpp)

target_link_libraries(tetris sfml-graphics sfml-window sfml-system)
configure_file(font.ttf ./)