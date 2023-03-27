#ifndef QUEEN_H
#define QUEEN_H

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <array>

using namespace std;
using namespace sf;

class Queen {
private:
	array<pair<int, int>, 8> posWhites;
	array<pair<int, int>, 8> posBlacks;
	Texture texture[2];
	RectangleShape queenW[8];
	RectangleShape queenB[8];

	int Wqueens = 1;
	int Bqueens = 1;

public:
	Queen();

	pair<int, int>& posWat(int index);

	pair<int, int>& posBat(int index);

	Texture& getWhiteTexture();

	Texture& getBlackTexture();

	array<pair<int, int>, 8>& getPosW();

	array<pair<int, int>, 8>& getPosB();

	void addWqueen();

	void addBqueen();

	int getWqueens();

	int getBqueens();

	void GetAvailablePosW(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	void GetAvailablePosB(char board[8][8], Vector2i pos, vector<pair<int, int>>& AP);

	RectangleShape& getQueenW(pair<int, int>);

	RectangleShape* getQueenWatIndex(int index);

	RectangleShape& getQueenB(pair<int, int>);

	RectangleShape* getQueenBatIndex(int index);

};

#endif
