#include "Bishop.h"

Bishop::Bishop() {

	this->posW[0] = (make_pair(0, 2)); this->posW[1] = (make_pair(0, 5));
	this->posB[0] = (make_pair(7, 2)); this->posB[1] = (make_pair(7, 5));

	this->texture[0].loadFromFile("Textures/w_bishop.png"); // white piece is first
	this->texture[1].loadFromFile("Textures/b_bishop.png"); // black piece is second

	bishopW[0].setSize(Vector2f(90.f, 90.f));
	bishopW[0].setTexture(&texture[0]);

	bishopW[1] = bishopW[0];

	bishopB[0].setSize(Vector2f(90.f, 90.f));
	bishopB[0].setTexture(&texture[1]);

	bishopB[1] = bishopB[0];

	for (size_t i = 0;i < 2;i++) {
		bishopW[i].setPosition(Vector2f(posW[i].second * 100 + 5, posW[i].first * 100 + 5));
		bishopB[i].setPosition(Vector2f(posB[i].second * 100 + 5, posB[i].first * 100 + 5));
	}

}

void Bishop::GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {

	AP.push_back(make_pair(pos.x, pos.y));

	for (size_t i = 1;i < 8;i++) {

		if (board[pos.x + i][pos.y + i] == '.'&& pos.x+i<8&&pos.y+i<8) {
			AP.push_back(make_pair(pos.x + i, pos.y + i));
		}
		else if(pos.x + i < 8 && pos.y + i < 8 && board[pos.x+i][pos.y+i] >= 97 && board[pos.x + i][pos.y + i] <= 122) {
			AP.push_back(make_pair(pos.x + i, pos.y + i));
			break;
		}
		else if (pos.x + i < 8 && pos.y + i < 8 && board[pos.x + i][pos.y + i] >= 65 && board[pos.x + i][pos.y + i] <= 90) {
			break;
		}
		else if (pos.x + i < 8 && pos.y + i < 8 && board[pos.x + i][pos.y + i] == '2') {
			AP.push_back(make_pair(pos.x + i, pos.y + i));
			break;
		}

	}

	for (size_t i = 1;i < 8;i++) {

		if (board[pos.x + i][pos.y - i] == '.' && pos.x + i < 8 && pos.y - i >= 0) {
			AP.push_back(make_pair(pos.x + i, pos.y - i));
		}
		else if (pos.x + i < 8 && pos.y - i>=0 && board[pos.x + i][pos.y - i] >= 97 && board[pos.x + i][pos.y - i] <= 122) {
			AP.push_back(make_pair(pos.x + i, pos.y - i));
			break;
		}
		else if (pos.x + i < 8 && pos.y - i >= 0 && board[pos.x + i][pos.y - i] >= 65 && board[pos.x + i][pos.y - i] <= 90) {
			break;
		}
		else if (pos.x + i < 8 && pos.y - i >= 0 && board[pos.x + i][pos.y - i] == '2') {
			AP.push_back(make_pair(pos.x + i, pos.y - i));
			break;
		}
	}

	for (size_t i = 1;i < 8;i++) {

		if (board[pos.x - i][pos.y - i] == '.' && pos.x - i >= 0 && pos.y - i >= 0) {
			AP.push_back(make_pair(pos.x - i, pos.y - i));
		}
		else if (pos.x - i >= 0 && pos.y - i >= 0 && board[pos.x - i][pos.y - i] >= 97 && board[pos.x - i][pos.y - i] <= 122) {
			AP.push_back(make_pair(pos.x - i, pos.y - i));
			break;
		}
		else if (pos.x - i >= 0 && pos.y - i >= 0 && board[pos.x - i][pos.y - i] >= 65 && board[pos.x - i][pos.y - i] <= 90) {
			break;
		}
		else if (pos.x - i >= 0 && pos.y - i >= 0 && board[pos.x - i][pos.y - i] == '2') {
			AP.push_back(make_pair(pos.x - i, pos.y - i));
			break;
		}

	}

	for (size_t i = 1;i < 8;i++) {

		if (board[pos.x - i][pos.y + i] == '.' && pos.x - i >= 0 && pos.y + i < 8) {
			AP.push_back(make_pair(pos.x - i, pos.y + i));
		}
		else if (pos.x - i >= 0 && pos.y + i < 8 && board[pos.x - i][pos.y + i] >= 97 && board[pos.x - i][pos.y + i] <= 122) {
			AP.push_back(make_pair(pos.x - i, pos.y + i));
			break;
		}
		else if (pos.x - i >= 0 && pos.y + i < 8 && board[pos.x - i][pos.y + i] >= 65 && board[pos.x - i][pos.y +i] <= 90) {
			break;
		}
		else if (pos.x - i >= 0 && pos.y + i < 8 && board[pos.x - i][pos.y + i] == '2') {
			AP.push_back(make_pair(pos.x - i, pos.y + i));
			break;
		}

	}
}

void Bishop::GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {

	AP.push_back(make_pair(pos.x, pos.y));

	for (size_t i = 1;i < 8;i++) {

		if (board[pos.x + i][pos.y + i] == '.' && pos.x + i < 8 && pos.y + i < 8) {
			AP.push_back(make_pair(pos.x + i, pos.y + i));
		}
		else if (pos.x + i < 8 && pos.y + i < 8 && board[pos.x + i][pos.y + i] >= 65 && board[pos.x + i][pos.y + i] <= 90) {
			AP.push_back(make_pair(pos.x + i, pos.y + i));
			break;
		}
		else if (pos.x + i < 8 && pos.y + i < 8 && board[pos.x + i][pos.y + i] >= 97 && board[pos.x + i][pos.y + i] <= 122) {
			break;
		}
		else if (pos.x + i < 8 && pos.y + i < 8 && board[pos.x + i][pos.y + i] == '1') {
			AP.push_back(make_pair(pos.x + i, pos.y + i));
			break;
		}

	}

	for (size_t i = 1;i < 8;i++) {

		if (board[pos.x + i][pos.y - i] == '.' && pos.x + i < 8 && pos.y - i >= 0) {
			AP.push_back(make_pair(pos.x + i, pos.y - i));
		}
		else if (pos.x + i < 8 && pos.y - i >= 0 && board[pos.x + i][pos.y - i] >= 65 && board[pos.x + i][pos.y - i] <= 90) {
			AP.push_back(make_pair(pos.x + i, pos.y - i));
			break;
		}
		else if (pos.x + i < 8 && pos.y - i >= 0 && board[pos.x + i][pos.y - i] >= 97 && board[pos.x + i][pos.y - i] <= 122) {
			break;
		}
		else if (pos.x + i < 8 && pos.y - i >= 0 && board[pos.x + i][pos.y - i] == '1') {
			AP.push_back(make_pair(pos.x + i, pos.y - i));
			break;
		}

	}

	for (size_t i = 1;i < 8;i++) {

		if (board[pos.x - i][pos.y - i] == '.' && pos.x - i >= 0 && pos.y - i >= 0) {
			AP.push_back(make_pair(pos.x - i, pos.y - i));
		}
		else if (pos.x - i >= 0 && pos.y - i >= 0 && board[pos.x - i][pos.y - i] >= 65 && board[pos.x - i][pos.y - i] <= 90) {
			AP.push_back(make_pair(pos.x - i, pos.y - i));
			break;
		}
		else if (pos.x - i >= 0 && pos.y - i >= 0 && board[pos.x - i][pos.y - i] >= 97 && board[pos.x - i][pos.y - i] <= 122) {
			break;
		}
		else if (pos.x - i >= 0 && pos.y - i >= 0 && board[pos.x - i][pos.y - i] == '1') {
			AP.push_back(make_pair(pos.x - i, pos.y - i));
			break;
		}

	}

	for (size_t i = 1;i < 8;i++) {

		if (board[pos.x - i][pos.y + i] == '.' && pos.x - i >= 0 && pos.y + i < 8) {
			AP.push_back(make_pair(pos.x - i, pos.y + i));
		}
		else if (pos.x - i >= 0 && pos.y + i < 8 && board[pos.x - i][pos.y + i] >= 65 && board[pos.x - i][pos.y + i] <= 90) {
			AP.push_back(make_pair(pos.x - i, pos.y + i));
			break;
		}
		else if (pos.x - i >= 0 && pos.y + i < 8 && board[pos.x - i][pos.y + i] >= 90 && board[pos.x - i][pos.y + i] <= 122) {
			break;
		}
		else if (pos.x - i >= 0 && pos.y + i < 8 && board[pos.x - i][pos.y + i] == '1') {
			AP.push_back(make_pair(pos.x - i, pos.y + i));
			break;
		}

	}
}

RectangleShape& Bishop::getBishopW(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posW[i] == pos)
			return bishopW[i];
	}

};

RectangleShape& Bishop::getBishopB(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posB[i] == pos)
			return bishopB[i];
	}

};