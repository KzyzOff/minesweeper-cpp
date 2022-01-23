
#include "BoardView.h"

BoardView::BoardView(MinesweeperCore* core, FontManager* font_mgr)
: m_core(core),
  m_font_mgr(font_mgr),
  m_reset_button(m_font_mgr),
  m_pause_button(m_font_mgr),
  m_btn_font_size(10),
  m_gap(1),
  m_offset(0),
  m_lb_flag(false),
  m_rb_flag(false)
{
	init();
}

void BoardView::init()
{
    setBoardSizing();
    setCells();
    int font_size = m_cell_size - m_cell_size / 10;
    m_offset = (m_cell_size - font_size) / 2;
    m_font_mgr->setSize(font_size);
    setBoardButtons();
}

void BoardView::setBoardSizing()
{
	int cell_w = (WINDOW_WIDTH - 40 - m_gap * (m_core->getX() - 1)) / m_core->getX();
	int cell_h = (WINDOW_HEIGHT - 40  - m_gap * (m_core->getY() - 1)) / m_core->getY();
	m_cell_size = (cell_w > cell_h) ? cell_h : cell_w;

	m_board_size.x = m_cell_size * m_core->getX() + m_gap * (m_core->getX() - 1);
	m_board_size.y = m_cell_size * m_core->getY() + m_gap * (m_core->getY() - 1);

	m_tlc.x = WINDOW_WIDTH / 2 - m_board_size.x / 2;
	m_tlc.y = WINDOW_HEIGHT / 2 - m_board_size.y / 2;

    m_clock_pos.x = m_clock_pos.y = 10;
    m_clock_size.x = m_tlc.x - m_clock_pos.x * 2;
    m_clock_size.y = m_clock_size.x / 3;
}

void BoardView::setCells()
{
	m_cells.clear();
	for (int i = 0; i < m_core->getY(); i++)
	{
		int y = m_tlc.y + i * (m_cell_size + m_gap);
		for (int j = 0; j < m_core->getX(); j++)
		{
			int x = m_tlc.x + j * (m_cell_size + m_gap);
			CellView cell(x, y, m_cell_size, m_cell_size, m_core->getCell(j, i));
			m_cells.push_back(cell);
		}
	}
	printf("Initialized cell vector successfully!\n");
}

void BoardView::setBoardButtons()
{
    Vec2i btn_size {
        m_clock_size.x - 10,
        m_clock_size.y
    };
    m_btn_font_size = btn_size.x / (int)strlen("Resume");
    setResetButton(btn_size);
    setPauseButton(btn_size);
}

void BoardView::setResetButton(Vec2i size)
{
    m_reset_button.setRect({
        WINDOW_WIDTH - m_clock_size.x, m_clock_pos.y,
        size.x, size.y
    });
    m_reset_button.setOutlineColor(Color::white);
    m_reset_button.setTextColor(Color::black);
    m_reset_button.setText("Reset");
    m_reset_button.setColor(Color::red);
    m_reset_button.setTextSize(m_btn_font_size);
    m_reset_button.centerText();
    Uint32 ev_num = SDL_RegisterEvents(1);
    if (ev_num != (Uint32) - 1)
    {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event));
        event.type = ev_num;
        event.user.data1 = (void*)CustomEvent::RESET;
        m_reset_button.setEvent(event);
    }
}

void BoardView::setPauseButton(Vec2i size)
{
    m_pause_button.setRect({
        m_reset_button.getRect().x,
        m_reset_button.getRect().y + int(size.y * 1.5),
        size.x,
        size.y
    });
    m_pause_button.setOutlineColor(Color::white);
    m_pause_button.setTextColor(Color::black);
    m_pause_button.setText("Pause");
    m_pause_button.setColor(Color::light_blue);
    m_pause_button.setTextSize(m_btn_font_size);
    m_pause_button.centerText();
    Uint32 ev_num = SDL_RegisterEvents(1);
    if (ev_num != (Uint32) - 1)
    {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event));
        event.type = ev_num;
        event.user.data1 = (void*)CustomEvent::PAUSE;
        m_pause_button.setEvent(event);
    }
}

void BoardView::updateMouse()
{
	SDL_PumpEvents();
	SDL_GetMouseState(&m_mouse.x, &m_mouse.y);
}

void BoardView::updateClock()
{
    m_timer = m_core->getClock()->duration(1000);
}

void BoardView::updateButtons()
{
    m_reset_button.update(m_mouse);
    if (m_core->getGameState() == GameState::PAUSE)
    {
        m_pause_button.setColor(Color::orange);
        m_pause_button.setText("Resume");
        m_pause_button.centerText();
    }
    else
    {
        m_pause_button.setColor(Color::light_blue);
        m_pause_button.setText("Pause");
        m_pause_button.centerText();
    }
    m_pause_button.update(m_mouse);
}

void BoardView::update()
{
	updateMouse();
    updateClock();
    updateButtons();
}

void BoardView::draw(SDL_Renderer *renderer)
{
	for (const auto &cell : m_cells)
	{
		drawCell(renderer, const_cast<CellView &>(cell));
	}
    if (m_core->getGameState() == GameState::PAUSE)
    {
        if ((SDL_GetTicks64() / 1000) % 2 == 0)
            drawClock(renderer);
    }
    else
        drawClock(renderer);
    drawButtons(renderer);
}

void BoardView::drawClock(SDL_Renderer* renderer)
{
	m_font_mgr->setColor(Color::yellow);
    m_font_mgr->setSize(m_clock_size.y);
	m_font_mgr->draw(renderer, 10, 10, std::to_string(m_timer));
}

void BoardView::drawCell(SDL_Renderer* renderer, CellView &cv)
{
	std::string text;
	switch (cv.cc->state)
	{
		case CellState::FLAG:
			setRenderColor(renderer, Color::light_green);
			text = "F";
			break;
		case CellState::REVEALED:
			if (cv.cc->mine)
				setRenderColor(renderer, Color::red);
			else
			{
				setRenderColor(renderer, Color::light_gray);
				text = (cv.cc->mine_count > 0) ? std::to_string(cv.cc->mine_count) : "";
			}
			break;
		case CellState::UNREVEALED:
			setRenderColor(renderer, Color::dark_gray);
			break;
		default:
			break;
	}
	SDL_RenderFillRect(renderer, &cv.rect);
	m_font_mgr->setColor(Color::black);
    m_font_mgr->setSize(cv.getRect().w);
	m_font_mgr->draw(renderer, cv.getRect().x + m_offset, cv.getRect().y, text);
}

void BoardView::drawButtons(SDL_Renderer *renderer)
{
    m_reset_button.draw(renderer);
    m_pause_button.draw(renderer);
}

void BoardView::setRenderColor(SDL_Renderer* renderer, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer,
						   color.r,
						   color.g,
						   color.b,
						   color.a);
}

// TODO: Decouple this method into smaller ones (for eg. make buttonUp() and buttonDown())
void BoardView::handleEvents(SDL_Event &event)
{
	for (int i = 0; i < int(m_cells.size()); i++)
	{
		if (m_cells.at(i).intersects(m_mouse))
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (event.type == SDL_MOUSEBUTTONDOWN && !m_lb_flag)
				{
					m_lb_flag = true;
					m_core->reveal(x2xy(i).x, x2xy(i).y);
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
					m_core->toggle_flag(x2xy(i).x, x2xy(i).y);
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
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        if (event.type == SDL_MOUSEBUTTONDOWN && !m_lb_flag)
        {
            if (m_reset_button.isActive())
                m_reset_button.onEvent();

            if (m_pause_button.isActive())
                m_pause_button.onEvent();

            m_rb_flag = true;
        }
        if (event.type == SDL_MOUSEBUTTONUP && m_rb_flag)
        {
            m_rb_flag = false;
            return;
        }
    }
}

Vec2i BoardView::x2xy(int x) const
{
	int width = m_core->getX();
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
	for (int i = 0; i < int(m_cells.size()); i++)
	{
		printf("[View] Cell (%d) state = %d, mine count = %d\n", i, m_core->getCell(x2xy(i).x, x2xy(i).y)->state,
		       m_core->getCell(x2xy(i).x, x2xy(i).y)->mine_count);
	}
}
