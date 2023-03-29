#include "Rook.h"

Rook::Rook() {
	
	this->posWhites[0] = (make_pair(0, 0)); this->posWhites[1] = (make_pair(0, 7));
	this->posBlacks[0] = (make_pair(7, 0)); this->posBlacks[1] = (make_pair(7, 7));

	texture[0].loadFromFile("Textures/w_rook.png"); // white piece is first
	texture[1].loadFromFile("Textures/b_rook.png"); // black piece is second

	rookW[0].setSize(Vector2f(90.f, 90.f));
	rookW[0].setTexture(&texture[0]);

	rookW[1] = rookW[0];
	
	rookB[0].setSize(Vector2f(90.f, 90.f));
	rookB[0].setTexture(&texture[1]);

	rookB[1] = rookB[0];

	for (size_t i = 0;i < 2;i++) {
		rookW[i].setPosition(Vector2f(posWhites[i].second * 100 + 5, posWhites[i].first * 100 + 5));
		rookB[i].setPosition(Vector2f(posBlacks[i].second * 100 + 5, posBlacks[i].first * 100 + 5));
	}
}

array<pair<int, int>, 8>& Rook::getPosW()
{
	return this->posWhites;

}

array<pair<int, int>, 8>& Rook::getPosB()
{
	return this->posBlacks;
}

Texture& Rook::getWhiteTexture()
{
	return this->texture[0];
}

Texture& Rook::getBlackTexture()
{
	return this->texture[1];
}

RectangleShape& Rook::getWRookShapeAt(pair<int,int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posWhites[i] == pos)
			return rookW[i];
	}

}

RectangleShape& Rook::getWRookShapeAt(int index)
{
	return this->rookW[index];
}

RectangleShape& Rook::getBRookShapeAt(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posBlacks[i] == pos)
			return rookB[i];
	}

}

RectangleShape& Rook::getBRookShapeAt(int index)
{
	return this->rookB[index];
}