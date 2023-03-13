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
public:
	char board[8][8];
	Knight knights;
	Bishop bishops;
	Pawn pawns;
	Queen queens;
	Rook rooks;
	King kings;

	Figures();

	void LoadStartingPositions();


};

#endif 
