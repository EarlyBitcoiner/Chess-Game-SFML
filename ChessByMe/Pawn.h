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
public:
	array<pair<int, int>,8> posW; // starting positions of white pawns
	array<pair<int, int>, 8> posB; // starting positions of black pawns
	Texture texture[2];
	RectangleShape pawnW[8];
	RectangleShape pawnB[8];

	Pawn();


	void GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	RectangleShape& getPawnW(pair<int, int>);

	RectangleShape& getPawnB(pair<int, int>);
};

#endif // !1

