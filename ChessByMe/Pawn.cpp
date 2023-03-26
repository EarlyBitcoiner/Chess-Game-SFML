#include "Pawn.h"

Pawn::Pawn() {
	for (size_t i = 0;i < 8;i++) {
		posW[i] = (make_pair(1, i));
		posB[i] = (make_pair(6,i));
	}

	texture[0].loadFromFile("Textures/w_pawn.png"); // white piece is first
	texture[1].loadFromFile("Textures/b_pawn.png"); // black piece is second

	for (size_t i = 0;i < 8;i++) {
		pawnW[i].setTexture(&texture[0]);
		pawnW[i].setSize(Vector2f(90.f, 90.f));
		pawnW[i].setPosition(Vector2f(posW[i].second * 100 + 5, posW[i].first * 100 + 5));
	}

	for (size_t i = 0;i < 8;i++) {
		pawnB[i].setTexture(&texture[1]);
		pawnB[i].setSize(Vector2f(90.f, 90.f));
		pawnB[i].setPosition(Vector2f(posB[i].second * 100 + 5, posB[i].first * 100 + 5));
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
	return this->posW;
}

array<pair<int, int>, 8>& Pawn::getPosB()
{
	return this->posB;
}

Texture& Pawn::getWhiteTexture()
{
	return this->texture[0];
}

Texture& Pawn::getBlackTexture()
{
	return this->texture[1];
}

void Pawn::GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {
	AP.push_back(make_pair(pos.x, pos.y));

	if (pos.x == 1 && board[pos.x + 2][pos.y] == '.')
		AP.push_back(make_pair(pos.x + 2, pos.y));

	if (pos.x + 1 < 8 && board[pos.x + 1][pos.y] == '.')
		AP.push_back(make_pair(pos.x + 1, pos.y));

	if (pos.x + 1 >= 0 && pos.y + 1 >= 0 && (board[pos.x + 1][pos.y + 1] >= 97 && board[pos.x + 1][pos.y + 1] <= 122 || board[pos.x + 1][pos.y + 1] == '2'))
		AP.push_back(make_pair(pos.x + 1, pos.y + 1));

	if (pos.x + 1 >= 0 && pos.y - 1 >= 0 && (board[pos.x + 1][pos.y - 1] >= 97 && board[pos.x + 1][pos.y - 1] <= 122 || board[pos.x + 1][pos.y - 1] == '2'))
		AP.push_back(make_pair(pos.x + 1, pos.y - 1));

	// checking if en passant is possible.
	if (pos.y + 1 < 8 && board[pos.x][pos.y + 1] == 'p' && make_pair(pos.x, pos.y + 1) == this->enPassantPawnPos && this->enPassant)
		AP.push_back(make_pair(pos.x + 1, pos.y + 1));

	if (pos.y - 1 >= 0 && board[pos.x][pos.y - 1] == 'p' && make_pair(pos.x, pos.y - 1) == this->enPassantPawnPos && this->enPassant)
		AP.push_back(make_pair(pos.x + 1, pos.y - 1));
};

void Pawn::GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {
	AP.push_back(make_pair(pos.x, pos.y));

	if (pos.x == 6 && board[pos.x - 2][pos.y]== '.')
		AP.push_back(make_pair(pos.x - 2, pos.y));

	if (pos.x - 1 >= 0 && board[pos.x - 1][pos.y] == '.')
		AP.push_back(make_pair(pos.x - 1, pos.y));

	if (pos.x - 1 >= 0 && pos.y - 1 >= 0 && (board[pos.x - 1][pos.y - 1] >= 65 && board[pos.x - 1][pos.y - 1] <= 90 || board[pos.x - 1][pos.y - 1] == '1'))
		AP.push_back(make_pair(pos.x - 1, pos.y - 1));

	if (pos.x - 1 >= 0 && pos.y + 1 >= 0 && (board[pos.x - 1][pos.y + 1] >= 65 && board[pos.x - 1][pos.y + 1] <= 90 || board[pos.x - 1][pos.y + 1] == '1'))
		AP.push_back(make_pair(pos.x - 1, pos.y + 1));

	// checking if en passant is possible.
	if (pos.y + 1 < 8 && board[pos.x][pos.y + 1] == 'P' && make_pair(pos.x, pos.y + 1) == this->enPassantPawnPos && this->enPassant)
		AP.push_back(make_pair(pos.x - 1, pos.y + 1));

	if (pos.y - 1 >= 0 && board[pos.x][pos.y - 1] == 'P' && make_pair(pos.x, pos.y - 1) == this->enPassantPawnPos && this->enPassant)
		AP.push_back(make_pair(pos.x - 1, pos.y - 1));
};

RectangleShape& Pawn::getPawnWatPos(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posW[i] == pos)
			return pawnW[i];
	}

}

RectangleShape& Pawn::getPawnWatIndex(int index)
{
	return this->pawnW[index];
}

RectangleShape& Pawn::getPawnBatPos(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posB[i] == pos)
			return pawnB[i];
	}

}

RectangleShape& Pawn::getPawnBatIndex(int index)
{
	return this->pawnB[index];
}