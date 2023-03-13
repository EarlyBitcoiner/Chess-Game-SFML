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
public:
	array<pair<int,int>,8> posW;
	array<pair<int, int>, 8> posB;
	Texture texture[2];
	RectangleShape rookW[2];
	RectangleShape rookB[2];

	Rook();

	void GetAvailablePosW(char board[8][8],Vector2i pos,vector<pair<int,int>>& AP);

	void GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	RectangleShape& getRookW(pair<int, int>);

	RectangleShape& getRookB(pair<int, int>);
};

#endif // !ROOK_H

