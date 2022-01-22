
#ifndef MINESWEEPER_BOARDCONTROLLER_H
#define MINESWEEPER_BOARDCONTROLLER_H


#include <memory>

#include "CONSTANTS.h"
#include "common.h"
#include "FontManager.h"
#include "Controller.h"
#include "MinesweeperCore.h"
#include "BoardView.h"

// TODO: Add pause button (need to add new mechanics in MinesweeperCore and BoardView classes)
// TODO: Add reset mechanics

class BoardController : public Controller
{
public:
    BoardController(int x, int y, GameDifficulty diff, FontManager* font_mgr);

    void draw(SDL_Renderer* renderer) override;
    void handleEvents(SDL_Event& event) override;
    void update() override;

    void setBoard(int x, int y, GameDifficulty diff);

private:
    std::shared_ptr<FontManager> m_font_mgr;
    std::shared_ptr<MinesweeperCore> m_core;
    std::shared_ptr<BoardView> m_view;

};


#endif //MINESWEEPER_BOARDCONTROLLER_H
