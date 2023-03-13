#include "Figures.h"

Figures::Figures() {

	for (size_t r = 2;r < 6;r++) {
		for (size_t c = 0;c < 8;c++) {
			board[r][c] = '.';
		}
	}

	LoadStartingPositions();
}

void Figures::LoadStartingPositions() {
	//White
	board[0][0] = 'R'; board[0][7] = 'R';
	board[0][1] = 'K'; board[0][6] = 'K';
	board[0][2] = 'B'; board[0][5] = 'B';
	board[0][3] = '1'; board[0][4] = 'Q';

	for (size_t i = 0;i < 8;i++)
		board[1][i] = 'P';
	//Black
	board[7][0] = 'r'; board[7][7] = 'r';
	board[7][1] = 'k'; board[7][6] = 'k';
	board[7][2] = 'b'; board[7][5] = 'b';
	board[7][3] = '2'; board[7][4] = 'q';

	for (size_t i = 0;i < 8;i++)
		board[6][i] = 'p';



};




