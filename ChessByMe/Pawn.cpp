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

void Pawn::GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {
	AP.push_back(make_pair(pos.x, pos.y));

	for (int i = 0;i < 8;i++) {

		if (posW[i] == make_pair(1, i))
			AP.push_back(make_pair(3,i));

		if (posW[i] == make_pair(pos.x, pos.y)) {
			if(pos.x+1 < 8 && board[pos.x+1][pos.y] == '.')
				AP.push_back(make_pair(pos.x+1, pos.y));

			if (pos.x + 1 >= 0 && pos.y + 1 >= 0 && (board[pos.x + 1][pos.y + 1] >= 97 && board[pos.x + 1][pos.y + 1] <= 122 || board[pos.x + 1][pos.y + 1] == '2'))
				AP.push_back(make_pair(pos.x + 1, pos.y + 1));

			if (pos.x + 1 >= 0 && pos.y - 1 >= 0 && (board[pos.x + 1][pos.y - 1] >= 97 && board[pos.x + 1][pos.y - 1] <= 122 || board[pos.x + 1][pos.y - 1] == '2'))
				AP.push_back(make_pair(pos.x + 1, pos.y - 1));
		}
		

	}
};

void Pawn::GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {
	AP.push_back(make_pair(pos.x, pos.y));

	for (int i = 0;i < 8;i++) {

		if (posB[i] == make_pair(6, i))
			AP.push_back(make_pair(4, i));

		if (posB[i] == make_pair(pos.x, pos.y)) {
			if (pos.x - 1 >= 0 && board[pos.x-1][pos.y] =='.')
				AP.push_back(make_pair(pos.x - 1, pos.y));

			if (pos.x - 1 >= 0 && pos.y - 1 >= 0 && (board[pos.x - 1][pos.y - 1] >= 65 && board[pos.x - 1][pos.y - 1] <= 90 || board[pos.x - 1][pos.y - 1] == '1'))
				AP.push_back(make_pair(pos.x - 1, pos.y - 1));

			if (pos.x - 1 >= 0 && pos.y + 1 >= 0 && (board[pos.x - 1][pos.y + 1] >= 65 && board[pos.x - 1][pos.y + 1] <= 90 || board[pos.x - 1][pos.y + 1] == '1'))
				AP.push_back(make_pair(pos.x - 1, pos.y + 1));
		}

	}
};

RectangleShape& Pawn::getPawnW(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posW[i] == pos)
			return pawnW[i];
	}

};

RectangleShape& Pawn::getPawnB(pair<int, int> pos) {

	for (size_t i = 0;i < 8;i++) {
		if (posB[i] == pos)
			return pawnB[i];
	}

};