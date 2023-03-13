#ifndef QUEEN_H
#define QUEEN_H

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <array>

using namespace std;
using namespace sf;

class Queen {
public:
	array<pair<int, int>, 8> posW;
	array<pair<int, int>, 8> posB;
	Texture texture[2];
	RectangleShape queenW[5];
	RectangleShape queenB[5];

	int Wqueens = 1;
	int Bqueens = 1;

	Queen();

	void GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	RectangleShape& getQueenW(pair<int, int>);

	RectangleShape& getQueenB(pair<int, int>);
};

#endif
