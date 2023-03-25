#include "Knight.h"

Knight::Knight() {

	this->posW[0] = (make_pair(0, 1)); this->posW[1] = (make_pair(0, 6));
	this->posB[0] = (make_pair(7, 1)); this->posB[1] = (make_pair(7, 6));

	this->texture[0].loadFromFile("Textures/w_knight.png"); // white piece is first
	this->texture[1].loadFromFile("Textures/b_knight.png"); // black piece is second

	knightW[0].setSize(Vector2f(90.f, 90.f));
	knightW[0].setTexture(&texture[0]);

	knightW[1] = knightW[0];

	knightB[0].setSize(Vector2f(90.f, 90.f));
	knightB[0].setTexture(&texture[1]);

	knightB[1] = knightB[0];

	for (size_t i = 0;i < 2;i++) {
		knightW[i].setPosition(Vector2f(posW[i].second * 100 + 5, posW[i].first * 100 + 5));
		knightB[i].setPosition(Vector2f(posB[i].second * 100 + 5, posB[i].first * 100 + 5));
	}


};

void Knight::GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {
	AP.push_back(make_pair(pos.x, pos.y));

	if(pos.x + 2 < 8 && pos.y + 1 < 8 && 
		(board[pos.x + 2][pos.y + 1] == '.' || 
		(board[pos.x + 2][pos.y + 1] >= 97 && board[pos.x + 2][pos.y + 1] <= 122) ) ||
		 board[pos.x + 2][pos.y + 1] == '2') {

		AP.push_back(make_pair(pos.x + 2, pos.y + 1));
	}

	if (pos.x + 2 < 8 && pos.y - 1 >= 0 &&
		(board[pos.x + 2][pos.y - 1] == '.' ||
		(board[pos.x + 2][pos.y - 1] >= 97 && board[pos.x + 2][pos.y - 1] <= 122) ) ||
		 board[pos.x + 2][pos.y - 1] == '2') {
	
		AP.push_back(make_pair(pos.x + 2, pos.y - 1));
	}

	if (pos.x + 1 < 8 && pos.y - 2 >= 0 &&
		(board[pos.x + 1][pos.y - 2] == '.' ||
		(board[pos.x + 1][pos.y - 2] >= 97 && board[pos.x + 1][pos.y - 2] <= 122) ) ||
		 board[pos.x + 1][pos.y - 2] == '2') {

		AP.push_back(make_pair(pos.x + 1, pos.y - 2));
	}

	if (pos.x - 1 >= 0 && pos.y - 2 >= 0 &&
		(board[pos.x - 1][pos.y - 2] == '.' ||
		(board[pos.x - 1][pos.y - 2] >= 97 && board[pos.x - 1][pos.y - 2] <= 122) ) ||
		 board[pos.x - 1][pos.y - 2] == '2') {

		AP.push_back(make_pair(pos.x - 1, pos.y - 2));
	}

	if (pos.x - 2 >= 0 && pos.y - 1 >= 0 &&
		(board[pos.x - 2][pos.y - 1] == '.' ||
		(board[pos.x - 2][pos.y - 1] >= 97 && board[pos.x - 2][pos.y - 1] <= 122) ) ||
		 board[pos.x - 2][pos.y - 1] == '2') {

		AP.push_back(make_pair(pos.x - 2, pos.y - 1));
	}

	if (pos.x - 2 >= 0 && pos.y + 1 < 8 &&
		(board[pos.x - 2][pos.y + 1] == '.' ||
		(board[pos.x - 2][pos.y + 1] >= 97 && board[pos.x - 2][pos.y + 1] <= 122) ) ||
		 board[pos.x - 2][pos.y + 1] == '2') {

		AP.push_back(make_pair(pos.x - 2, pos.y + 1));
	}

	if (pos.x - 1 >= 0 && pos.y + 2 < 8 &&
		(board[pos.x - 1][pos.y + 2] == '.' ||
		(board[pos.x - 1][pos.y + 2] >= 97 && board[pos.x - 1][pos.y + 2] <= 122) ) ||
		 board[pos.x - 1][pos.y + 2] == '2') {

		AP.push_back(make_pair(pos.x -1, pos.y + 2));
	}

	if (pos.x + 1 < 8 && pos.y + 2 < 8 &&
		(board[pos.x + 1][pos.y + 2] == '.' ||
		(board[pos.x + 1][pos.y + 2] >= 97 && board[pos.x + 1][pos.y + 2] <= 122) ) ||
		 board[pos.x + 1][pos.y + 2] == '2') {

		AP.push_back(make_pair(pos.x + 1, pos.y + 2));
	}
};

void Knight::GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {
	AP.push_back(make_pair(pos.x, pos.y));

	if (pos.x + 2 < 8 && pos.y + 1 < 8 &&
		(board[pos.x + 2][pos.y + 1] == '.' ||
		(board[pos.x + 2][pos.y + 1] >= 65 && board[pos.x + 2][pos.y + 1] <= 90) ) ||
		 board[pos.x + 2][pos.y + 1] == '1') {

		AP.push_back(make_pair(pos.x + 2, pos.y + 1));
	}

	if (pos.x + 2 < 8 && pos.y - 1 >= 0 &&
		(board[pos.x + 2][pos.y - 1] == '.' ||
		(board[pos.x + 2][pos.y - 1] >= 65 && board[pos.x + 2][pos.y - 1] <= 90) ) ||
		 board[pos.x + 2][pos.y - 1] == '1') {

		AP.push_back(make_pair(pos.x + 2, pos.y - 1));
	}

	if (pos.x + 1 < 8 && pos.y - 2 >= 0 &&
		(board[pos.x + 1][pos.y - 2] == '.' ||
		(board[pos.x + 1][pos.y - 2] >= 65 && board[pos.x + 1][pos.y - 2] <= 90) ) ||
		 board[pos.x + 1][pos.y - 2] == '1') {

		AP.push_back(make_pair(pos.x + 1, pos.y - 2));
	}

	if (pos.x - 1 >= 0 && pos.y - 2 >= 0 &&
		(board[pos.x - 1][pos.y - 2] == '.' ||
		(board[pos.x - 1][pos.y - 2] >= 65 && board[pos.x - 1][pos.y - 2] <= 90) ) ||
		 board[pos.x - 1][pos.y - 2] == '1') {

		AP.push_back(make_pair(pos.x - 1, pos.y - 2));
	}

	if (pos.x - 2 >= 0 && pos.y - 1 >= 0 &&
		(board[pos.x - 2][pos.y - 1] == '.' ||
		(board[pos.x - 2][pos.y - 1] >= 65 && board[pos.x - 2][pos.y - 1] <= 90) ) ||
		 board[pos.x - 2][pos.y - 1] == '1') {

		AP.push_back(make_pair(pos.x - 2, pos.y - 1));
	}

	if (pos.x - 2 >= 0 && pos.y + 1 < 8 &&
		(board[pos.x - 2][pos.y + 1] == '.' ||
		(board[pos.x - 2][pos.y + 1] >= 65 && board[pos.x - 2][pos.y + 1] <= 90) ) ||
		 board[pos.x - 2][pos.y + 1] == '1') {

		AP.push_back(make_pair(pos.x - 2, pos.y + 1));
	}

	if (pos.x - 1 >= 0 && pos.y + 2 < 8 &&
		(board[pos.x - 1][pos.y + 2] == '.' ||
		(board[pos.x - 1][pos.y + 2] >= 65 && board[pos.x - 1][pos.y + 2] <= 90) ) ||
		 board[pos.x - 1][pos.y + 2] == '1') {

		AP.push_back(make_pair(pos.x - 1, pos.y + 2));
	}

	if (pos.x + 1 < 8 && pos.y + 2 < 8 &&
		(board[pos.x + 1][pos.y + 2] == '.' ||
		(board[pos.x + 1][pos.y + 2] >= 65 && board[pos.x + 1][pos.y + 2] <= 90) ) ||
		 board[pos.x + 1][pos.y + 2] == '1') {

		AP.push_back(make_pair(pos.x + 1, pos.y + 2));
	}
};

array<pair<int, int>, 8>& Knight::getPosW()
{
	return this->posW;
}

array<pair<int, int>, 8>& Knight::getPosB()
{
	return this->posB;
}

Texture& Knight::getWhiteTexture()
{
	return this->texture[0];
}

Texture& Knight::getBlackTexture()
{
	return this->texture[1];
}

RectangleShape& Knight::getKnightWatPos(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posW[i] == pos)
			return knightW[i];
	}

}
RectangleShape& Knight::getKnightWatIndex(int index)
{
	return this->knightW[index];
}
;

RectangleShape& Knight::getKnightBatPos(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posB[i] == pos)
			return knightB[i];
	}

}
RectangleShape& Knight::getKnightBatIndex(int index)
{
	return this->knightB[index];
}
;