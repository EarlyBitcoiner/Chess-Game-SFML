
#include "Board.h"
#include "Game.h"
#include "Figures.h"

using namespace sf;
using namespace std;


int main() {

	Game game;

	// Game loop
	while (game.isRunning()) { // we check on every iteration if the program is closed.

		// Updating
		game.update(); // all the game logic happens here.

		// Render frame
		game.render(); // here we just draw the shapes we have.

	}



	return 0;
} // 2 376 rows of code for this game.

