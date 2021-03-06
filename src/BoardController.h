
#ifndef MINESWEEPER_BOARDCONTROLLER_H
#define MINESWEEPER_BOARDCONTROLLER_H


#include <memory>

#include "CONSTANTS.h"
#include "common.h"
#include "FontManager.h"
#include "Controller.h"
#include "MinesweeperCore.h"
#include "BoardView.h"

class BoardController : public Controller
{
public:
    BoardController(int x, int y, GameDifficulty diff, FontManager* font_mgr);

    void draw(SDL_Renderer* renderer) override;
    void handleEvents(SDL_Event& event) override;
    void update() override;

    void setBoard(int x, int y, GameDifficulty diff);
    void setView(MinesweeperCore* core, FontManager* font_mgr);

private:
    std::shared_ptr<FontManager> m_font_mgr;
    std::shared_ptr<MinesweeperCore> m_core;
    std::shared_ptr<BoardView> m_view;

};


#endif //MINESWEEPER_BOARDCONTROLLER_H
