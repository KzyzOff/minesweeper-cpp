
#include "BoardController.h"

BoardController::BoardController(int x, int y, GameDifficulty diff, FontManager* font_mgr)
: m_font_mgr(font_mgr),
  m_core(nullptr),
  m_view(nullptr)
{
    setBoard(x, y, diff);
    setView(m_core.get(), m_font_mgr.get());
}

void BoardController::draw(SDL_Renderer *renderer)
{
    m_view->draw(renderer);
}

void BoardController::handleEvents(SDL_Event &event)
{
    m_view->handleEvents(event);

    if (event.user.data1 == (void*)CustomEvent::RESET)
    {
        m_core->reset();
        printf("It's a reset!\n");
    }

    if (event.user.data1 == (void*)CustomEvent::PAUSE)
    {
        m_core->togglePause();
        printf("It's a pause!\n");
    }
}

void BoardController::update()
{
    m_view->update();
}

void BoardController::setBoard(int x, int y, GameDifficulty diff)
{
    m_core = std::make_shared<MinesweeperCore>(x, y, diff);
}

void BoardController::setView(MinesweeperCore* core, FontManager* font_mgr)
{
    m_view = std::make_shared<BoardView>(core, font_mgr);
}
