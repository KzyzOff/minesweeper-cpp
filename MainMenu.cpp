
#include "MainMenu.h"

MainMenu::MainMenu(FontManager* font_mgr)
: m_font_mgr(font_mgr)
{
    init();
}

void MainMenu::init()
{
    setButtons();
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

}

void MainMenu::update()
{
    for (auto& button : m_buttons)
    {
        button.update();
    }
}

void MainMenu::setButtons()
{
    m_buttons.clear();
    int win_offset = 40;
    int button_offset = 15;
    m_button_size.y = (WINDOW_HEIGHT - 2 * win_offset - 3 * button_offset) / 4;
    m_button_size.x = (WINDOW_WIDTH - 2 * win_offset) / 2;
    int tlc_x = WINDOW_WIDTH / 2 - m_button_size.x / 2;
    Button b;
    for (int i = 0; i < 4; i++)
    {
        b.rect.h = m_button_size.y;
        b.rect.w = m_button_size.x;
        b.rect.x = tlc_x;
        b.rect.y = win_offset;
        win_offset += m_button_size.y + button_offset;
        m_buttons.push_back(b);
        m_buttons.at(i).active = false;
    }
    m_buttons.at(0).color = Color::green;
    m_buttons.at(0).text = "EASY";
    m_buttons.at(1).color = Color::orange;
    m_buttons.at(1).text = "MEDIUM";
    m_buttons.at(2).color = Color::red;
    m_buttons.at(2).text = "HARD";
    m_buttons.at(3).color = Color::yellow;
    m_buttons.at(3).text = "QUIT";
}

void Button::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
    if (active)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void Button::update()
{
    SDL_PumpEvents();
    Vec2i mouse {};
    SDL_GetMouseState(&mouse.x, &mouse.y);
    if (mouse.x > rect.x && mouse.x < rect.x + rect.w && mouse.y > rect.y && mouse.y < rect.y + rect.h)
    {
        active = true;
    }
    else
    {
        active = false;
    }
}
