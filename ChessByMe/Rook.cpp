#include "Rook.h"

Rook::Rook() {
	
	this->posW[0] = (make_pair(0, 0)); this->posW[1] = (make_pair(0, 7));
	this->posB[0] = (make_pair(7, 0)); this->posB[1] = (make_pair(7, 7));

	texture[0].loadFromFile("Textures/w_rook.png"); // white piece is first
	texture[1].loadFromFile("Textures/b_rook.png"); // black piece is second

	rookW[0].setSize(Vector2f(90.f, 90.f));
	rookW[0].setTexture(&texture[0]);

	rookW[1] = rookW[0];
	
	rookB[0].setSize(Vector2f(90.f, 90.f));
	rookB[0].setTexture(&texture[1]);

	rookB[1] = rookB[0];

	for (size_t i = 0;i < 2;i++) {
		rookW[i].setPosition(Vector2f(posW[i].second * 100 + 5, posW[i].first * 100 + 5));
		rookB[i].setPosition(Vector2f(posB[i].second * 100 + 5, posB[i].first * 100 + 5));
	}
}

RectangleShape& Rook::getRookW(pair<int,int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posW[i] == pos)
			return rookW[i];
	}

};

RectangleShape& Rook::getRookB(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posB[i] == pos)
			return rookB[i];
	}

};

void Rook::GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {

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
};

void Rook::GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {

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
};