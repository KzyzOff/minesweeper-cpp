
#include "MinesweeperCore2D.h"

MinesweeperCore2D::MinesweeperCore2D(int x, int y, GameDifficulty difficulty)
: m_x(x),
  m_y(y),
  m_difficulty(difficulty),
  m_game_state(GameState::RUNNING),
  m_first_move(true),
  m_mine_count(0),
  m_clock(std::make_shared<Clock>())
{
	setBoard();
}

void MinesweeperCore2D::setBoard()
{
	m_game_state = GameState::RUNNING;
	m_board.clear();

	int dbg_x = 3, dbg_y = 3;

	m_board.resize((m_difficulty == GameDifficulty::DEBUG) ? dbg_x : m_x);
	for (auto &i : m_board)
	{
		i.resize((m_difficulty == GameDifficulty::DEBUG) ? dbg_y : m_y);
		fill(i.begin(), i.end(), CoreCell());
	}

	m_board_size = int(m_board.size() * m_board.at(0).size());
	// DEBUG ONLY
	if (m_difficulty == GameDifficulty::DEBUG)
	{
		m_x = dbg_x;
		m_y = dbg_y;
		m_board.at(0).at(0).mine = true;
		m_board.at(0).at(1).mine = true;
		m_board.at(0).at(2).state = CellState::UNREVEALED;
		m_board.at(1).at(0).state = CellState::REVEALED;
		m_board.at(1).at(1).mine = true;
		m_board.at(1).at(2).state = CellState::UNREVEALED;
		m_board.at(2).at(0).state = CellState::REVEALED;
		m_board.at(2).at(1).state = CellState::REVEALED;

		m_mine_count = 3;
//		m_first_move = false;

		return;
	}

	m_mine_count = int(float(m_x * m_y) * static_cast<float>(m_difficulty) / 100.f);
}

void MinesweeperCore2D::updateState()
{
	int unrevealed = m_board_size - m_mine_count;
	for (const auto &column : m_board)
	{
		for (const auto &cell : column)
		{
			if (cell.state == CellState::REVEALED)
			{
				unrevealed -= 1;
			}
		}
	}
	if (unrevealed == 0)
	{
		m_game_state = GameState::FINISHED_WIN;
	}
}

void MinesweeperCore2D::genMines(int count, int fm_x, int fm_y)
{
	std::srand(std::time(nullptr));
	int rand_x = std::rand() % m_x;
	int rand_y = std::rand() % m_y;
	while (count != 0)
	{
		if (!m_board.at(rand_x).at(rand_y).mine && rand_x != fm_x && rand_y != fm_y)
		{
			m_board.at(rand_x).at(rand_y).mine = true;
			count--;
		}
		else
		{
			rand_x = std::rand() % m_x;
			rand_y = std::rand() % m_y;
		}
	}
}

bool MinesweeperCore2D::isOutside(int x, int y) const
{
	if (x < 0 || x > m_x - 1) return true;
	if (y < 0 || y > m_y - 1) return true;

	return false;
}

void MinesweeperCore2D::reveal(int x, int y)
{
	if (m_game_state == GameState::FINISHED_LOSS || m_game_state == GameState::FINISHED_WIN) return;
	if (isOutside(x, y)) return;
	if (m_board.at(x).at(y).state == CellState::REVEALED || m_board.at(x).at(y).state == CellState::REVEALED) return;

	if (m_first_move)
	{
		m_first_move = false;
		genMines(m_mine_count, x, y);
		setMineCount();
	}

	floodReveal(x, y);
	if (!m_clock->isRunning())
		m_clock->start();

	if (m_board.at(x).at(y).mine)
	{
		m_game_state = GameState::FINISHED_LOSS;
		if (m_clock->isRunning())
			m_clock->stop();
		revealAll();
		return;
	}

	updateState();
	debug_draw();
}

void MinesweeperCore2D::toggle_flag(int x, int y)
{
	if (m_game_state == GameState::FINISHED_LOSS || m_game_state == GameState::FINISHED_WIN) return;
	if (isOutside(x, y)) return;
	if (m_board.at(x).at(y).state == CellState::REVEALED) return;

	if (m_board.at(x).at(y).state == CellState::FLAG)
		m_board.at(x).at(y).state = CellState::UNREVEALED;
	else
		m_board.at(x).at(y).state = CellState::FLAG;
}

int MinesweeperCore2D::countMines(int x, int y) const
{
	if (isOutside(x, y) /*|| m_board.at(x).at(y).state == CellState::UNREVEALED*/)
		return -1;

	int count = 0;
	// Check every possible direction from specified cell
	if (!isOutside(x - 1, y - 1)) { if (m_board.at(x - 1).at(y - 1).mine) count++; }
	if (!isOutside(x    , y - 1)) { if (m_board.at(x    ).at(y - 1).mine) count++; }
	if (!isOutside(x + 1, y - 1)) { if (m_board.at(x + 1).at(y - 1).mine) count++; }
	if (!isOutside(x + 1, y    )) { if (m_board.at(x + 1).at(y    ).mine) count++; }
	if (!isOutside(x + 1, y + 1)) { if (m_board.at(x + 1).at(y + 1).mine) count++; }
	if (!isOutside(x    , y + 1)) { if (m_board.at(x    ).at(y + 1).mine) count++; }
	if (!isOutside(x - 1, y + 1)) { if (m_board.at(x - 1).at(y + 1).mine) count++; }
	if (!isOutside(x - 1, y    )) { if (m_board.at(x - 1).at(y    ).mine) count++; }

	return count;
}

void MinesweeperCore2D::floodReveal(int x, int y)
{
	if (isOutside(x, y)) return;
	if (m_board.at(x).at(y).mine || m_board.at(x).at(y).visited) return;

	m_board.at(x).at(y).state = CellState::REVEALED;
	m_board.at(x).at(y).visited = true;

	if (countMines(x, y) > 0)
		return;

	floodReveal(x - 1, y);
	floodReveal(x + 1, y);
	floodReveal(x, y - 1);
	floodReveal(x, y + 1);

	floodReveal(x - 1, y + 1);
	floodReveal(x + 1, y + 1);
	floodReveal(x + 1, y - 1);
	floodReveal(x - 1, y - 1);

}

void MinesweeperCore2D::revealAll()
{
	for (auto &row : m_board)
	{
		for (auto &cell : row)
		{
			cell.state = CellState::REVEALED;
		}
	}
}

void MinesweeperCore2D::setMineCount()
{
	for (int i = 0; i < m_x; i++)
	{
		for (int j = 0; j < m_y; j++)
		{
			m_board.at(i).at(j) .mine_count = countMines(i, j);
			// TODO: Remove after debug phase
			printf("Mine count on cell (%d, %d) = %d\n", i, j, countMines(i, j));
		}
	}
}

CellState MinesweeperCore2D::getCellState(int x, int y) const
{
	return m_board.at(x).at(y).state;
}

void MinesweeperCore2D::debug_draw() const
{
	for (size_t y = 0; y < m_y; y++)
	{
		for (size_t x = 0; x < m_x; x++)
		{
			char sign = '.';
			if (m_board.at(x).at(y).state == CellState::REVEALED) {
				int mines = countMines(int(x), int(y));
				if (mines > 0) sign = '0' + mines;
				else sign = '_';
			}
			if (m_board.at(x).at(y).state == CellState::FLAG) sign = 'F';
			if (m_board.at(x).at(y).mine) sign = 'X';
			printf("%c", sign);
		}
		printf("\n");
	}
}

std::shared_ptr<std::vector<std::vector<CoreCell> > > MinesweeperCore2D::getBoard() const
{
	return std::make_shared<std::vector<std::vector<CoreCell>>>(m_board);
}
