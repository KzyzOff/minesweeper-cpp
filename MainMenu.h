
#ifndef MINESWEEPER_MAINMENU_H
#define MINESWEEPER_MAINMENU_H


#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>

#include "CONSTANTS.h"
#include "common.h"
#include "Color.h"
#include "FontManager.h"
#include "Controller.h"

struct Button
{
    std::string text;
    SDL_Rect rect;
    SDL_Color color;
    bool active;
    void draw(SDL_Renderer* renderer);
    void update();
};

class MainMenu : public Controller {
public:
    explicit MainMenu(FontManager* font_mgr);

    void draw(SDL_Renderer* renderer) override;
    void handleEvents(SDL_Event& event) override;
    void update() override;
    void init();

private:
    void setButtons();

    std::shared_ptr<FontManager> m_font_mgr;
    Vec2i m_button_size;
    std::vector<Button> m_buttons;

};


#endif //MINESWEEPER_MAINMENU_H
