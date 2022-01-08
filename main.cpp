
#include <iostream>

#include "App.h"
#include "App.h"
#include "MinesweeperCore.h"
#include "BoardView.h"

int main()
{
	App app("some title", 100, 100);
	app.run();
//	MinesweeperCore mc(15, 8, GameDifficulty::EASY);
//	mc.reveal(2, 2);
//
//	mc.debug_draw();
//	printf("\nCurrent game state is: %i", mc.getGameState());

	return 0;
}
