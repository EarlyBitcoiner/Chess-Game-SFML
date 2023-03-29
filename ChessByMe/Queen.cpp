#include "Queen.h"

Queen::Queen() {
	this->posWhites[0] = make_pair(0, 4);
	this->posBlacks[0] = make_pair(7, 4);

	this->texture[0].loadFromFile("Textures/w_queen.png"); // white piece is first
	this->texture[1].loadFromFile("Textures/b_queen.png"); // black piece is second

	this->queenW[0].setSize(Vector2f(90.f, 90.f));
	this->queenW[0].setTexture(&texture[0]);
	this->queenW[0].setPosition(Vector2f(posWhites[0].second * 100 + 5, posWhites[0].first * 100 + 5));

	this->queenB[0].setSize(Vector2f(90.f, 90.f));
	this->queenB[0].setTexture(&texture[1]);
	this->queenB[0].setPosition(Vector2f(posBlacks[0].second * 100 + 5, posBlacks[0].first * 100 + 5));

}

pair<int, int>& Queen::posWat(int index) { return this->posWhites[index]; };

pair<int, int>& Queen::posBat(int index) { return this->posBlacks[index]; };

Texture& Queen::getWhiteTexture() { return this->texture[0]; };

Texture& Queen::getBlackTexture() { return this->texture[1]; };

array<pair<int, int>, 8>& Queen::getPosW() { return this->posWhites; };

array<pair<int, int>, 8>& Queen::getPosB() { return this->posBlacks; };

void Queen::addWqueen() { this->Wqueens++; };

void Queen::addBqueen() { this->Bqueens++; };

int Queen::getWqueens() { return this->Wqueens; };

int Queen::getBqueens() { return this->Bqueens; };

RectangleShape& Queen::getWQueenShapeAt(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posWhites[i] == pos)
			return queenW[i];
	}
	
};

RectangleShape* Queen::getWQueenShapeAt(int index) {
	return &this->queenW[index];
};

RectangleShape& Queen::getBQueenShapeAt(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posBlacks[i] == pos)
			return queenB[i];
	}

};

RectangleShape* Queen::getBQueenShapeAt(int index) {
	return &this->queenB[index];
};