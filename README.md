# Tetris
Another very disruptive game.
Written in C++.
Hope Bjarne will be proud.

# How to play ?

- Z - rotate
- Space - drop
- Left Arrow - left
- Right Arrow - right
- Down Arrow - down 

# LINUX : Compile and run from source

The following procedure has been tested on Ubuntu 20.04.

## The very lazy way

Just run the INSTALL.sh script, follow the instructions, and enjoy your life. 
To do so, from the source directory, run

```sh
chmod +x INSTALL.sh; sudo ./INSTALL.sh
```

This script will install dependencies, build the project, and run it. You will have to enter sudo password, and might have to accept some package installation. 

To run the game again, just run 
```sh
./tetris
```
from the build directory.

If you want to compile the project step by step, the categories below provide more details.

## Dependencies

To compile this project, some packages have to be installed on your machine.


First, install some usual packages concerning C/C++ build.

```sh
sudo apt install gcc libstdc++6 make cmake 
```

Those packages are respectivelly the C/C++ compiler, the C++ standard library, the automatic build application, and a tool to generate scripts for the automatic build application.

The project is also based on the SFML project (Simple Fast Multimedia Library).

To install the required module of this library, run
```sh
sudo apt install libsfml-dev libsfml-graphics2.5 libsfml-system2.5 libsfml-window2.5
```


## Compile
To compile the game, you first need to create a build directory aside from the source. For example, from this directory, run

```sh
mkdir build 
cd build
```

Then, from the build directory, run cmake with Release option (this will generate a MakeFile with Release flags for the compiler), through the command

```sh
cmake .. -DCMAKE_BUILD_TYPE=Release
```

Please note that `..` is just a generic command that designates the parent directory. 

The generic path to provide to cmake is the path to the source directory (i.e. where the `CMakeList.txt` file is). 

Consequently, if the build folder has been created elsewhere, you must replace `..` with the source directory path.

From the same directory you ran the `cmake <...>` command, now run

```sh
make
```

This command calls the compiler to properly generate the final binary. 

## Run

A binary file called `tetris` has been created in the build folder.

To run the game, juste run 
```sh
./tetris
```

If it fails with a message such as `permission denied: ./tetris`, you need to grant `tetris` the execution permission by running :

```sh
chmod +x tetris
```

The precedent command should now work properly.

# Notes 

- The `.ttf` file is a font that is recquired to display the score on screen.
