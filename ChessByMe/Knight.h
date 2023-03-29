#ifndef KNIGHT_H
#define KNIGHT_H

#include "Figure.h"

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <array>

using namespace std;
using namespace sf;

class Knight : public Figure {
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

	RectangleShape& getWKnightShapeAt(pair<int, int>);

	RectangleShape& getWKnightShapeAt(int index);

	RectangleShape& getBKnightShapeAt(pair<int, int>);

	RectangleShape& getBKnightShapeAt(int index);

};

#endif
