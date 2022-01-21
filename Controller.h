
#ifndef MINESWEEPER_CONTROLLER_H
#define MINESWEEPER_CONTROLLER_H


#include "header.h"

#include "common.h"

class Controller
{
public:
    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void handleEvents(SDL_Event& event) = 0;
    virtual void update() = 0;
};


#endif //MINESWEEPER_CONTROLLER_H
