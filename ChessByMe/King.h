#ifndef KING_H
#define KING_H

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>

using namespace std;
using namespace sf;

class King {
public:
	pair<int, int> posW = make_pair(0,3); // starting positions of white king
	pair<int, int> posB = make_pair(7,3); // starting positions of black king
	Texture texture[2];
	RectangleShape king[2];// [0] is white [1] is black
	bool inDangerW = 0, inDangerB = 0, hasMovedW = 0, hasMovedB = 0;

	King();

	void GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	RectangleShape& getKingW(pair<int, int>);

	RectangleShape& getKingB(pair<int, int>);
};

#endif
