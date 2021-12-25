
#ifndef MINESWEEPER_MENUSTATE_H
#define MINESWEEPER_MENUSTATE_H


#include "AppState.h"

class MenuState : public AppState
{
public:
	MenuState() = default;

	virtual void draw(SDL_Renderer* renderer);
	virtual void handleEvents(SDL_Event& event);
	virtual void update();

};


#endif //MINESWEEPER_MENUSTATE_H
