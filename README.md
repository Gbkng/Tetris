# Tetris

Another very disruptive game, written in C++.

# How to play ?

commands in parenthesis are vi-like alternatives
- `z (k)` - rotate
- `space` - drop
- `LeftArrow (h)` - left
- `RightArrow (l)` - right
- `Down Arrow (j)` - down

# LINUX : Compile and run from source

The following procedure has been tested on Ubuntu 20.04.

## The very lazy way

Just run the INSTALL.sh script, from the source directory:

```sh
chmod +x INSTALL.sh; ./INSTALL.sh
```

This script will build the project, assuming you have the correct dependencies.

**WARNING** Please read the first few lines of the script if the procedure fails. They provide information about dependencies installation.

To run the game, run 

```sh
./bin/tetris
```

from the source directory.

If you want to compile the project step by step, the categories below provide more details.

## Dependencies

To compile this project, some packages have to be installed on your machine.

First, install some usual packages concerning C/C++ build.

```sh
sudo apt install gcc libstdc++6 make cmake 
```

Those packages are respectivelly the C/C++ compiler, the C++ standard library, and make/cmake build tools.

The project is also based on the SFML project (Simple Fast Multimedia Library).

To install the required module of this library, run

```sh
sudo apt install libsfml-dev libsfml-graphics2.5 libsfml-system2.5 libsfml-window2.5
```

## Compile

To compile the game, you first need to create a build directory aside from the source:

```sh
mkdir bin
```

Then, run cmake with Release build option: 

```sh
# from source dir
cmake -S . -B bin -D CMAKE_BUILD_TYPE=Release
```
Other available build options are `Debug` and `RelWithDebInfo`

Then, run make

```sh
make -C bin
```

## Run

A binary file called `tetris` has been created in the build folder.

```sh
./bin/tetris
```

If it fails with a message such as `permission denied: ./tetris`, you need to grant `tetris` the execution permission by running :

```sh
chmod +x ./bin/tetris
```

# Notes 

- The `.ttf` file is a font that is recquired to display the score on screen.
