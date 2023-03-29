#include "Knight.h"

Knight::Knight() {

	this->posWhites[0] = (make_pair(0, 1)); this->posWhites[1] = (make_pair(0, 6));
	this->posBlacks[0] = (make_pair(7, 1)); this->posBlacks[1] = (make_pair(7, 6));

	this->texture[0].loadFromFile("Textures/w_knight.png"); // white piece is first
	this->texture[1].loadFromFile("Textures/b_knight.png"); // black piece is second

	knightW[0].setSize(Vector2f(90.f, 90.f));
	knightW[0].setTexture(&texture[0]);

	knightW[1] = knightW[0];

	knightB[0].setSize(Vector2f(90.f, 90.f));
	knightB[0].setTexture(&texture[1]);

	knightB[1] = knightB[0];

	for (size_t i = 0;i < 2;i++) {
		knightW[i].setPosition(Vector2f(posWhites[i].second * 100 + 5, posWhites[i].first * 100 + 5));
		knightB[i].setPosition(Vector2f(posBlacks[i].second * 100 + 5, posBlacks[i].first * 100 + 5));
	}


};

array<pair<int, int>, 8>& Knight::getPosW()
{
	return this->posWhites;
}

array<pair<int, int>, 8>& Knight::getPosB()
{
	return this->posBlacks;
}

Texture& Knight::getWhiteTexture()
{
	return this->texture[0];
}

Texture& Knight::getBlackTexture()
{
	return this->texture[1];
}

RectangleShape& Knight::getWKnightShapeAt(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posWhites[i] == pos)
			return knightW[i];
	}

}
RectangleShape& Knight::getWKnightShapeAt(int index)
{
	return this->knightW[index];
}
;

RectangleShape& Knight::getBKnightShapeAt(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posBlacks[i] == pos)
			return knightB[i];
	}

}
RectangleShape& Knight::getBKnightShapeAt(int index)
{
	return this->knightB[index];
}
;