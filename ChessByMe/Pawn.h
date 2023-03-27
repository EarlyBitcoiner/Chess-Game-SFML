#ifndef PAWN_H
#define PAWN_H

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <array>

using namespace std;
using namespace sf;

class Pawn {
private:
	array<pair<int, int>, 8> posWhites; // starting positions of white pawns
	array<pair<int, int>, 8> posBlacks; // starting positions of black pawns
	Texture texture[2];
	RectangleShape pawnW[8];
	RectangleShape pawnB[8];

	bool enPassant = 0; // if value is 1 then en passant move is available.
	pair<int, int> enPassantPawnPos; // here we will keep the position of the last pawn which is in danger of en passant.

public:

	Pawn();

	pair<int, int>& getEnPassantPawnPos();

	void setEnPassantPawnPos(pair<int, int> pos);

	bool getEnPassant();

	void raiseEnPassant();

	void lowerEnPassant();

	array<pair<int, int>, 8>& getPosW();

	array<pair<int, int>, 8>& getPosB();

	Texture& getWhiteTexture();

	Texture& getBlackTexture();

	void GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	RectangleShape& getPawnWatPos(pair<int, int>);

	RectangleShape& getPawnWatIndex(int index);

	RectangleShape& getPawnBatPos(pair<int, int>);

	RectangleShape& getPawnBatIndex(int index);
};

#endif // !1

