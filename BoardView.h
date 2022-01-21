
#ifndef MINESWEEPER_BOARDVIEW_H
#define MINESWEEPER_BOARDVIEW_H

#include "header.h"
#include <cstdlib>
#include <utility>
#include <memory>

#include "MinesweeperCore.h"
#include "Button.h"
#include "FontManager.h"
#include "Color.h"
#include "common.h"
#include "CONSTANTS.h"

// TODO: Add restart button
// TODO: Add pause button

struct CellView
{
	std::shared_ptr<const CoreCell> cc;
	SDL_Rect rect;
	CellView(int x, int y, int w, int h, const CoreCell* cc) : cc(cc), rect({x, y, w, h}) {}
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
    void setResetButton();
    void setPauseButton();
	void updateMouse();
    void updateClock();
    void updateButtons();
	void drawClock(SDL_Renderer* renderer);
	void drawCell(SDL_Renderer* renderer, CellView &cv);
    void drawButtons(SDL_Renderer* renderer);
	static void setRenderColor(SDL_Renderer* renderer, SDL_Color color);

	Vec2i x2xy(int x) const;

	std::shared_ptr<MinesweeperCore> m_core;
	std::shared_ptr<FontManager> m_font_mgr;
	std::vector<CellView> m_cells;
    Button m_reset_button;
//    Button m_pause_button;
	int m_cell_size;
	Vec2i m_tlc;
	Vec2i m_board_size;
	int m_gap;
	int m_offset;
    Vec2i m_clock_pos;
    Vec2i m_clock_size;
    Uint64 m_timer;
	Vec2i m_mouse;
	bool m_lb_flag;
	bool m_rb_flag;

};


#endif //MINESWEEPER_BOARDVIEW_H
