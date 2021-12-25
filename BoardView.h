
#ifndef MINESWEEPER_BOARDVIEW_H
#define MINESWEEPER_BOARDVIEW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <utility>

#include "MinesweeperCore.h"
#include "FontManager.h"
#include "Color.h"

struct Vec2i
{
	int x;
	int y;
};

// TODO: Make use of one base SDL_Rect, get rid of separate SDL_Rect for every cell on board
//       Test cases where you can use one SDL_Rect instead of bloating memory with excess SDL_Rect
// TODO: Debug flag toggling (doesn't seem to work)

struct CellView
{
	std::shared_ptr<const CoreCell> cc;
	SDL_Rect rect;
	CellView(int x, int y, int w, int h, const CoreCell* cc) : rect({x, y, w, h}), cc(cc) {}
	SDL_Rect getRect() const { return rect; }
	bool intersects(Vec2i mouse) const;
};

class BoardView
{
public:
	BoardView(MinesweeperCore &mc, FontManager &fm, int win_w, int win_h);
	~BoardView() = default;

	void update();
	void draw(SDL_Renderer *renderer);
	void handleEvents(SDL_Event &event);


	void debug_print() const;

private:
	void setBoardSizing();
	void setCells();
	void updateMouse();
	void drawClock(SDL_Renderer* renderer);
	void drawCell(SDL_Renderer* renderer, CellView &cv);
	static void setRenderColor(SDL_Renderer* renderer, SDL_Color color);

	Vec2i x2xy(int x) const;

	MinesweeperCore &m_core;
	FontManager &m_font_mgr;
//	SDL_Color m_font_color;
	std::vector<CellView> m_cells;
	Vec2i m_win_size;
	int m_cell_size;
	Vec2i m_tlc;
	Vec2i m_board_size;
	int m_gap;
	int m_offset;
	Vec2i m_mouse;
	// Mouse button flags
	bool m_lb_flag;
	bool m_rb_flag;
	Uint32 m_mouse_buttons;

};


#endif //MINESWEEPER_BOARDVIEW_H
