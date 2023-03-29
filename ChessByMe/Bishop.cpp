#include "Bishop.h"

Bishop::Bishop() {

	this->posWhites[0] = (make_pair(0, 2)); this->posWhites[1] = (make_pair(0, 5));
	this->posBlacks[0] = (make_pair(7, 2)); this->posBlacks[1] = (make_pair(7, 5));

	this->texture[0].loadFromFile("Textures/w_bishop.png"); // white piece is first (put white texture here)
	this->texture[1].loadFromFile("Textures/b_bishop.png"); // black piece is second (put black texture here)

	bishopW[0].setSize(Vector2f(90.f, 90.f));
	bishopW[0].setTexture(&texture[0]);

	bishopW[1] = bishopW[0];

	bishopB[0].setSize(Vector2f(90.f, 90.f));
	bishopB[0].setTexture(&texture[1]);

	bishopB[1] = bishopB[0];

	for (size_t i = 0;i < 2;i++) {
		bishopW[i].setPosition(Vector2f(posWhites[i].second * 100 + 5, posWhites[i].first * 100 + 5));
		bishopB[i].setPosition(Vector2f(posBlacks[i].second * 100 + 5, posBlacks[i].first * 100 + 5));
	}

}

array<pair<int, int>, 8>& Bishop::getPosW()
{
	return this->posWhites;
}

array<pair<int, int>, 8>& Bishop::getPosB()
{
	return this->posBlacks;
}

Texture& Bishop::getWhiteTexture()
{
	return this->texture[0];
}

Texture& Bishop::getBlackTexture()
{
	return this->texture[1];
}

RectangleShape& Bishop::getWBishopShapeAt(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posWhites[i] == pos)
			return bishopW[i];
	}

}

RectangleShape& Bishop::getWBishopShapeAt(int index)
{
	return this->bishopW[index];
}

RectangleShape& Bishop::getBBishopShapeAt(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posBlacks[i] == pos)
			return bishopB[i];
	}

}

RectangleShape& Bishop::getBBishopShapeAt(int index)
{
	return this->bishopB[index];
}
