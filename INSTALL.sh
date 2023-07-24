#!/bin/bash

echo -e "\
---------------------
Tetris install script
---------------------
"

if ! [ -f '/etc/debian_version' ]; then
    echo "It seems that your distribution is not debian-based. The install \
procedure may fail."
fi

echo "Please run the following command to ensure dependencies are correctly \
installed:

'sudo apt install -y \
gcc \
libstdc++6 \
make \
cmake \
libsfml-dev \
libsfml-graphics2.5 \
libsfml-system2.5 \
libsfml-window2.5'\
"

printf  "\nconfigure project with 'cmake'\n\n"

set -e

mkdir -p bin .build

cmake -S . -B .build \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_INSTALL_PREFIX=.

printf  "\n\nbuild project with 'make'\n\n"

make -C .build install
chmod +x bin/tetris

set +e
