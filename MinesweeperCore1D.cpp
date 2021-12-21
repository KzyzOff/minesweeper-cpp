
#include "MinesweeperCore1D.h"


#include "MinesweeperCore1D.h"

MinesweeperCore1D::MinesweeperCore1D(Vec2i board_size, GameDifficulty difficulty)
		: m_board_size(board_size),
		  m_difficulty(difficulty),
		  m_game_state(GameState::RUNNING),
		  m_first_move(true),
		  m_mine_count(0),
		  m_clock(std::make_shared<Clock>())
{
	setBoard();
}

void MinesweeperCore1D::setBoard()
{
	m_game_state = GameState::RUNNING;
	m_board.clear();

	if (m_difficulty == GameDifficulty::DEBUG)
		m_board_size = { 4, 4 };

	m_board.resize(m_board_size.x * m_board_size.y);
	fill(m_board.begin(), m_board.end(), std::make_shared<CoreCell>());

	// DEBUG ONLY
	if (m_difficulty == GameDifficulty::DEBUG)
	{
		m_board.at(0)->mine = true;
		m_board.at(0)->mine = true;
		m_board.at(0)->state = CellState::UNREVEALED;
		m_board.at(1)->state = CellState::REVEALED;
		m_board.at(1)->mine = true;
		m_board.at(1)->state = CellState::UNREVEALED;
		m_board.at(2)->state = CellState::REVEALED;
		m_board.at(2)->state = CellState::REVEALED;
		m_mine_count = 3;
//		m_first_move = false;
		return;
	}

	m_mine_count = int(float(m_board_size.x * m_board_size.y) * static_cast<float>(m_difficulty) / 100.f);
}

void MinesweeperCore1D::updateState()
{
	int unrevealed = m_board_size - m_mine_count;
	for (const auto &column : m_board)
	{
		unrevealed -= 1;
	}
	if (unrevealed == 0)
	{
		m_game_state = GameState::FINISHED_WIN;
	}
}

void MinesweeperCore1D::genMines(int count, int fm_x, int fm_y)
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

bool MinesweeperCore1D::isOutside(int x, int y) const
{
	if (x < 0 || x > m_x - 1) return true;
	if (y < 0 || y > m_y - 1) return true;

	return false;
}

void MinesweeperCore1D::reveal(int x, int y)
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

void MinesweeperCore1D::toggle_flag(int x, int y)
{
	if (m_game_state == GameState::FINISHED_LOSS || m_game_state == GameState::FINISHED_WIN) return;
	if (isOutside(x, y)) return;
	if (m_board.at(x).at(y).state == CellState::REVEALED) return;

	if (m_board.at(x).at(y).state == CellState::FLAG)
		m_board.at(x).at(y).state = CellState::UNREVEALED;
	else
		m_board.at(x).at(y).state = CellState::FLAG;
}

int MinesweeperCore1D::countMines(int x, int y) const
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

void MinesweeperCore1D::floodReveal(int x, int y)
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

void MinesweeperCore1D::revealAll()
{
	for (auto &row : m_board)
	{
		for (auto &cell : row)
		{
			cell.state = CellState::REVEALED;
		}
	}
}

void MinesweeperCore1D::setMineCount()
{
	for (int i = 0; i < m_x; i++)
	{
		for (int j = 0; j < m_y; j++)
		{
			m_board.at(i).at(j) .mine_count = countMines(i, j);
			printf("Mine count on cell (%d, %d) = %d\n", i, j, countMines(i, j));
		}
	}
}

CellState MinesweeperCore1D::getCellState(int x, int y) const
{
	return m_board.at(x).at(y).state;
}

void MinesweeperCore1D::debug_draw() const
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

std::shared_ptr<std::vector<std::vector<CoreCell> > > MinesweeperCore1D::getBoard() const
{
	return std::make_shared<std::vector<std::vector<CoreCell>>>(m_board);
}
