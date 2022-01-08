
#ifndef MINESWEEPER_BOARDVIEW_H
#define MINESWEEPER_BOARDVIEW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <utility>
#include <memory>

#include "MinesweeperCore.h"
#include "FontManager.h"
#include "Color.h"
#include "common.h"
#include "CONSTANTS.h"

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
	BoardView(MinesweeperCore* core, FontManager* font_mgr);
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

	std::shared_ptr<MinesweeperCore> m_core;
	std::shared_ptr<FontManager> m_font_mgr;
	std::vector<CellView> m_cells;
//	Vec2i m_win_size;
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
