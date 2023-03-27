#ifndef ROOK_H
#define ROOK_H

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <array>

using namespace std;
using namespace sf;

class Rook {
private:

	array<pair<int, int>, 8> posWhites;
	array<pair<int, int>, 8> posBlacks;
	Texture texture[2];
	RectangleShape rookW[2];
	RectangleShape rookB[2];

public:

	Rook();

	array<pair<int, int>, 8>& getPosW();

	array<pair<int, int>, 8>& getPosB();

	Texture& getWhiteTexture();

	Texture& getBlackTexture();

	void GetAvailablePosW(char board[8][8],Vector2i pos,vector<pair<int,int>>& AP);

	void GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	RectangleShape& getRookWatPos(pair<int, int>);

	RectangleShape& getRookWatIndex(int index);

	RectangleShape& getRookBatPos(pair<int, int>);

	RectangleShape& getRookBatIndex(int index);
};

#endif // !ROOK_H

