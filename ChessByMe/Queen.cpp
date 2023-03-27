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

void Queen::GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {

	AP.push_back(make_pair(pos.x, pos.y));

	for (int r = pos.x - 1;r >= 0;r--) {

		if (board[r][pos.y] == '.')
			AP.push_back(make_pair(r, pos.y));
		else if (board[r][pos.y] >= 97 && board[r][pos.y] <= 122) {
			AP.push_back(make_pair(r, pos.y));
			break;
		}
		else if (board[r][pos.y] >= 65 && board[r][pos.y] <= 90 || board[r][pos.y] == '1') {
			break;
		}
		else if (board[r][pos.y] == '2') {
			AP.push_back(make_pair(r, pos.y));
			break;
		}
	}

	for (int r = pos.x + 1;r <= 8;r++) {

		if (board[r][pos.y] == '.')
			AP.push_back(make_pair(r, pos.y));
		else if (board[r][pos.y] >= 97 && board[r][pos.y] <= 122) {
			AP.push_back(make_pair(r, pos.y));
			break;
		}
		else if (board[r][pos.y] >= 65 && board[r][pos.y] <= 90 || board[r][pos.y] == '1') {
			break;
		}
		else if (board[r][pos.y] == '2') {
			AP.push_back(make_pair(r, pos.y));
			break;
		}

	}

	for (int c = pos.y - 1;c >= 0;c--) {

		if (board[pos.x][c] == '.')
			AP.push_back(make_pair(pos.x, c));
		else if (board[pos.x][c] >= 97 && board[pos.x][c] <= 122) {
			AP.push_back(make_pair(pos.x, c));
			break;
		}
		else if (board[pos.x][c] >= 65 && board[pos.x][c] <= 90 || board[pos.x][c] == '1') {
			break;
		}
		else if (board[pos.x][c] == '2') {
			AP.push_back(make_pair(pos.x, c));
			break;
		}
	}

	for (int c = pos.y + 1;c <= 8;c++) {

		if (board[pos.x][c] == '.')
			AP.push_back(make_pair(pos.x, c));
		else if (board[pos.x][c] >= 97 && board[pos.x][c] <= 122) {
			AP.push_back(make_pair(pos.x, c));
			break;
		}
		else if (board[pos.x][c] >= 65 && board[pos.x][c] <= 90 || board[pos.x][c] == '1') {
			break;
		}
		else if (board[pos.x][c] == '2') {
			AP.push_back(make_pair(pos.x, c));
			break;
		}
	}


	for (int i = 1;i < 8;i++) {

		if (board[pos.x + i][pos.y + i] == '.' && pos.x + i < 8 && pos.y + i < 8) {
			AP.push_back(make_pair(pos.x + i, pos.y + i));
		}
		else if (pos.x + i < 8 && pos.y + i < 8 && board[pos.x + i][pos.y + i] >= 97 && board[pos.x + i][pos.y + i] <= 122) {
			AP.push_back(make_pair(pos.x + i, pos.y + i));
			break;
		}
		else if (pos.x + i < 8 && pos.y + i < 8 && board[pos.x + i][pos.y + i] >= 65 && board[pos.x + i][pos.y + i] <= 90 || board[pos.x + i][pos.y + i] == '1') {
			break;
		}
		else if (pos.x + i < 8 && pos.y + i < 8 && board[pos.x + i][pos.y + i] == '2') {
			AP.push_back(make_pair(pos.x + i, pos.y + i));
			break;
		}
		else if (pos.x + i >= 8 || pos.y + i >= 8) {
			break;
		}
	

	}

	for (int i = 1;i < 8;i++) {

		if (board[pos.x + i][pos.y - i] == '.' && pos.x + i < 8 && pos.y - i >= 0) {
			AP.push_back(make_pair(pos.x + i, pos.y - i));
		}
		else if (pos.x + i < 8 && pos.y - i >= 0 && board[pos.x + i][pos.y - i] >= 97 && board[pos.x + i][pos.y - i] <= 122) {
			AP.push_back(make_pair(pos.x + i, pos.y - i));
			break;
		}
		else if (pos.x + i < 8 && pos.y - i >= 0 && board[pos.x + i][pos.y - i] >= 65 && board[pos.x + i][pos.y - i] <= 90 || board[pos.x + i][pos.y - i] == '1') {
			break;
		}
		else if (pos.x + i < 8 && pos.y - i >= 0 && board[pos.x + i][pos.y - i] == '2') {
			AP.push_back(make_pair(pos.x + i, pos.y - i));
			break;
		}
		else if (pos.x + i >= 8 || pos.y - i < 0) {
			break;
		}
	}

	for (int i = 1;i < 8;i++) {

		if (board[pos.x - i][pos.y - i] == '.' && pos.x - i >= 0 && pos.y - i >= 0) {
			AP.push_back(make_pair(pos.x - i, pos.y - i));
		}
		else if (pos.x - i >= 0 && pos.y - i >= 0 && board[pos.x - i][pos.y - i] >= 97 && board[pos.x - i][pos.y - i] <= 122) {
			AP.push_back(make_pair(pos.x - i, pos.y - i));
			break;
		}
		else if (pos.x - i >= 0 && pos.y - i >= 0 && board[pos.x - i][pos.y - i] >= 65 && board[pos.x - i][pos.y - i] <= 90 || board[pos.x - i][pos.y - i] == '1') {
			break;
		}
		else if (pos.x - i >= 0 && pos.y - i >= 0 && board[pos.x - i][pos.y - i] == '2') {
			AP.push_back(make_pair(pos.x - i, pos.y - i));
			break;
		}
		else if (pos.x - i < 0 || pos.y - i < 0) {
			break;
		}

	}

	for (int i = 1;i < 8;i++) {

		if (board[pos.x - i][pos.y + i] == '.' && pos.x - i >= 0 && pos.y + i < 8) {
			AP.push_back(make_pair(pos.x - i, pos.y + i));
		}
		else if (pos.x - i >= 0 && pos.y + i < 8 && board[pos.x - i][pos.y + i] >= 97 && board[pos.x - i][pos.y + i] <= 122) {
			AP.push_back(make_pair(pos.x - i, pos.y + i));
			break;
		}
		else if (pos.x - i >= 0 && pos.y + i < 8 && board[pos.x - i][pos.y + i] >= 65 && board[pos.x - i][pos.y + i] <= 90 || board[pos.x - i][pos.y + i] == '1') {
			break;
		}
		else if (pos.x - i >= 0 && pos.y + i < 8 && board[pos.x - i][pos.y + i] == '2') {
			AP.push_back(make_pair(pos.x - i, pos.y + i));
			break;
		}
		else if (pos.x - i < 0 || pos.y + i >= 8) {
			break;
		}

	}
}

void Queen::GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {

	AP.push_back(make_pair(pos.x, pos.y));

	for (int r = pos.x - 1;r >= 0;r--) {

		if (board[r][pos.y] == '.')
			AP.push_back(make_pair(r, pos.y));
		else if (board[r][pos.y] >= 65 && board[r][pos.y] <= 90) {
			AP.push_back(make_pair(r, pos.y));
			break;
		}
		else if (board[r][pos.y] >= 97 && board[r][pos.y] <= 122 || board[r][pos.y] == '2') {
			break;
		}
		else if (board[r][pos.y] == '1') {
			AP.push_back(make_pair(r, pos.y));
			break;
		}
	}

	for (int r = pos.x + 1;r <= 8;r++) {

		if (board[r][pos.y] == '.')
			AP.push_back(make_pair(r, pos.y));
		else if (board[r][pos.y] >= 65 && board[r][pos.y] <= 90) {
			AP.push_back(make_pair(r, pos.y));
			break;
		}
		else if (board[r][pos.y] >= 97 && board[r][pos.y] <= 122 || board[r][pos.y] == '2') {
			break;
		}
		else if (board[r][pos.y] == '1') {
			AP.push_back(make_pair(r, pos.y));
			break;
		}
	}

	for (int c = pos.y - 1;c >= 0;c--) {

		if (board[pos.x][c] == '.')
			AP.push_back(make_pair(pos.x, c));
		else if (board[pos.x][c] >= 65 && board[pos.x][c] <= 90) {
			AP.push_back(make_pair(pos.x, c));
			break;
		}
		else if (board[pos.x][c] >= 90 && board[pos.x][c] <= 122 || board[pos.x][c] == '2') {
			break;
		}
		else if (board[pos.x][c] == '1') {
			AP.push_back(make_pair(pos.x, c));
			break;
		}
	}

	for (int c = pos.y + 1;c <= 8;c++) {

		if (board[pos.x][c] == '.')
			AP.push_back(make_pair(pos.x, c));
		else if (board[pos.x][c] >= 65 && board[pos.x][c] <= 90) {
			AP.push_back(make_pair(pos.x, c));
			break;
		}
		else if (board[pos.x][c] >= 90 && board[pos.x][c] <= 122 || board[pos.x][c] == '2') {
			break;
		}
		else if (board[pos.x][c] == '1') {
			AP.push_back(make_pair(pos.x, c));
			break;
		}
	}

	for (int i = 1;i < 8;i++) {

		if (board[pos.x + i][pos.y + i] == '.' && pos.x + i < 8 && pos.y + i < 8) {
			AP.push_back(make_pair(pos.x + i, pos.y + i));
		}
		else if (pos.x + i < 8 && pos.y + i < 8 && board[pos.x + i][pos.y + i] >= 65 && board[pos.x + i][pos.y + i] <= 90) {
			AP.push_back(make_pair(pos.x + i, pos.y + i));
			break;
		}
		else if (pos.x + i < 8 && pos.y + i < 8 && board[pos.x + i][pos.y + i] >= 97 && board[pos.x + i][pos.y + i] <= 122 || board[pos.x + i][pos.y + i] == '2') {
			break;
		}
		else if (pos.x + i < 8 && pos.y + i < 8 && board[pos.x + i][pos.y + i] == '1') {
			AP.push_back(make_pair(pos.x + i, pos.y + i));
			break;
		}
		else if (pos.x + i >= 8 || pos.y + i >= 8) {
			break;
		}

	}

	for (int i = 1;i < 8;i++) {

		if (board[pos.x + i][pos.y - i] == '.' && pos.x + i < 8 && pos.y - i >= 0) {
			AP.push_back(make_pair(pos.x + i, pos.y - i));
		}
		else if (pos.x + i < 8 && pos.y - i >= 0 && board[pos.x + i][pos.y - i] >= 65 && board[pos.x + i][pos.y - i] <= 90) {
			AP.push_back(make_pair(pos.x + i, pos.y - i));
			break;
		}
		else if (pos.x + i < 8 && pos.y - i >= 0 && board[pos.x + i][pos.y - i] >= 97 && board[pos.x + i][pos.y - i] <= 122 || board[pos.x + i][pos.y - i] == '2') {
			break;
		}
		else if (pos.x + i < 8 && pos.y - i >= 0 && board[pos.x + i][pos.y - i] == '1') {
			AP.push_back(make_pair(pos.x + i, pos.y - i));
			break;
		}
		else if (pos.x + i >= 8 || pos.y - i < 0) {
			break;
		}

	}

	for (int i = 1;i < 8;i++) {

		if (board[pos.x - i][pos.y - i] == '.' && pos.x - i >= 0 && pos.y - i >= 0) {
			AP.push_back(make_pair(pos.x - i, pos.y - i));
		}
		else if (pos.x - i >= 0 && pos.y - i >= 0 && board[pos.x - i][pos.y - i] >= 65 && board[pos.x - i][pos.y - i] <= 90) {
			AP.push_back(make_pair(pos.x - i, pos.y - i));
			break;
		}
		else if (pos.x - i >= 0 && pos.y - i >= 0 && board[pos.x - i][pos.y - i] >= 97 && board[pos.x - i][pos.y - i] <= 122 || board[pos.x - i][pos.y - i] == '2') {
			break;
		}
		else if (pos.x - i >= 0 && pos.y - i >= 0 && board[pos.x - i][pos.y - i] == '1') {
			AP.push_back(make_pair(pos.x - i, pos.y - i));
			break;
		}
		else if (pos.x - i < 0 || pos.y - i < 0) {
			break;
		}

	}

	for (int i = 1;i < 8;i++) {

		if (board[pos.x - i][pos.y + i] == '.' && pos.x - i >= 0 && pos.y + i < 8) {
			AP.push_back(make_pair(pos.x - i, pos.y + i));
		}
		else if (pos.x - i >= 0 && pos.y + i < 8 && board[pos.x - i][pos.y + i] >= 65 && board[pos.x - i][pos.y + i] <= 90) {
			AP.push_back(make_pair(pos.x - i, pos.y + i));
			break;
		}
		else if (pos.x - i >= 0 && pos.y + i < 8 && board[pos.x - i][pos.y + i] >= 90 && board[pos.x - i][pos.y + i] <= 122 || board[pos.x - i][pos.y + i] == '2') {
			break;
		}
		else if (pos.x - i >= 0 && pos.y + i < 8 && board[pos.x - i][pos.y + i] == '1') {
			AP.push_back(make_pair(pos.x - i, pos.y + i));
			break;
		}
		else if (pos.x - i < 0 || pos.y + i >= 8) {
			break;
		}

	}
};

RectangleShape& Queen::getQueenW(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posWhites[i] == pos)
			return queenW[i];
	}
	
};

RectangleShape* Queen::getQueenWatIndex(int index) {
	return &this->queenW[index];
};

RectangleShape& Queen::getQueenB(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posBlacks[i] == pos)
			return queenB[i];
	}

};

RectangleShape* Queen::getQueenBatIndex(int index) {
	return &this->queenB[index];
};