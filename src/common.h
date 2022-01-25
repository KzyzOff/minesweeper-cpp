
#ifndef MINESWEEPER_COMMON_H
#define MINESWEEPER_COMMON_H


enum class AppState { Menu, Game, Exit };
enum class CellState { FLAG, REVEALED, UNREVEALED };
enum class GameState { RUNNING, PAUSE, FINISHED_LOSS, FINISHED_WIN };
enum class GameDifficulty { EASY = 15, MEDIUM = 20, HARD = 25 };
enum class CustomEvent { RESET = 2, PAUSE = 3 };

struct Vec2i
{
    int x;
    int y;
};


#endif //MINESWEEPER_COMMON_H
