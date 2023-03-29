#ifndef QUEEN_H
#define QUEEN_H

#include "Figure.h"

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <array>

using namespace std;
using namespace sf;

class Queen : public Figure {
private:
	array<pair<int, int>, 8> posWhites;
	array<pair<int, int>, 8> posBlacks;
	Texture texture[2];
	RectangleShape queenW[8];
	RectangleShape queenB[8];

	int Wqueens = 1;
	int Bqueens = 1;

public:
	Queen();

	pair<int, int>& posWat(int index);

	pair<int, int>& posBat(int index);

	Texture& getWhiteTexture();

	Texture& getBlackTexture();

	array<pair<int, int>, 8>& getPosW();

	array<pair<int, int>, 8>& getPosB();

	void addWqueen();

	void addBqueen();

	int getWqueens();

	int getBqueens();

	RectangleShape& getWQueenShapeAt(pair<int, int>);

	RectangleShape* getWQueenShapeAt(int index);

	RectangleShape& getBQueenShapeAt(pair<int, int>);

	RectangleShape* getBQueenShapeAt(int index);

};

#endif
