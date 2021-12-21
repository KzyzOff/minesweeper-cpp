
#include "BoardView.h"

BoardView::BoardView(MinesweeperCore2D &mc, FontManager &fm, int win_w, int win_h)
: m_core(mc),
  m_font_mgr(fm),
  m_win_size({win_w, win_h}),
  m_gap(1),
  m_offset(0),
  m_lb_flag(false),
  m_rb_flag(false),
  m_font_color({20, 20, 20})
{
	setBoardSizing();
	setCells();
	int font_size = m_cell_size - m_cell_size / 10;
	m_offset = (m_cell_size - font_size) / 2;
	m_font_mgr.setSize(font_size);
	m_font_mgr.setColor(m_font_color);
//	debug_print();
}

void BoardView::setBoardSizing()
{
	int cell_w = (m_win_size.x - 40 - m_gap * (m_core.getX() - 1)) / m_core.getX();
	int cell_h = (m_win_size.y - 40  - m_gap * (m_core.getY() - 1)) / m_core.getY();
	m_cell_size = (cell_w > cell_h) ? cell_h : cell_w;

	m_board_size.x = m_cell_size * m_core.getX() + m_gap * (m_core.getX() - 1);
	m_board_size.y = m_cell_size * m_core.getY() + m_gap * (m_core.getY() - 1);

	m_tlc.x = m_win_size.x / 2 - m_board_size.x / 2;
	m_tlc.y = m_win_size.y / 2 - m_board_size.y / 2;
}

void BoardView::setCells()
{
	m_cells.clear();
	int x = 0;
	int y = 0;
	for (int i = 0; i < m_core.getY(); i++)
	{
		y = m_tlc.y + i * (m_cell_size + m_gap);
		for (int j = 0; j < m_core.getX(); j++)
		{
			x = m_tlc.x + j * (m_cell_size + m_gap);
			CellView cell(x, y, m_cell_size, m_cell_size);
			m_cells.push_back(cell);
		}
	}
	printf("Initialized cell vector successfully!\n");
}

void BoardView::updateMouse()
{
	SDL_PumpEvents();
	m_mouse_buttons = SDL_GetMouseState(&m_mouse.x, &m_mouse.y);
}

void BoardView::update()
{
	updateMouse();
	Vec2i pos {};
	for (int i = 0; i < m_cells.size(); i++)
	{
		pos = x2xy(i);
		m_cells.at(i).state =  m_core.getCellState(pos.x, pos.y);
		if (m_core.getCellState(pos.x, pos.y) == CellState::REVEALED)
		{
			m_cells.at(i).mines = m_core.countMines(pos.x, pos.y);
		}
	}
}

void BoardView::draw(SDL_Renderer *renderer)
{
	for (auto cell : m_cells)
	{
		switch (cell.state)
		{
			case CellState::FLAG:
				SDL_SetRenderDrawColor(renderer, 114, 232, 157, 255);
				break;
			case CellState::REVEALED:
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				break;
			case CellState::UNREVEALED:
				SDL_SetRenderDrawColor(renderer, 72, 122, 176, 255);
				break;
			default:
				SDL_SetRenderDrawColor(renderer, 247, 255, 249, 255);
				break;
		}
		SDL_RenderFillRect(renderer, &cell.rect);
		if (cell.state == CellState::REVEALED)
		{
			std::string count = (cell.mines > 0) ? std::to_string(cell.mines) : "";
			m_font_mgr.draw(renderer, cell.getRect().x + m_offset, cell.getRect().y, count);
		}

		if (cell.state == CellState::FLAG)
		{
			const std::string f = "F";
			m_font_mgr.draw(renderer, cell.getRect().x + m_offset, cell.getRect().y, f);
		}
	}
	Uint64 clock = (m_core.getClock()->isRunning())
			? m_core.getClock()->fromStart(1000)
			: m_core.getClock()->duration(1000);
	m_font_mgr.draw(renderer, 10, 10, std::to_string(clock));
}

void BoardView::handleEvents(SDL_Event &event)
{
	for (int i = 0; i < m_cells.size(); i++)
	{
		if (m_cells.at(i).intersects(m_mouse))
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (event.type == SDL_MOUSEBUTTONDOWN && !m_lb_flag)
				{
					m_lb_flag = true;
					m_core.reveal(x2xy(i).x, x2xy(i).y);
					return;
				}
				if (event.type == SDL_MOUSEBUTTONUP && m_lb_flag)
				{
					m_lb_flag = false;
					return;
				}
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				if (event.type == SDL_MOUSEBUTTONDOWN && !m_lb_flag)
				{
					m_rb_flag = true;
					m_core.toggle_flag(x2xy(i).x, x2xy(i).y);
					return;
				}
				if (event.type == SDL_MOUSEBUTTONUP && m_rb_flag)
				{
					m_rb_flag = false;
					return;
				}
			}
		}
	}
}

Vec2i BoardView::x2xy(int x) const
{
	int width = m_core.getX();
	int _x = x % width;
	int _y = x / width;

	return {_x, _y};
}

bool CellView::intersects(Vec2i mouse) const
{
	if (mouse.x > getRect().x && mouse.x < getRect().x + getRect().w &&
		mouse.y > getRect().y && mouse.y < getRect().y + getRect().h)
		return true;
	return false;
}

void BoardView::debug_print() const
{
	for (int i = 0; i < m_cells.size(); i++)
	{
		SDL_Rect rect = m_cells.at(i).rect;
		printf("Cell [%d] = (%d, %d), size = (%d, %d)\n",
			   i, rect.x, rect.y, rect.w, rect.h);
	}
}
