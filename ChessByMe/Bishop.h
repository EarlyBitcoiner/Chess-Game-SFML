#ifndef BISHOP_H
#define BISHOP_H

#include "Figure.h"

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <array>

using namespace std;
using namespace sf;

class Bishop : public Figure {
private:

	array<pair<int, int>,8> posWhites;
	array<pair<int, int>,8> posBlacks;
	Texture texture[2];
	RectangleShape bishopW[2];
	RectangleShape bishopB[2];

public:

	Bishop();

	array<pair<int, int>, 8>& getPosW();

	array<pair<int, int>, 8>& getPosB();

	Texture& getWhiteTexture();

	Texture& getBlackTexture();

	RectangleShape& getWBishopShapeAt(pair<int, int>);

	RectangleShape& getWBishopShapeAt(int index);

	RectangleShape& getBBishopShapeAt(pair<int, int>);

	RectangleShape& getBBishopShapeAt(int index);
};

#endif
