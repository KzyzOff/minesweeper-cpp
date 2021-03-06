

#ifndef MINESWEEPER_MINESWEEPERCORE_H
#define MINESWEEPER_MINESWEEPERCORE_H


#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>
#include <memory>

#include "common.h"
#include "Clock.h"

struct CoreCell
{
	CellState state;
	bool mine;
	bool visited;
	unsigned short mine_count;
	CoreCell() : state(CellState::UNREVEALED), mine(false), visited(false), mine_count(0) {}
};

class MinesweeperCore
{
public:
	MinesweeperCore(int x, int y, GameDifficulty difficulty);

    void init();
    void reset();

    void reveal(int x, int y);
    void toggle_flag(int x, int y);

    void togglePause();
    int getX() const { return m_x; };
    int getY() const { return m_y; };
    GameState getGameState() const { return m_game_state; };
    const CoreCell* getCell(int x, int y) const;
    int countMines(int x, int y) const;

	std::shared_ptr<Clock> getClock() const { return m_clock; };

	void debug_draw() const;

private:
    void updateState();
	void genMines(int count, int fm_x, int fm_y);
	void floodReveal(int x, int y);
	void revealAll();
	void setMineCount();
	bool isOutside(int x, int y) const;

	GameState m_game_state;
	GameDifficulty m_difficulty;

	std::vector<std::vector<CoreCell>> m_board;
	bool m_first_move;
	int m_x;
	int m_y;
	int m_board_size;
	int m_mine_count;

	std::shared_ptr<Clock> m_clock;

};


#endif //MINESWEEPER_MINESWEEPERCORE_H
