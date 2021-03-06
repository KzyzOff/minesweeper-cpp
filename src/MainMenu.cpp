
#include "MainMenu.h"

MainMenu::MainMenu(FontManager* font_mgr)
: m_font_mgr(font_mgr),
  m_quit(false)
{
    init();
}

void MainMenu::init()
{
    setMenu();
    m_quit = false;
}

void MainMenu::draw(SDL_Renderer* renderer)
{
    for (auto& button : m_buttons)
    {
        button.draw(renderer);
    }
}

void MainMenu::handleEvents(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        for (auto& button : m_buttons)
        {
            if (button.isActive() && !m_quit)
            {
                button.onEvent();
                m_quit = true;
                break;
            }
        }
    }
}

void MainMenu::update()
{
    SDL_PumpEvents();
    Vec2i mouse {};
    SDL_GetMouseState(&mouse.x, &mouse.y);
    for (auto& button : m_buttons)
    {
        button.update(mouse);
    }
}

void MainMenu::setMenu()
{
    m_buttons.clear();

    setButtonsSizing();
    m_buttons.at(0).setColor(Color::green);
    m_buttons.at(1).setColor(Color::orange);
    m_buttons.at(2).setColor(Color::red);
    m_buttons.at(3).setColor(Color::yellow);

    m_buttons.at(0).setText("EASY");
    m_buttons.at(1).setText("MEDIUM");
    m_buttons.at(2).setText("HARD");
    m_buttons.at(3).setText("QUIT");

    centerTextOnButtons();
    setButtonsEvents();
}

void MainMenu::setButtonsSizing()
{
    int win_offset = 40;
    int button_offset = 15;
    Vec2i size {
            (WINDOW_WIDTH - 2 * win_offset) * 2 / 3,
            (WINDOW_HEIGHT - 2 * win_offset - 3 * button_offset) / 4
    };
    int tlc_x = WINDOW_WIDTH / 2 - size.x / 2;
    for (int i = 0; i < 4; i++)
    {
        Button b(m_font_mgr);
        b.setRect({tlc_x, win_offset, size.x, size.y});
        b.setOutlineColor(Color::white);
        b.setTextColor(Color::black);
        b.setTextSize(b.getRect().h / 2);
        win_offset += size.y + button_offset;
        m_buttons.push_back(b);
    }
}

void MainMenu::centerTextOnButtons()
{
    for (auto& b : m_buttons)
    {
        b.centerText();
    }
}

void MainMenu::setButtonsEvents()
{
    Uint32 ev_num = SDL_RegisterEvents(1);
    if (ev_num != (Uint32) - 1)
    {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event));
        event.type = ev_num;
        event.user.data1 = (void*)GameDifficulty::EASY;
        m_buttons.at(0).setEvent(event);

        event.user.data1 = (void*)GameDifficulty::MEDIUM;
        m_buttons.at(1).setEvent(event);

        event.user.data1 = (void*)GameDifficulty::HARD;
        m_buttons.at(2).setEvent(event);

        event.type = SDL_QUIT;
        m_buttons.at(3).setEvent(event);
    }
}
