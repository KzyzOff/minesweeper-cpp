
#include "Button.h"

#include <utility>

Button::Button(std::shared_ptr<FontManager> font_mgr)
: m_font_mgr(std::move(font_mgr)),
  m_text(),
  m_text_pos({ 5, 5 }),
  m_text_size(5),
  m_rect({0, 0, 10, 10}),
  m_color(Color::white),
  m_outline_color(Color::orange),
  m_text_color(Color::black),
  m_event(),
  m_active(false)
{}

void Button::centerText()
{
    m_text_pos.x = m_rect.x + m_rect.w / 2 - (int)m_text.size() * m_text_size / 2;
    m_text_pos.y = m_rect.y + m_rect.h / 2 - m_text_size / 2;
}

void Button::draw(SDL_Renderer* renderer)
{
    drawRect(renderer);
    drawText(renderer);
}

void Button::drawRect(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, &m_rect);
    if (m_active)
    {
        SDL_SetRenderDrawColor(renderer, m_outline_color.r, m_outline_color.g,
                               m_outline_color.b, m_outline_color.a);
        SDL_Rect r{m_rect.x - 1, m_rect.y - 1, m_rect.w + 2, m_rect.h + 2};
        SDL_RenderDrawRect(renderer, &m_rect);
        SDL_RenderDrawRect(renderer, &r);
    }
}

void Button::drawText(SDL_Renderer *renderer)
{
    m_font_mgr->setSize(m_text_size);
    m_font_mgr->setColor(m_text_color);
    m_font_mgr->draw(renderer, m_text_pos.x, m_text_pos.y, m_text);
}

void Button::update(const Vec2i mouse_pos)
{
    if (intersects(mouse_pos))
        m_active = true;
    else
        m_active = false;
}

bool Button::intersects(const Vec2i& p) const
{
    return p.x > m_rect.x && p.x < m_rect.x + m_rect.w && p.y > m_rect.y && p.y < m_rect.y + m_rect.h;
}

void Button::setSize(Vec2i size)
{
    m_rect.w = size.x;
    m_rect.h = size.y;
}

void Button::setPosition(Vec2i pos)
{
    m_rect.x = pos.x;
    m_rect.y = pos.y;
}

void Button::setRect(SDL_Rect rect)
{
    setPosition({rect.x, rect.y});
    setSize({rect.w, rect.h});
}
