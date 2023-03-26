#ifndef Board_h
#define Board_h

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>

#include "Game.h"

using namespace sf;
using namespace std;

class Board{
private:

	RectangleShape board[8][8];

public:

	Board();

	RectangleShape* getBoardBox(int& x, int& y);

};

#endif // !Board_h

