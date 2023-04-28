#include "Figure.h"

void Figure::GetPossiblePosWhitesDiagonaly(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP)
{
	if (AP.size() == 0) {
		AP.push_back(make_pair(pos.x, pos.y));
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
		else if ((pos.x - i) < 0 || (pos.y - i) < 0) {
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

void Figure::GetPossiblePosBlacksDiagonaly(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP)
{
	if (AP.size() == 0) {
		AP.push_back(make_pair(pos.x, pos.y));
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
}

void Figure::GetPossiblePosRookWhites(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {

	if (AP.size()==0) {
		AP.push_back(make_pair(pos.x, pos.y));
	}

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

void Figure::GetPossiblePosRookBlacks(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {

	if (AP.size() == 0) {
		AP.push_back(make_pair(pos.x, pos.y));
	}

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
}

void Figure::GetPossiblePosQueenWhites(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP)
{
	this->GetPossiblePosRookWhites(board,pos,AP);
	this->GetPossiblePosWhitesDiagonaly(board, pos, AP);
}

void Figure::GetPossiblePosQueenBlacks(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP)
{
	this->GetPossiblePosRookBlacks(board, pos, AP);
	this->GetPossiblePosBlacksDiagonaly(board, pos, AP);
}

void Figure::GetPossiblePosKnightWhites(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {
	AP.push_back(make_pair(pos.x, pos.y));

	if (pos.x + 2 < 8 && pos.y + 1 < 8 &&
		(board[pos.x + 2][pos.y + 1] == '.' ||
			(board[pos.x + 2][pos.y + 1] >= 97 && board[pos.x + 2][pos.y + 1] <= 122)) ||
		board[pos.x + 2][pos.y + 1] == '2') {

		AP.push_back(make_pair(pos.x + 2, pos.y + 1));
	}

	if (pos.x + 2 < 8 && pos.y - 1 >= 0 &&
		(board[pos.x + 2][pos.y - 1] == '.' ||
			(board[pos.x + 2][pos.y - 1] >= 97 && board[pos.x + 2][pos.y - 1] <= 122)) ||
		board[pos.x + 2][pos.y - 1] == '2') {

		AP.push_back(make_pair(pos.x + 2, pos.y - 1));
	}

	if (pos.x + 1 < 8 && pos.y - 2 >= 0 &&
		(board[pos.x + 1][pos.y - 2] == '.' ||
			(board[pos.x + 1][pos.y - 2] >= 97 && board[pos.x + 1][pos.y - 2] <= 122)) ||
		board[pos.x + 1][pos.y - 2] == '2') {

		AP.push_back(make_pair(pos.x + 1, pos.y - 2));
	}

	if (pos.x - 1 >= 0 && pos.y - 2 >= 0 &&
		(board[pos.x - 1][pos.y - 2] == '.' ||
			(board[pos.x - 1][pos.y - 2] >= 97 && board[pos.x - 1][pos.y - 2] <= 122)) ||
		board[pos.x - 1][pos.y - 2] == '2') {

		AP.push_back(make_pair(pos.x - 1, pos.y - 2));
	}

	if (pos.x - 2 >= 0 && pos.y - 1 >= 0 &&
		(board[pos.x - 2][pos.y - 1] == '.' ||
			(board[pos.x - 2][pos.y - 1] >= 97 && board[pos.x - 2][pos.y - 1] <= 122)) ||
		board[pos.x - 2][pos.y - 1] == '2') {

		AP.push_back(make_pair(pos.x - 2, pos.y - 1));
	}

	if (pos.x - 2 >= 0 && pos.y + 1 < 8 &&
		(board[pos.x - 2][pos.y + 1] == '.' ||
			(board[pos.x - 2][pos.y + 1] >= 97 && board[pos.x - 2][pos.y + 1] <= 122)) ||
		board[pos.x - 2][pos.y + 1] == '2') {

		AP.push_back(make_pair(pos.x - 2, pos.y + 1));
	}

	if (pos.x - 1 >= 0 && pos.y + 2 < 8 &&
		(board[pos.x - 1][pos.y + 2] == '.' ||
			(board[pos.x - 1][pos.y + 2] >= 97 && board[pos.x - 1][pos.y + 2] <= 122)) ||
		board[pos.x - 1][pos.y + 2] == '2') {

		AP.push_back(make_pair(pos.x - 1, pos.y + 2));
	}

	if (pos.x + 1 < 8 && pos.y + 2 < 8 &&
		(board[pos.x + 1][pos.y + 2] == '.' ||
			(board[pos.x + 1][pos.y + 2] >= 97 && board[pos.x + 1][pos.y + 2] <= 122)) ||
		board[pos.x + 1][pos.y + 2] == '2') {

		AP.push_back(make_pair(pos.x + 1, pos.y + 2));
	}
};

void Figure::GetPossiblePosKnightBlacks(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP) {
	AP.push_back(make_pair(pos.x, pos.y));

	if (pos.x + 2 < 8 && pos.y + 1 < 8 &&
		(board[pos.x + 2][pos.y + 1] == '.' ||
			(board[pos.x + 2][pos.y + 1] >= 65 && board[pos.x + 2][pos.y + 1] <= 90)) ||
		board[pos.x + 2][pos.y + 1] == '1') {

		AP.push_back(make_pair(pos.x + 2, pos.y + 1));
	}

	if (pos.x + 2 < 8 && pos.y - 1 >= 0 &&
		(board[pos.x + 2][pos.y - 1] == '.' ||
			(board[pos.x + 2][pos.y - 1] >= 65 && board[pos.x + 2][pos.y - 1] <= 90)) ||
		board[pos.x + 2][pos.y - 1] == '1') {

		AP.push_back(make_pair(pos.x + 2, pos.y - 1));
	}

	if (pos.x + 1 < 8 && pos.y - 2 >= 0 &&
		(board[pos.x + 1][pos.y - 2] == '.' ||
			(board[pos.x + 1][pos.y - 2] >= 65 && board[pos.x + 1][pos.y - 2] <= 90)) ||
		board[pos.x + 1][pos.y - 2] == '1') {

		AP.push_back(make_pair(pos.x + 1, pos.y - 2));
	}

	if (pos.x - 1 >= 0 && pos.y - 2 >= 0 &&
		(board[pos.x - 1][pos.y - 2] == '.' ||
			(board[pos.x - 1][pos.y - 2] >= 65 && board[pos.x - 1][pos.y - 2] <= 90)) ||
		board[pos.x - 1][pos.y - 2] == '1') {

		AP.push_back(make_pair(pos.x - 1, pos.y - 2));
	}

	if (pos.x - 2 >= 0 && pos.y - 1 >= 0 &&
		(board[pos.x - 2][pos.y - 1] == '.' ||
			(board[pos.x - 2][pos.y - 1] >= 65 && board[pos.x - 2][pos.y - 1] <= 90)) ||
		board[pos.x - 2][pos.y - 1] == '1') {

		AP.push_back(make_pair(pos.x - 2, pos.y - 1));
	}

	if (pos.x - 2 >= 0 && pos.y + 1 < 8 &&
		(board[pos.x - 2][pos.y + 1] == '.' ||
			(board[pos.x - 2][pos.y + 1] >= 65 && board[pos.x - 2][pos.y + 1] <= 90)) ||
		board[pos.x - 2][pos.y + 1] == '1') {

		AP.push_back(make_pair(pos.x - 2, pos.y + 1));
	}

	if (pos.x - 1 >= 0 && pos.y + 2 < 8 &&
		(board[pos.x - 1][pos.y + 2] == '.' ||
			(board[pos.x - 1][pos.y + 2] >= 65 && board[pos.x - 1][pos.y + 2] <= 90)) ||
		board[pos.x - 1][pos.y + 2] == '1') {

		AP.push_back(make_pair(pos.x - 1, pos.y + 2));
	}

	if (pos.x + 1 < 8 && pos.y + 2 < 8 &&
		(board[pos.x + 1][pos.y + 2] == '.' ||
			(board[pos.x + 1][pos.y + 2] >= 65 && board[pos.x + 1][pos.y + 2] <= 90)) ||
		board[pos.x + 1][pos.y + 2] == '1') {

		AP.push_back(make_pair(pos.x + 1, pos.y + 2));
	}
}

void Figure::GetPossiblePosPawnWhites(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP)
{
	AP.push_back(make_pair(pos.x, pos.y));

	if (pos.x == 1 && board[pos.x + 2][pos.y] == '.')
		AP.push_back(make_pair(pos.x + 2, pos.y));

	if (pos.x + 1 < 8 && board[pos.x + 1][pos.y] == '.')
		AP.push_back(make_pair(pos.x + 1, pos.y));

	if (pos.x + 1 >= 0 && pos.y + 1 >= 0 && (board[pos.x + 1][pos.y + 1] >= 97 && board[pos.x + 1][pos.y + 1] <= 122 || board[pos.x + 1][pos.y + 1] == '2'))
		AP.push_back(make_pair(pos.x + 1, pos.y + 1));

	if (pos.x + 1 >= 0 && pos.y - 1 >= 0 && (board[pos.x + 1][pos.y - 1] >= 97 && board[pos.x + 1][pos.y - 1] <= 122 || board[pos.x + 1][pos.y - 1] == '2'))
		AP.push_back(make_pair(pos.x + 1, pos.y - 1));

}

void Figure::GetPossiblePosPawnBlacks(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP)
{
	AP.push_back(make_pair(pos.x, pos.y));

	if (pos.x == 6 && board[pos.x - 2][pos.y] == '.')
		AP.push_back(make_pair(pos.x - 2, pos.y));

	if (pos.x - 1 >= 0 && board[pos.x - 1][pos.y] == '.')
		AP.push_back(make_pair(pos.x - 1, pos.y));

	if (pos.x - 1 >= 0 && pos.y - 1 >= 0 && (board[pos.x - 1][pos.y - 1] >= 65 && board[pos.x - 1][pos.y - 1] <= 90 || board[pos.x - 1][pos.y - 1] == '1'))
		AP.push_back(make_pair(pos.x - 1, pos.y - 1));

	if (pos.x - 1 >= 0 && pos.y + 1 >= 0 && (board[pos.x - 1][pos.y + 1] >= 65 && board[pos.x - 1][pos.y + 1] <= 90 || board[pos.x - 1][pos.y + 1] == '1'))
		AP.push_back(make_pair(pos.x - 1, pos.y + 1));

}

void Figure::GetPossiblePosKingWhites(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP)
{
	AP.push_back(make_pair(pos.x, pos.y));

	if ((board[pos.x + 1][pos.y] == '.' || board[pos.x + 1][pos.y] >= 97 && board[pos.x + 1][pos.y] <= 122 || board[pos.x + 1][pos.y] == '2') &&
		pos.x + 1 < 8)
		AP.push_back(make_pair(pos.x + 1, pos.y));

	if ((board[pos.x + 1][pos.y - 1] == '.' || board[pos.x + 1][pos.y - 1] >= 97 && board[pos.x + 1][pos.y - 1] <= 122 || board[pos.x + 1][pos.y - 1] == '2') &&
		pos.y - 1 >= 0 && pos.x + 1 < 8)
		AP.push_back(make_pair(pos.x + 1, pos.y - 1));

	if ((board[pos.x][pos.y - 1] == '.' || board[pos.x][pos.y - 1] >= 97 && board[pos.x][pos.y - 1] <= 122 || board[pos.x][pos.y - 1] == '2') &&
		pos.y - 1 >= 0)
		AP.push_back(make_pair(pos.x, pos.y - 1));

	if ((board[pos.x - 1][pos.y - 1] == '.' || board[pos.x - 1][pos.y - 1] >= 97 && board[pos.x - 1][pos.y - 1] <= 122 || board[pos.x - 1][pos.y - 1] == '2') &&
		pos.x - 1 >= 0 && pos.y - 1 >= 0)
		AP.push_back(make_pair(pos.x - 1, pos.y - 1));

	if ((board[pos.x - 1][pos.y] == '.' || board[pos.x - 1][pos.y] >= 97 && board[pos.x - 1][pos.y] <= 122 || board[pos.x - 1][pos.y] == '2') &&
		pos.x - 1 >= 0)
		AP.push_back(make_pair(pos.x - 1, pos.y));

	if ((board[pos.x - 1][pos.y + 1] == '.' || board[pos.x - 1][pos.y + 1] >= 97 && board[pos.x - 1][pos.y + 1] <= 122 || board[pos.x - 1][pos.y + 1] == '2') &&
		pos.x - 1 >= 0 && pos.y + 1 < 8)
		AP.push_back(make_pair(pos.x - 1, pos.y + 1));

	if ((board[pos.x][pos.y + 1] == '.' || board[pos.x][pos.y + 1] >= 97 && board[pos.x][pos.y + 1] <= 122 || board[pos.x][pos.y + 1] == '2') &&
		pos.y + 1 < 8)
		AP.push_back(make_pair(pos.x, pos.y + 1));

	if ((board[pos.x + 1][pos.y + 1] == '.' || board[pos.x + 1][pos.y + 1] >= 97 && board[pos.x + 1][pos.y + 1] <= 122 || board[pos.x + 1][pos.y + 1] == '2') &&
		pos.x + 1 < 8 && pos.y + 1 < 8)
		AP.push_back(make_pair(pos.x + 1, pos.y + 1));
}

void Figure::GetPossiblePosKingBlacks(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP)
{
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
}
