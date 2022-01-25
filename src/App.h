
#ifndef MINESWEEPER_APP_H
#define MINESWEEPER_APP_H


#include "header.h"
#include <string>
#include <iostream>
#include <memory>

#include "CONSTANTS.h"
#include "Controller.h"
#include "MainMenu.h"
#include "BoardController.h"
#include "BoardView.h"
#include "FontManager.h"

// TODO: Add EndScreen class with exit button, game result and time spent to achieve win

class App
{
public:
    App(const std::string &title, int x, int y);
    ~App();

    void run();

    bool running() const { return m_running; };

private:
    void handleEvents();
    void render();
    std::unique_ptr<Controller> initBoard(GameDifficulty diff);

    std::unique_ptr<Controller> m_current;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    std::shared_ptr<FontManager> m_fm;

    bool m_running;

};


#endif //MINESWEEPER_APP_H
