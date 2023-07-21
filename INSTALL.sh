#!/bin/bash

echo -e "\
---------------------
Tetris install script
---------------------"

echo "install dependencies"

sudo apt install -y \
  gcc \
  libstdc++6  \
  make  \
  cmake  \
  libsfml-dev  \
  libsfml-graphics2.5  \
  libsfml-system2.5  \
  libsfml-window2.5

echo "configure project"

mkdir -p bin
cmake -S . -B bin -DCMAKE_BUILD_TYPE=Release

echo "build"

make -C bin
chmod +x bin/tetris
