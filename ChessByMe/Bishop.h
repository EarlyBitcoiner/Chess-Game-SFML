#ifndef BISHOP_H
#define BISHOP_H

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <array>

using namespace std;
using namespace sf;

class Bishop {
public:
	array<pair<int, int>,8> posW;
	array<pair<int, int>,8> posB;
	Texture texture[2];
	RectangleShape bishopW[2];
	RectangleShape bishopB[2];

	Bishop();

	void GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	RectangleShape& getBishopW(pair<int, int>);

	RectangleShape& getBishopB(pair<int, int>);
};

#endif
