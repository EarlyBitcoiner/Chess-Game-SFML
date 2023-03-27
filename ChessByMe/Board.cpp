#include "Board.h"
#include "Game.h"

Board::Board() {

	this->textures[0].loadFromFile("Textures/w_square.png");
	this->textures[1].loadFromFile("Textures/b_square.png");
	Texture* current = &this->textures[0];
	Vector2f squareSize(100.f, 100.f);

	for (size_t r = 0;r < 8;r++) {
		for (size_t c = 0;c < 8;c++) {

			board[r][c].setSize(squareSize);
			board[r][c].setTexture(current);
			board[r][c].setPosition(Vector2f
			                                (c*100.f // X
				                            ,r*100.f) // Y 
			                       );

			if (c != 7) {
				(current == &textures[0]) ? current = &this->textures[1] : current = &this->textures[0];
			}

		}
	}

}

RectangleShape* Board::getBoardBox(int& x, int& y)
{
	return &this->board[x][y];
}
