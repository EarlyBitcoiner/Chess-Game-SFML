#include "Board.h"
#include "Game.h"

Board::Board() {

	Color white = Color::White;
	Color black = Color::Black;
	Color current = white;
	Vector2f squareSize(100.f, 100.f);

	for (size_t r = 0;r < 8;r++) {
		for (size_t c = 0;c < 8;c++) {

			board[r][c].setSize(squareSize);
			board[r][c].setFillColor(current);
			board[r][c].setPosition(Vector2f
			                                (c*100.f // X
				                            ,r*100.f) // Y 
			                       );

			if (c != 7) {
				(current == white) ? current = black : current = white;
			}

		}
	}

}
