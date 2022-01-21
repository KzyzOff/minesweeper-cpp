
#ifndef MINESWEEPER_BUTTON_H
#define MINESWEEPER_BUTTON_H


#include "header.h"
#include <string>
#include <memory>
#include <utility>

#include "Color.h"
#include "common.h"
#include "FontManager.h"

// TODO: Try to decouple this bloated class (possible solution is to use Builder design pattern)
// https://refactoring.guru/pl/design-patterns/builder

class Button
{
public:
    explicit Button(FontManager* font_mgr);

    void draw(SDL_Renderer* renderer);
    void update(const Vec2i mouse);
    void onEvent() { SDL_PushEvent(&m_event); };

    void setSize(Vec2i size);
    void setPosition(Vec2i pos);
    void setRect(SDL_Rect rect);
    void setText(std::string text) { m_text = std::move(text); };
    void setTextSize(int size) { m_text_size = size; };
    void setTextPos(Vec2i pos) { m_text_pos = pos; };
    void setEvent(SDL_Event event) { m_event = event; };
    void setColor(SDL_Color color) { m_color = color; };
    void setOutlineColor(SDL_Color color) { m_outline_color = color; };
    void setTextColor(SDL_Color color) { m_text_color = color; };

    bool intersects(const Vec2i& p) const;
    SDL_Rect getRect() const { return m_rect; };
    std::string getText() const { return m_text; };
    int getFontSize() const { return m_text_size; };
    bool isActive() const { return m_active; };

private:
    void drawRect(SDL_Renderer* renderer);
    void drawText(SDL_Renderer* renderer);

    std::shared_ptr<FontManager> m_font_mgr;
    std::string m_text;
    Vec2i m_text_pos;
    int m_text_size;
    SDL_Rect m_rect;
    SDL_Color m_color;
    SDL_Color m_outline_color;
    SDL_Color m_text_color;
    SDL_Event m_event;
    bool m_active;

};


#endif //MINESWEEPER_BUTTON_H
