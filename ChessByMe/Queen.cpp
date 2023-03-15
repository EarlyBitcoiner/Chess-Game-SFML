#include "Queen.h"

Queen::Queen() {
	this->posW[0] = make_pair(0, 4);
	this->posB[0] = make_pair(7, 4);

	this->texture[0].loadFromFile("Textures/w_queen.png"); // white piece is first
	this->texture[1].loadFromFile("Textures/b_queen.png"); // black piece is second

	this->queenW[0].setSize(Vector2f(90.f, 90.f));
	this->queenW[0].setTexture(&texture[0]);
	this->queenW[0].setPosition(Vector2f(posW[0].second * 100 + 5, posW[0].first * 100 + 5));

	this->queenB[0].setSize(Vector2f(90.f, 90.f));
	this->queenB[0].setTexture(&texture[1]);
	this->queenB[0].setPosition(Vector2f(posB[0].second * 100 + 5, posB[0].first * 100 + 5));

}

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

	for (size_t i = 0;i < 5;i++) {
		if (posW[i] == pos)
			return queenW[i];
	}
	
};

RectangleShape& Queen::getQueenB(pair<int, int> pos) {

	for (size_t i = 0;i < 5;i++) {
		if (posB[i] == pos)
			return queenB[i];
	}

};