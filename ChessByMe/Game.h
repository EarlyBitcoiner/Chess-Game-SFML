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
	Board* chessBoard;
	Figures* figs;
	Event mainEv;
	Vector2i mousePosWindow;
	vector < pair < int, int > > pressedFigPossiblePositions; // here we put the valid positions of the piece we have pressed on.
	pair < int, int > lastMoveTo = make_pair(0, 0);
	pair < int, int > lastMoveFrom = make_pair(0, 0);
	Color lastMoveToColor = Color::White;
	Color lastMoveFromColor = Color::White;
	Font font;
	Text text;
	bool IsFigurePressed = 0;
	bool doWeHaveAWinner = 0;
	char pressedFigSymbol;
	char playerTurn = 'W'; // the first player to take turn is the Whites (W).
	 
	// Private func
	void createVar();
	void setWindow();
	void setText();

public:

	Game();

	bool IsPossiblePositionDesiredOne(pair<int, int>& it, int& moveToRow, int& moveToColumn);

	bool hasThePlayerPressedOnAValidFigure(int& r,int& c); // checks if the player clicked on valid figure.

	void setOrangeColor(int& oldPosX,int& oldPosY,int& newPosX,int& newPosY); // sets orange color to Board[][] textures at the given positions.

	void setDefaultColor(); // sets the default to Board[][] texture

	vector<pair<int,int>> getPossiblePositionsOfFigure(char fig, Vector2i pos); // updates to hold the valid positions for the pressed figure.

	bool isRunning(); // returns if window is open.

	void poolEvents(); // grabs the events.

	void ExecMouseButtonPressedLogic();

	void ExecMouseButtonReleasedLogic();

	void update(); // takes the last event and acts upon it.

	void updateMousePos(); // updates the mouse position(x,y).

	void render(); // erases and displays the new frame after drawing the it.

	void checkIfKingIsInDanger(); // tells us if the king is in danger.

	void deleteTakenFigureAt(int&, int&); // removes a figure drawable capabilities if taken by another figure.(just sets the position to -100,-100)

	bool checkIfPlayerPutsOwnKingInDanger(int r,int c,pair<int,int>); // Does a simulation of the next move and decides it's validity based on whether the king will be put in danger. If you put your own king in danger then it is invalid. If your king is check and you make a move not putting it out of check it is invalid.

	bool checkIfGameEnded(); // Here we check if the we have a winner or a draw.

	bool checkForStaleMate(); // We check for draw

	bool checkForCheckMate(); // We check if a king is in check mate.

	void placeFigureBack(char&,pair<int,int>&); // places the figure's texture back on it's position after draging it with the mouse.

	void glueFigToMouse(char&); // glues the pressed figure to the mouse cursor until the button is released.

	void updateBoardPosition(int&,int&); // updates the board based on the moved figure and renders the figure on its new place.

	void getMouseSittingIndex(int& ,int& ,Vector2i&); // returns the index of the board on which the mouse happen to be when called.

	virtual ~Game();
};

#endif // !GAME_H
