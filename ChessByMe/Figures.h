#ifndef FIGURES_H
#define FIGURES_H

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>

#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "King.h"

using namespace sf;
using namespace std;

class Figures {
private:
	Knight knights;
	Bishop bishops;
	Pawn pawns;
	Queen queens;
	Rook rooks;
	King kings;

	void LoadStartingPositions();

public:
	char board[8][8];

	Figures();

	Knight& getKnights();

	Bishop& getBishops();

	Pawn& getPawns();

	Queen& getQueens();

	Rook& getRooks();

	King& getKings();
};

#endif 
