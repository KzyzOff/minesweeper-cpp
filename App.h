
#ifndef MINESWEEPER_APP_H
#define MINESWEEPER_APP_H


#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#include "BoardView.h"
#include "FontManager.h"

class App
{
public:
	App(const std::string &title, int x, int y, int width, int height);
	~App();

	void run();

	bool running() const { return m_running; };

private:
	void handleEvents();
	void update();
	void render();

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	MinesweeperCore2D* m_mc;
	FontManager* m_fm;
	BoardView* m_bv;

	bool m_running;

};


#endif //MINESWEEPER_APP_H
