#ifndef KING_H
#define KING_H

#include "Figure.h"

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>

using namespace std;
using namespace sf;

class King : public Figure {
private:
	pair<int, int> posWhite = make_pair(0,3); // starting positions of white king
	pair<int, int> posBlack = make_pair(7,3); // starting positions of black king
	Texture texture[2];
	RectangleShape king[2];// [0] is white [1] is black

	bool WinDanger = 0, BinDanger = 0, hasWmoved = 0, hasBmoved = 0;

public:

	King();

	bool gethasWmoved();

	bool gethasBmoved();

	void sethasWmoved(bool value);

	void sethasBmoved(bool value);

	bool getWinDanger();

	bool getBinDanger();

	void setWinDanger(bool value);

	void setBinDanger(bool value);

	pair<int, int>& getPosW();

	pair<int, int>& getPosB();

	Texture& getWhiteTexture();

	Texture& getBlackTexture();

	void GetPossiblePosKingWhites(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetPossiblePosKingBlacks(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	RectangleShape& getWKingShapeAt(pair<int, int>);

	RectangleShape& getBKingShapeAt(pair<int, int>);

	RectangleShape& getKingShapeAt(int index);
};

#endif
