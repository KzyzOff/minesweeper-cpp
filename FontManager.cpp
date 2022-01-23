
#include "FontManager.h"

FontManager::FontManager(const std::string &file)
: m_font(nullptr),
  m_size(80),
  m_color({255, 255, 255, 255})
{
	if (TTF_Init() != -1)
	{
		m_font = TTF_OpenFont(file.c_str(), m_size);
        printf("Font loaded successfully!\n");
	}
}

void FontManager::setSize(int size)
{
	m_size = size;
}

void FontManager::setColor(SDL_Color color)
{
	m_color = color;
}

void FontManager::draw(SDL_Renderer *renderer, int x, int y, const std::string &text)
{
	SDL_Surface* tmp_surface = TTF_RenderText_Solid(m_font, text.c_str(), m_color);
	// Converting font into a texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
    rect.w = m_size * (int)text.size();
	rect.h = m_size;

	SDL_RenderCopy(renderer, texture, nullptr, &rect);

	SDL_FreeSurface(tmp_surface);
	SDL_DestroyTexture(texture);
}
