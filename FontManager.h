
#ifndef MINESWEEPER_FONTMANAGER_H
#define MINESWEEPER_FONTMANAGER_H


#include <SDL2/SDL_ttf.h>
#include <string>

class FontManager
{
public:
	explicit FontManager(const std::string &file);

	void setSize(int size);
	void setColor(SDL_Color color);
	void draw(SDL_Renderer* renderer, int x, int y, const std::string &text);

    int getSize() const { return m_size; };

private:
	int m_size;
	TTF_Font* m_font;
	SDL_Color m_color;

};


#endif //MINESWEEPER_FONTMANAGER_H
