
# minesweeper-cpp

Simple minesweeper game written in **C++/SDL2**. \
**SDL2** modules used:
- **SDL2_ttf**,
- **SDL_image**.

### Important note:
The application is currently in the development state.
Unexpected errors may occur during use.

***

## Build prerequisites

On _GNU/Linux_ systems open terminal and install the **sdl2**, **sdl2_image**,
**sdl2_ttf** packages by using package manager on your system. For example
when you're using **Debian** (or **Ubuntu**):

```bash
$ apt-get install sdl2 sdl2_image sdl2_ttf
```

***

## Build and play the game

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./Minesweeper
```

Enjoy :) \
K. D.