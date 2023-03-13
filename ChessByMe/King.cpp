#include "King.h"

King::King() {

	this->texture[0].loadFromFile("Textures/w_king.png"); // white piece is first
	this->texture[1].loadFromFile("Textures/b_king.png"); // black piece is second

	this->king[0].setSize(Vector2f(90.f, 90.f));
	this->king[0].setTexture(&texture[0]);
	this->king[0].setPosition(Vector2f(posW.second * 100 + 5,posW.first * 100 + 5));

	this->king[1].setSize(Vector2f(90.f, 90.f));
	this->king[1].setTexture(&texture[1]);
	this->king[1].setPosition(Vector2f(posB.second * 100 + 5, posB.first * 100 + 5));
	
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

	if ( hasMovedW == 0 && board[pos.x][pos.y + 1] == '.' && 
		 board[pos.x][pos.y + 2] == '.' && 
		 board[pos.x][pos.y + 3] == '.' &&
		 board[pos.x][pos.y + 4] == 'R') {

		AP.push_back(make_pair(pos.x,pos.y + 2));

	}

	if (hasMovedW == 0 && board[pos.x][pos.y - 1] == '.' &&
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

	if (hasMovedB == 0 && board[pos.x][pos.y + 1] == '.' &&
		board[pos.x][pos.y + 2] == '.' &&
		board[pos.x][pos.y + 3] == '.' &&
		board[pos.x][pos.y + 4] == 'r') {

		AP.push_back(make_pair(pos.x, pos.y + 2));

	}

	if (hasMovedB == 0 && board[pos.x][pos.y - 1] == '.' &&
		board[pos.x][pos.y - 2] == '.' &&
		board[pos.x][pos.y - 3] == 'r') {

		AP.push_back(make_pair(pos.x, pos.y - 2));

	}
};

RectangleShape& King::getKingW(pair<int, int> pos) {

		if (posW == pos)
			return king[0];

};

RectangleShape& King::getKingB(pair<int, int> pos) {

	if (posB == pos)
		return king[1];

};