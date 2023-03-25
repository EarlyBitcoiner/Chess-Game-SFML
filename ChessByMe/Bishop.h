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
private:

	array<pair<int, int>,8> posW;
	array<pair<int, int>,8> posB;
	Texture texture[2];
	RectangleShape bishopW[2];
	RectangleShape bishopB[2];

public:

	Bishop();

	array<pair<int, int>, 8>& getPosW();

	array<pair<int, int>, 8>& getPosB();

	Texture& getWhiteTexture();

	Texture& getBlackTexture();

	void GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	RectangleShape& getBishopWatPos(pair<int, int>);

	RectangleShape& getBishopWatIndex(int index);

	RectangleShape& getBishopBatPos(pair<int, int>);

	RectangleShape& getBishopBatIndex(int index);
};

#endif
