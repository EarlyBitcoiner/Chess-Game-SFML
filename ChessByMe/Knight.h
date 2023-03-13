#ifndef KNIGHT_H
#define KNIGHT_H

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <array>

using namespace std;
using namespace sf;

class Knight {
public:
	array<pair<int, int>,8> posW;
	array<pair<int, int>,8> posB;
	Texture texture[2];
	RectangleShape knightW[2];
	RectangleShape knightB[2];
public:
	Knight();

	void GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	RectangleShape& getKnightW(pair<int, int>);

	RectangleShape& getKnightB(pair<int, int>);
};

#endif
