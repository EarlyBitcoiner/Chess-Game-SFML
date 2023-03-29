#include "Pawn.h"

Pawn::Pawn() {
	for (size_t i = 0;i < 8;i++) {
		posWhites[i] = (make_pair(1, i));
		posBlacks[i] = (make_pair(6,i));
	}

	texture[0].loadFromFile("Textures/w_pawn.png"); // white piece is first
	texture[1].loadFromFile("Textures/b_pawn.png"); // black piece is second

	for (size_t i = 0;i < 8;i++) {
		pawnW[i].setTexture(&texture[0]);
		pawnW[i].setSize(Vector2f(90.f, 90.f));
		pawnW[i].setPosition(Vector2f(posWhites[i].second * 100 + 5, posWhites[i].first * 100 + 5));
	}

	for (size_t i = 0;i < 8;i++) {
		pawnB[i].setTexture(&texture[1]);
		pawnB[i].setSize(Vector2f(90.f, 90.f));
		pawnB[i].setPosition(Vector2f(posBlacks[i].second * 100 + 5, posBlacks[i].first * 100 + 5));
	}
	


}

pair<int, int>& Pawn::getEnPassantPawnPos()
{
	return this->enPassantPawnPos;
}

void Pawn::setEnPassantPawnPos( pair<int,int> pos)
{
	this->enPassantPawnPos = pos;
}

bool Pawn::getEnPassant()
{
	return this->enPassant;
}

void Pawn::raiseEnPassant()
{
	this->enPassant = 1;
}

void Pawn::lowerEnPassant()
{
	this->enPassant = 0;
}

array<pair<int, int>, 8>& Pawn::getPosW()
{
	return this->posWhites;
}

array<pair<int, int>, 8>& Pawn::getPosB()
{
	return this->posBlacks;
}

Texture& Pawn::getWhiteTexture()
{
	return this->texture[0];
}

Texture& Pawn::getBlackTexture()
{
	return this->texture[1];
}

void Pawn::GetPossiblePosPawnWhites(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {
	
	Figure::GetPossiblePosPawnWhites(board, pos, AP);

	// checking if en passant is possible.
	if (pos.y + 1 < 8 && board[pos.x][pos.y + 1] == 'p' && make_pair(pos.x, pos.y + 1) == this->enPassantPawnPos && this->enPassant)
		AP.push_back(make_pair(pos.x + 1, pos.y + 1));

	if (pos.y - 1 >= 0 && board[pos.x][pos.y - 1] == 'p' && make_pair(pos.x, pos.y - 1) == this->enPassantPawnPos && this->enPassant)
		AP.push_back(make_pair(pos.x + 1, pos.y - 1));
};

void Pawn::GetPossiblePosPawnBlacks(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {
	
	Figure::GetPossiblePosPawnBlacks(board, pos, AP);

	// checking if en passant is possible.
	if (pos.y + 1 < 8 && board[pos.x][pos.y + 1] == 'P' && make_pair(pos.x, pos.y + 1) == this->enPassantPawnPos && this->enPassant)
		AP.push_back(make_pair(pos.x - 1, pos.y + 1));

	if (pos.y - 1 >= 0 && board[pos.x][pos.y - 1] == 'P' && make_pair(pos.x, pos.y - 1) == this->enPassantPawnPos && this->enPassant)
		AP.push_back(make_pair(pos.x - 1, pos.y - 1));
};

RectangleShape& Pawn::getWPawnShapeAt(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posWhites[i] == pos)
			return pawnW[i];
	}

}

RectangleShape& Pawn::getWPawnShapeAt(int index)
{
	return this->pawnW[index];
}

RectangleShape& Pawn::getBPawnShapeAt(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posBlacks[i] == pos)
			return pawnB[i];
	}

}

RectangleShape& Pawn::getBPawnShapeAt(int index)
{
	return this->pawnB[index];
}