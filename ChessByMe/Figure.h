#ifndef FIGURE_H
#define FIGURE_H

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <array>

using namespace std;
using namespace sf;

class Figure {
public:
	void GetPossiblePosWhitesDiagonaly(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetPossiblePosBlacksDiagonaly(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetPossiblePosRookWhites(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetPossiblePosRookBlacks(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetPossiblePosQueenWhites(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetPossiblePosQueenBlacks(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetPossiblePosKnightWhites(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetPossiblePosKnightBlacks(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetPossiblePosPawnWhites(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetPossiblePosPawnBlacks(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetPossiblePosKingWhites(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetPossiblePosKingBlacks(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);
};

#endif // !FIGURE_H

