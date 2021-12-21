
#include <iostream>

#include "App.h"
#include "MinesweeperCore2D.h"
#include "BoardView.h"

int main()
{
	App app("some title", 100, 100, 600, 400);
	app.run();
//	MinesweeperCore2D mc(15, 8, GameDifficulty::EASY);
//	mc.reveal(2, 2);
//
//	mc.debug_draw();
//	printf("\nCurrent game state is: %i", mc.getGameState());

	return 0;
}
