#include "King.h"

King::King() {

	this->texture[0].loadFromFile("Textures/w_king.png"); // white piece is first
	this->texture[1].loadFromFile("Textures/b_king.png"); // black piece is second

	this->texture[0].setSmooth(true);
	this->texture[1].setSmooth(true);

	this->king[0].setSize(Vector2f(90.f, 90.f));
	this->king[0].setTexture(&texture[0]);
	this->king[0].setPosition(Vector2f(posWhite.second * 100 + 5,posWhite.first * 100 + 5));

	this->king[1].setSize(Vector2f(90.f, 90.f));
	this->king[1].setTexture(&texture[1]);
	this->king[1].setPosition(Vector2f(posBlack.second * 100 + 5, posBlack.first * 100 + 5));
	
}

bool King::gethasWmoved() {
	return this->hasWmoved;
};

bool King::gethasBmoved() {
	return this->hasBmoved;
};

void King::sethasWmoved(bool value) {
	this->hasWmoved = value;
};

void King::sethasBmoved(bool value) {
	this->hasBmoved = value;
};

bool King::getWinDanger()
{
	return this->WinDanger;
}

bool King::getBinDanger()
{
	return this->BinDanger;
}

void King::setWinDanger(bool value)
{
	this->WinDanger = value;
}

void King::setBinDanger(bool value)
{
	this->BinDanger = value;
}

pair<int, int>& King::getPosW()
{
	return this->posWhite;
}

pair<int, int>& King::getPosB()
{
	return this->posBlack;
}

Texture& King::getWhiteTexture()
{
	return this->texture[0];
}

Texture& King::getBlackTexture()
{
	return this->texture[1];
}

void King::GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {
	AP.push_back(make_pair(pos.x, pos.y));

	if ( (board[pos.x + 1][pos.y] == '.' || board[pos.x + 1][pos.y] >= 97 && board[pos.x + 1][pos.y] <= 122 || board[pos.x + 1][pos.y] == '2') &&
		pos.x + 1 < 8)
		AP.push_back(make_pair(pos.x + 1, pos.y));

	if ( (board[pos.x + 1][pos.y - 1] == '.' || board[pos.x + 1][pos.y - 1] >= 97 && board[pos.x + 1][pos.y - 1] <= 122 || board[pos.x + 1][pos.y - 1] == '2') &&
		pos.y - 1 >= 0 && pos.x + 1 < 8)
		AP.push_back(make_pair(pos.x + 1, pos.y - 1));

	if ( (board[pos.x][pos.y - 1] == '.' || board[pos.x][pos.y - 1] >= 97 && board[pos.x][pos.y - 1] <= 122 || board[pos.x][pos.y - 1] == '2') &&
		pos.y - 1 >= 0)
		AP.push_back(make_pair(pos.x , pos.y - 1));

	if ( (board[pos.x - 1][pos.y - 1] == '.' || board[pos.x - 1][pos.y - 1] >= 97 && board[pos.x - 1][pos.y - 1] <= 122 || board[pos.x - 1][pos.y - 1] == '2') &&
		pos.x - 1 >= 0 && pos.y - 1 >= 0)
		AP.push_back(make_pair(pos.x - 1, pos.y - 1));

	if ( (board[pos.x - 1][pos.y] == '.' || board[pos.x - 1][pos.y] >= 97 && board[pos.x - 1][pos.y] <= 122 || board[pos.x - 1][pos.y] == '2') &&
		pos.x - 1 >= 0)
		AP.push_back(make_pair(pos.x - 1, pos.y));

	if ( (board[pos.x - 1][pos.y + 1] == '.' || board[pos.x - 1][pos.y + 1] >= 97 && board[pos.x - 1][pos.y + 1] <= 122 || board[pos.x - 1][pos.y + 1] == '2') &&
		pos.x - 1 >= 0 && pos.y + 1 < 8)
		AP.push_back(make_pair(pos.x - 1, pos.y + 1));

	if ( (board[pos.x][pos.y + 1] == '.' || board[pos.x][pos.y + 1] >= 97 && board[pos.x][pos.y + 1] <= 122 || board[pos.x][pos.y + 1] == '2') &&
		pos.y + 1 < 8)
		AP.push_back(make_pair(pos.x, pos.y + 1));

	if ( (board[pos.x + 1][pos.y + 1] == '.' || board[pos.x + 1][pos.y + 1] >= 97 && board[pos.x + 1][pos.y + 1] <= 122 || board[pos.x + 1][pos.y + 1] == '2') &&
		pos.x + 1 < 8 && pos.y + 1 < 8)
		AP.push_back(make_pair(pos.x + 1, pos.y + 1));

	if ( hasWmoved == 0 && board[pos.x][pos.y + 1] == '.' && 
		 board[pos.x][pos.y + 2] == '.' && 
		 board[pos.x][pos.y + 3] == '.' &&
		 board[pos.x][pos.y + 4] == 'R') {

		AP.push_back(make_pair(pos.x,pos.y + 2));

	}

	if (hasWmoved == 0 && board[pos.x][pos.y - 1] == '.' &&
		board[pos.x][pos.y - 2] == '.' &&
		board[pos.x][pos.y - 3] == 'R') {

		AP.push_back(make_pair(pos.x, pos.y - 2));

	}
};

void King::GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {
	AP.push_back(make_pair(pos.x, pos.y));

	if ((board[pos.x + 1][pos.y] == '.' || board[pos.x + 1][pos.y] >= 65 && board[pos.x + 1][pos.y] <= 90 || board[pos.x + 1][pos.y] == '1') &&
		pos.x + 1 < 8)
		AP.push_back(make_pair(pos.x + 1, pos.y));

	if ((board[pos.x + 1][pos.y - 1] == '.' || board[pos.x + 1][pos.y - 1] >= 65 && board[pos.x + 1][pos.y - 1] <= 90 || board[pos.x + 1][pos.y - 1] == '1') &&
		pos.y - 1 >= 0 && pos.x + 1 < 8)
		AP.push_back(make_pair(pos.x + 1, pos.y - 1));

	if ((board[pos.x][pos.y - 1] == '.' || board[pos.x][pos.y - 1] >= 65 && board[pos.x][pos.y - 1] <= 90 || board[pos.x][pos.y - 1] == '1') &&
		pos.y - 1 >= 0)
		AP.push_back(make_pair(pos.x, pos.y - 1));

	if ((board[pos.x - 1][pos.y - 1] == '.' || board[pos.x - 1][pos.y - 1] >= 65 && board[pos.x - 1][pos.y - 1] <= 90 || board[pos.x - 1][pos.y - 1] == '1') &&
		pos.x - 1 >= 0 && pos.y - 1 >= 0)
		AP.push_back(make_pair(pos.x - 1, pos.y - 1));

	if ((board[pos.x - 1][pos.y] == '.' || board[pos.x - 1][pos.y] >= 65 && board[pos.x - 1][pos.y] <= 90 || board[pos.x - 1][pos.y] == '1') &&
		pos.x - 1 >= 0)
		AP.push_back(make_pair(pos.x - 1, pos.y));

	if ((board[pos.x - 1][pos.y + 1] == '.' || board[pos.x - 1][pos.y + 1] >= 65 && board[pos.x - 1][pos.y + 1] <= 90 || board[pos.x - 1][pos.y + 1] == '1') &&
		pos.x - 1 >= 0 && pos.y + 1 < 8)
		AP.push_back(make_pair(pos.x - 1, pos.y + 1));

	if ((board[pos.x][pos.y + 1] == '.' || board[pos.x][pos.y + 1] >= 65 && board[pos.x][pos.y + 1] <= 90 || board[pos.x][pos.y + 1] == '1') &&
		pos.y + 1 < 8)
		AP.push_back(make_pair(pos.x, pos.y + 1));

	if ((board[pos.x + 1][pos.y + 1] == '.' || board[pos.x + 1][pos.y + 1] >= 65 && board[pos.x + 1][pos.y + 1] <= 90 || board[pos.x + 1][pos.y + 1] == '1') &&
		pos.x + 1 < 8 && pos.y + 1 < 8)
		AP.push_back(make_pair(pos.x + 1, pos.y + 1));

	if (hasBmoved == 0 && board[pos.x][pos.y + 1] == '.' &&
		board[pos.x][pos.y + 2] == '.' &&
		board[pos.x][pos.y + 3] == '.' &&
		board[pos.x][pos.y + 4] == 'r') {

		AP.push_back(make_pair(pos.x, pos.y + 2));

	}

	if (hasBmoved == 0 && board[pos.x][pos.y - 1] == '.' &&
		board[pos.x][pos.y - 2] == '.' &&
		board[pos.x][pos.y - 3] == 'r') {

		AP.push_back(make_pair(pos.x, pos.y - 2));

	}
};

RectangleShape& King::getKingWatPos(pair<int, int> pos) {

		if (posWhite == pos)
			return king[0];

}

RectangleShape& King::getKingBatPos(pair<int, int> pos) {

	if (posBlack == pos)
		return king[1];

}

RectangleShape& King::getKingAtIndex(int index)
{
	return this->king[index];
}
;