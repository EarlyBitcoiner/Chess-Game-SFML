#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <ctime>

#include "Board.h"
#include "Figures.h"

using namespace sf;
using namespace std;

int const displayX = GetSystemMetrics(SM_CXSCREEN);
int const displayY = GetSystemMetrics(SM_CYSCREEN);

class Board;
class Game {
private:

	// Variables 
	// Window
	RenderWindow* window;
	Event mainEv;
	Vector2i mousePosWindow;
	Board* chessBoard;
	Figures* figs;
	Font font;
	Text text;
	bool pressedFig = 0;
	char pressedFigSymbol;
	char playerTurn = 'W'; // the first player to take turn is the Whites (W).
	vector <pair<int, int>> validPositions; // here we put the valid positions of the piece we have pressed on.
	bool weHaveWinner = 0;


	 
	// Private func
	void createVar();
	void setWindow();
	void setText();

public:

	Game();

	virtual ~Game();

	vector<pair<int,int>> getValidPositions(char fig, Vector2i pos); // updates to hold the valid positions for the pressed figure.

	bool isRunning(); // returns if window is open.

	void poolEvents(); // grabs the events.

	void ExecMouseButtonPressedLogic();

	void ExecMouseButtonReleasedLogic();

	void update(); // takes the last event and acts upon it.

	void updateMousePos(); // updates the mouse position(x,y).

	void render(); // erases and displays the new frame after drawing the it.

	void checkIfKingIsInDanger(); // tells us if the king is in danger.

	void deleteFigure(int&, int&); // removes a figure drawable capabilities if taken by another figure.(just sets the position to -100,-100)

	bool checkIfNextMoveIsValid(int r,int c,pair<int,int>); // Does a simulation of the next move and decides it's validity based on whether the king will be put in danger. If you put your own king in danger then it is invalid. If your king is check and you make a move not putting it out of check it is invalid.

	void checkIfGameEnded(); // Here we check if the we have a winner or a draw.

	bool checkForStaleMate(); // We check for draw

	bool checkForCheckMate(); // We check if a king is in check mate.

	void placeBack(char&,pair<int,int>&); // places the figure's texture back on it's position after draging it with the mouse.

	void glueFigToMouse(char&); // glues the pressed figure to the mouse cursor until the button is released.

	void updateBoardPosition(int&,int&); // updates the board based on the moved figure and renders the figure on its new place.

	void mouseIndex(int& ,int& ,Vector2i&); // returns the index of the board on which the mouse happen to be when called.

};

#endif // !GAME_H
