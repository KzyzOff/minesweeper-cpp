

#ifndef MINESWEEPER_STATE_H
#define MINESWEEPER_STATE_H


#include <SDL2/SDL.h>
#include "common.h"

class State
{
public:
    virtual void draw(SDL_Renderer* renderer);
    virtual void handleEvent(SDL_Event& event);
    virtual State onExit();
};


#endif //MINESWEEPER_STATE_H
