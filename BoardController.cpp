
#include "BoardController.h"

BoardController::BoardController(int x, int y, GameDifficulty diff, FontManager* font_mgr)
: m_core(nullptr),
  m_view(nullptr),
  m_font_mgr(font_mgr)
{
    init(x, y, diff);
}

void BoardController::draw(SDL_Renderer *renderer)
{
    m_view->draw(renderer);
}

void BoardController::handleEvents(SDL_Event &event)
{
    m_view->handleEvents(event);
}

void BoardController::update()
{
    m_view->update();
}

void BoardController::init(int x, int y, GameDifficulty diff)
{
    m_core = std::make_shared<MinesweeperCore>(x, y, diff);
    m_view = std::make_shared<BoardView>(m_core.get(), m_font_mgr.get());
}
