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
private:

	array<pair<int, int>, 8> posWhites;
	array<pair<int, int>, 8> posBlacks;
	Texture texture[2];
	RectangleShape knightW[2];
	RectangleShape knightB[2];

public:
	Knight();

	array<pair<int, int>, 8>& getPosW();

	array<pair<int, int>, 8>& getPosB();

	Texture& getWhiteTexture();

	Texture& getBlackTexture();

	void GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	RectangleShape& getKnightWatPos(pair<int, int>);

	RectangleShape& getKnightWatIndex(int index);

	RectangleShape& getKnightBatPos(pair<int, int>);

	RectangleShape& getKnightBatIndex(int index);

};

#endif
