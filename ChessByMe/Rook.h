#ifndef ROOK_H
#define ROOK_H

#include "Figure.h"

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <array>

using namespace std;
using namespace sf;

class Rook : public Figure {
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

	RectangleShape& getWRookShapeAt(pair<int, int>);

	RectangleShape& getWRookShapeAt(int index);

	RectangleShape& getBRookShapeAt(pair<int, int>);

	RectangleShape& getBRookShapeAt(int index);
};

#endif // !ROOK_H

