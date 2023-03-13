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
public:

	RectangleShape board[8][8];

public:

	Board();

};

#endif // !Board_h

