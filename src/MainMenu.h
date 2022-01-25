
#ifndef MINESWEEPER_MAINMENU_H
#define MINESWEEPER_MAINMENU_H


#include <memory>
#include <vector>

#include "Controller.h"
#include "Button.h"
#include "FontManager.h"
#include "Color.h"
#include "common.h"
#include "CONSTANTS.h"

class MainMenu : public Controller {
public:
    explicit MainMenu(FontManager* font_mgr);

    void draw(SDL_Renderer* renderer) override;
    void handleEvents(SDL_Event& event) override;
    void update() override;
    void init();

private:
    void setMenu();
    void setButtonsSizing();
    void setButtonsEvents();
    void centerTextOnButtons();

    std::shared_ptr<FontManager> m_font_mgr;
    std::vector<Button> m_buttons;
    bool m_quit;

};


#endif //MINESWEEPER_MAINMENU_H
