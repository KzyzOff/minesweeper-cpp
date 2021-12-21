
#ifndef MINESWEEPER_APPSTATE_H
#define MINESWEEPER_APPSTATE_H


#include <SDL2/SDL.h>

class AppState
{
public:
	virtual ~AppState();

	virtual void handleEvents(SDL_Event& event);
	virtual void update();
};

#endif //MINESWEEPER_APPSTATE_H
