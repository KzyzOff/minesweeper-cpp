
#ifndef MINESWEEPER_FONTMANAGER_H
#define MINESWEEPER_FONTMANAGER_H


#include "header.h"
#include <string>
//#include <memory>

#include "common.h"

class FontManager
{
public:
	explicit FontManager(const std::string &file);

	void setSize(int size);
	void setColor(SDL_Color color);
	void draw(SDL_Renderer* renderer, int x, int y, const std::string &text);

    int getSize() const { return m_size; };

private:
    TTF_Font* m_font;
    int m_size;
	SDL_Color m_color;

};


#endif //MINESWEEPER_FONTMANAGER_H
