
#include "Game.h"
#include "Board.h"
#include "Figures.h"

// Events Logic
void Game::poolEvents() {

	while (this->window->pollEvent(mainEv)) { // we stay here until all events are gone through.

		if (this->mainEv.type == Event::Closed)
			this->window->close(); // this condition is true only if we press the X of the window to close it. 

		if (this->mainEv.type == Event::MouseButtonPressed && this->mainEv.mouseButton.button == Mouse::Left)
			ExecMouseButtonPressedLogic();

		if (this->mainEv.type == Event::MouseButtonReleased && this->mainEv.mouseButton.button == Mouse::Left && IsFigurePressed == 1)
			ExecMouseButtonReleasedLogic();
		else if (this->IsFigurePressed == 1) // We constantly go through this [else if] when we are dragging a figure.
			glueFigToMouse(this->pressedFigSymbol); // glues the pressed figure to the mouse cursor until the button is released.
	}

}

// Game Logic
vector<pair<int,int>> Game::getPossiblePositionsOfFigure(char fig,Vector2i pos) {

	vector<pair<int, int>> v;

	switch (fig) {
	case 'R':
		this->figs->getRooks().GetPossiblePosRookWhites(figs->board, pos, v);
		break;	  
	case 'r':
		this->figs->getRooks().GetPossiblePosRookBlacks(figs->board, pos, v);
		break;
	case 'K':
		this->figs->getKnights().GetPossiblePosKnightWhites(figs->board, pos, v);
		break;
	case 'k':
		this->figs->getKnights().GetPossiblePosKnightBlacks(figs->board, pos, v);
		break;
	case 'B':
		this->figs->getBishops().GetPossiblePosWhitesDiagonaly(figs->board, pos, v);
		break;
	case 'b':
		this->figs->getBishops().GetPossiblePosBlacksDiagonaly(figs->board, pos, v);
		break;
	case 'P':
		this->figs->getPawns().GetPossiblePosPawnWhites(figs->board, pos, v);
		break;
	case 'p':
		this->figs->getPawns().GetPossiblePosPawnBlacks(figs->board, pos, v);
		break;
	case 'Q':
		this->figs->getQueens().GetPossiblePosQueenWhites(figs->board, pos, v);
		break;
	case 'q':
		this->figs->getQueens().GetPossiblePosQueenBlacks(figs->board, pos, v);
		break;
	case '1':
		this->figs->getKings().GetPossiblePosKingWhites(figs->board, pos, v);
		break;
	case '2':
		this->figs->getKings().GetPossiblePosKingBlacks(figs->board, pos, v);
		break;
	}

	return v;

};

void Game::ExecMouseButtonPressedLogic() {

	this->mousePosWindow.x = mainEv.mouseButton.x;
	this->mousePosWindow.y = mainEv.mouseButton.y;

	int row = 0, column = 0;

	getMouseSittingIndex(row, column, mousePosWindow); // returns the board index on which the mouse happen to be when called by assigning it in r and c.

	if(!hasThePlayerPressedOnAValidFigure(row, column))
		return;

	this->IsFigurePressed = 1; // by setting the value 1 we now know that the player pressed on a figure and will maybe drag it.
	this->pressedFigSymbol = figs->board[row][column]; //we get the symbol to know with what figure we have to work.
	this->pressedFigPossiblePositions = getPossiblePositionsOfFigure(figs->board[row][column], Vector2i(row, column)); // we get the valid positions on which the pressed figure can move.

};

void Game::ExecMouseButtonReleasedLogic() {
	this->IsFigurePressed = 0;
	this->mousePosWindow.x = mainEv.mouseButton.x;
	this->mousePosWindow.y = mainEv.mouseButton.y;
	int desiredMoveToRow = 0, desiredMoveToColumn = 0;

	getMouseSittingIndex(desiredMoveToRow, desiredMoveToColumn, mousePosWindow); // returns the index of the board on which the mouse happen to be when called.
	
	vector<pair<int, int>>::iterator currPossiblePos = pressedFigPossiblePositions.begin();

	while (currPossiblePos != pressedFigPossiblePositions.end()) {
		currPossiblePos++;

		if (currPossiblePos == pressedFigPossiblePositions.end()) {
			pair<int, int> oldFigPos = pressedFigPossiblePositions.front();

			placeFigureBack(this->pressedFigSymbol, oldFigPos); // places the figure's texture back on it's position after draging it with the mouse.
			break;
		}

		if (IsPossiblePositionDesiredOne(*currPossiblePos, desiredMoveToRow, desiredMoveToColumn))
			break;

	}

	this->pressedFigSymbol = '0';
	this->pressedFigPossiblePositions.clear();
};

bool Game::IsPossiblePositionDesiredOne(pair<int, int>& it, int& desiredMoveToRow, int& desiredMoveToColumn) {

	if (it.first == desiredMoveToRow && it.second == desiredMoveToColumn) {

		if (!checkIfPlayerPutsOwnKingInDanger(desiredMoveToRow, desiredMoveToColumn, pressedFigPossiblePositions[0])) {

			deleteTakenFigureAt(desiredMoveToRow, desiredMoveToColumn); // removes a figure drawable capabilities if taken by another figure.(just sets the position to -100,-100)
			updateBoardPosition(desiredMoveToRow, desiredMoveToColumn); // updates the board based on the moved figure and renders the figure on its new place.

			checkIfKingIsInDanger();

			(playerTurn == 'W') ? playerTurn = 'B' : playerTurn = 'W'; // if we arrive here that means the player which turn it is has made a valid move and now we change turns.
			return true;
		}
		else {

			pair<int, int> oldPos = pressedFigPossiblePositions.front();
			placeFigureBack(this->pressedFigSymbol, oldPos);

			return false;
		}

	}

	return false;
}

void Game::update() {

	poolEvents();
	//cout << "mouse is at " << Mouse::getPosition(*window).x << " " << Mouse::getPosition(*window).y << endl;
}

void Game::render() {
	// Erase drawings
	window->clear();
	
	// Draw Board
	for (int r = 0;r < 8;r++) {
		for (int c = 0;c < 8;c++) {
			window->draw(*this->chessBoard->getBoardBox(r,c));
		}
	}

	// Draw Figures
	for (size_t i = 0;i < 8;i++) {
		window->draw(*figs->getQueens().getWQueenShapeAt(i));
	}

	for (size_t i = 0;i < 8;i++) {
		window->draw(*figs->getQueens().getBQueenShapeAt(i));
	}

	for (size_t i = 0;i < 2;i++) {
		window->draw(figs->getKings().getKingShapeAt(i));

		window->draw(figs->getRooks().getWRookShapeAt(i));
		window->draw(figs->getRooks().getBRookShapeAt(i));

		window->draw(figs->getBishops().getWBishopShapeAt(i));
		window->draw(figs->getBishops().getBBishopShapeAt(i));

		window->draw(figs->getKnights().getWKnightShapeAt(i));
		window->draw(figs->getKnights().getBKnightShapeAt(i));
	}

	for (size_t i = 0;i < 8;i++) {
		window->draw(figs->getPawns().getWPawnShapeAt(i));
		window->draw(figs->getPawns().getBPawnShapeAt(i));
	}

	if (doWeHaveAWinner) {
		window->draw(text);
	}

	// Display drawn
	window->display();

}

void Game::updateMousePos() {

	this->mousePosWindow = Mouse::getPosition(*this->window);

}

bool Game::isRunning() {
	return window->isOpen();
};

bool Game::checkIfPlayerPutsOwnKingInDanger(int r, int c, pair<int,int> oldFigPos) {
	char boardCopy[8][8]; // making a variable to the board.

	// copying the board.
	for (size_t row = 0;row < 8;row++) {
		for (size_t column = 0;column < 8;column++) {
			boardCopy[row][column] = figs->board[row][column];
		}
	} 

	// updating the copy based on the made move.
	boardCopy[r][c] = this->pressedFigSymbol/*figs->board[oldFigPos.first][oldFigPos.second]*/;
	boardCopy[oldFigPos.first][oldFigPos.second] = '.';

	vector <pair<int, int>> currentFigurePossibleMoves; // use this vector to iterate through the board and store the available moves of the figure we iterate.

	pair<int, int> KingWPos; // making variable to store the position of the white king.
	pair<int, int> KingBPos; // making variable to store the position of the black king.

	(boardCopy[r][c] == '1') ? KingWPos = make_pair(r, c) : KingWPos = figs->getKings().getPosW(); // finding and assigning the white king position.
	(boardCopy[r][c] == '2') ? KingBPos = make_pair(r, c) : KingBPos = figs->getKings().getPosB(); // finding and assigning the black king position.

	// we iterate through every position on the board. j is for rows and k is for columns.
	for (int j = 0;j < 8;j++) {
		for (int k = 0;k < 8;k++) {
			// we only do switch case for position with figure on it.
			if (boardCopy[j][k] != '.') {
				// get the possible moves of the figure on the current position and saving them in the vector [current].
				switch (boardCopy[j][k]) {
				case 'R':
					this->figs->getRooks().GetPossiblePosRookWhites(boardCopy, Vector2i(j, k), currentFigurePossibleMoves);
					break;
				case 'r':
					this->figs->getRooks().GetPossiblePosRookBlacks(boardCopy, Vector2i(j, k), currentFigurePossibleMoves);
					break;
				case 'K':
					this->figs->getKnights().GetPossiblePosKnightWhites(boardCopy, Vector2i(j, k), currentFigurePossibleMoves);
					break;
				case 'k':
					this->figs->getKnights().GetPossiblePosKnightBlacks(boardCopy, Vector2i(j, k), currentFigurePossibleMoves);
					break;
				case 'B':
					this->figs->getBishops().GetPossiblePosWhitesDiagonaly(boardCopy, Vector2i(j, k), currentFigurePossibleMoves);
					break;
				case 'b':
					this->figs->getBishops().GetPossiblePosBlacksDiagonaly(boardCopy, Vector2i(j, k), currentFigurePossibleMoves);
					break;
				case 'P':
					this->figs->getPawns().GetPossiblePosPawnWhites(boardCopy, Vector2i(j, k), currentFigurePossibleMoves);
					break;
				case 'p':
					this->figs->getPawns().GetPossiblePosPawnBlacks(boardCopy, Vector2i(j, k), currentFigurePossibleMoves);
					break;
				case 'Q':
					this->figs->getQueens().GetPossiblePosQueenWhites(boardCopy, Vector2i(j, k), currentFigurePossibleMoves);
					break;
				case 'q':
					this->figs->getQueens().GetPossiblePosQueenBlacks(boardCopy, Vector2i(j, k), currentFigurePossibleMoves);
					break;
				case '1':
					this->figs->getKings().GetPossiblePosKingWhites(boardCopy, Vector2i(j, k), currentFigurePossibleMoves);
					break;
				case '2':
					this->figs->getKings().GetPossiblePosKingBlacks(boardCopy, Vector2i(j, k), currentFigurePossibleMoves);
					break;
				}

				// checking if the vector current has any positions in it. We check bigger than 1 because there will be
				// always 1 position in it (of the figure we are checking).
				if (currentFigurePossibleMoves.size() > 1) {

					// making sure whites is not putting his own king in danger.
					if (find(currentFigurePossibleMoves.begin() + 1, currentFigurePossibleMoves.end(), KingWPos) != currentFigurePossibleMoves.end() && playerTurn == 'W') {
						return true;
					} // cheking if the king is still in check if it was.
					else if(find(currentFigurePossibleMoves.begin() + 1, currentFigurePossibleMoves.end(), KingWPos) != currentFigurePossibleMoves.end() && playerTurn == 'W' && figs->getKings().getWinDanger()) {
						return true;
					} // making sure blacks is not putting his own king in danger.
					else if (find(currentFigurePossibleMoves.begin() + 1, currentFigurePossibleMoves.end(), KingBPos) != currentFigurePossibleMoves.end() && playerTurn == 'B') {
						return true;
					} // checking if the king is still in check if it was.
					else if (find(currentFigurePossibleMoves.begin() + 1, currentFigurePossibleMoves.end(), KingBPos) != currentFigurePossibleMoves.end() && playerTurn == 'B' && figs->getKings().getBinDanger()) {
						return true;
					}
				}

				// emptying the vector for the next iteartion
				currentFigurePossibleMoves.clear();
			}
		}
	}

	// if we haven't returned false until now then the move is valid and our king is not in danger so we return true.
	return false;
}

void Game::checkIfGameEnded()
{
	if (this->figs->getKings().getWinDanger()) {
		if (checkForCheckMate()) {
			this->text.setString("Black Wins!");
			playerTurn = '.';
			doWeHaveAWinner = 1;
			return;
		};
	}
	else if (this->figs->getKings().getBinDanger()) {
		if (checkForCheckMate()) {
			this->text.setString("White Wins!");
			playerTurn = '.';
			doWeHaveAWinner = 1;
			return;
		};
	}
	else if (this->figs->getKings().getWinDanger() == 0 && this->figs->getKings().getBinDanger() == 0) {
		if (checkForStaleMate()) {
			this->text.setString("STALEMATE");
			playerTurn = '.';
			doWeHaveAWinner = 1;
			return;
		}
	}
}

bool Game::checkForStaleMate() {
	vector <pair<int, int>> curr; // use this vector to iterate through the board and store the available positions of figure we iterate.

	if (figs->getKings().getWinDanger() == 0) {

		for (int j = 0;j < 8;j++) {
			for (int k = 0;k < 8;k++) {
				// we only do switch case for position with figure on it.
				if (this->figs->board[j][k] != '.') {
					// get the possible moves of the figure on the current position and saving them in the vector [current].
					switch (figs->board[j][k]) {
					case 'R':
						this->figs->getRooks().GetPossiblePosRookWhites(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'K':
						this->figs->getKnights().GetPossiblePosKnightWhites(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'B':
						this->figs->getBishops().GetPossiblePosWhitesDiagonaly(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'P':
						this->figs->getPawns().GetPossiblePosPawnWhites(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'Q':
						this->figs->getQueens().GetPossiblePosQueenWhites(this->figs->board, Vector2i(j, k), curr);
						break;
					case '1':
						this->figs->getKings().GetPossiblePosKingWhites(this->figs->board, Vector2i(j, k), curr);
						break;
					}

					// checking if the vector current has any positions in it. We check bigger than 1 because there will be
					// always 1 position in it (of the figure we are checking).
					if (curr.size() > 1) {

						for (vector<pair<int, int>>::iterator it = curr.begin() + 1; it != curr.end(); it++) {

							if (checkIfPlayerPutsOwnKingInDanger(it->first, it->second, curr.front())) {
								return false;
							}

						}

					}

					// emptying the vector for the next iteartion
					curr.clear();
				}
			}
		}

		return true;
	}

	if (figs->getKings().getBinDanger() == 0) {

		for (int j = 0;j < 8;j++) {
			for (int k = 0;k < 8;k++) {
				// we only do switch case for position with figure on it.
				if (this->figs->board[j][k] != '.') {
					// get the possible moves of the figure on the current position and saving them in the vector [current].
					switch (figs->board[j][k]) {
					case 'r':
						this->figs->getRooks().GetPossiblePosRookBlacks(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'k':
						this->figs->getKnights().GetPossiblePosKnightBlacks(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'b':
						this->figs->getBishops().GetPossiblePosBlacksDiagonaly(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'p':
						this->figs->getPawns().GetPossiblePosPawnBlacks(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'q':
						this->figs->getQueens().GetPossiblePosQueenBlacks(this->figs->board, Vector2i(j, k), curr);
						break;
					case '2':
						this->figs->getKings().GetPossiblePosKingBlacks(this->figs->board, Vector2i(j, k), curr);
						break;
					}

					// checking if the vector current has any positions in it. We check bigger than 1 because there will be
					// always 1 position in it (of the figure we are checking).
					if (curr.size() > 1) {

						for (vector<pair<int, int>>::iterator it = curr.begin() + 1; it != curr.end(); it++) {

							if (checkIfPlayerPutsOwnKingInDanger(it->first, it->second, curr.front())) {
								return false;
							}

						}

					}

					// emptying the vector for the next iteartion
					curr.clear();
				}
			}
		}

		return true;
	}
}

bool Game::checkForCheckMate() {

	vector <pair<int, int>> curr; // use this vector to iterate through the board and store the available positions of figure we iterate.

	if (figs->getKings().getWinDanger()) {

		for (int j = 0;j < 8;j++) {
			for (int k = 0;k < 8;k++) {
				// we only do switch case for position with figure on it.
				if (this->figs->board[j][k] != '.') {
					// get the possible moves of the figure on the current position and saving them in the vector [current].
					switch (figs->board[j][k]) {
					case 'R':
						this->figs->getRooks().GetPossiblePosRookWhites(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'K':
						this->figs->getKnights().GetPossiblePosRookWhites(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'B':
						this->figs->getBishops().GetPossiblePosRookWhites(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'P':
						this->figs->getPawns().GetPossiblePosRookWhites(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'Q':
						this->figs->getQueens().GetPossiblePosRookWhites(this->figs->board, Vector2i(j, k), curr);
						break;
					case '1':
						this->figs->getKings().GetPossiblePosRookWhites(this->figs->board, Vector2i(j, k), curr);
						break;
					}

					// checking if the vector current has any positions in it. We check bigger than 1 because there will be
					// always 1 position in it (of the figure we are checking).
					if (curr.size() > 1) {

						for (vector<pair<int, int>>::iterator it = curr.begin() + 1; it != curr.end(); it++) {

							if (checkIfPlayerPutsOwnKingInDanger(it->first, it->second, curr.front())) {
								return false;
							}

						}
						
					}

					// emptying the vector for the next iteartion
					curr.clear();
				}
			}
		}

		return true;
	}

	if (figs->getKings().getBinDanger()) {

		for (int j = 0;j < 8;j++) {
			for (int k = 0;k < 8;k++) {
				// we only do switch case for position with figure on it.
				if (this->figs->board[j][k] != '.') {
					// get the possible moves of the figure on the current position and saving them in the vector [current].
					switch (figs->board[j][k]) {
					case 'r':
						this->figs->getRooks().GetPossiblePosRookBlacks(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'k':
						this->figs->getKnights().GetPossiblePosRookBlacks(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'b':
						this->figs->getBishops().GetPossiblePosRookBlacks(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'p':
						this->figs->getPawns().GetPossiblePosRookBlacks(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'q':
						this->figs->getQueens().GetPossiblePosRookBlacks(this->figs->board, Vector2i(j, k), curr);
						break;
					case '2':
						this->figs->getKings().GetPossiblePosRookBlacks(this->figs->board, Vector2i(j, k), curr);
						break;
					}

					// checking if the vector current has any positions in it. We check bigger than 1 because there will be
					// always 1 position in it (of the figure we are checking).
					if (curr.size() > 1) {

						for (vector<pair<int, int>>::iterator it = curr.begin() + 1; it != curr.end(); it++) {

							if (checkIfPlayerPutsOwnKingInDanger(it->first, it->second, curr.front())) {
								return false;
							}

						}

					}

					// emptying the vector for the next iteartion
					curr.clear();
				}
			}
		}

		return true;
	}
}

void Game::checkIfKingIsInDanger() {
	pair<int, int> kingWpos = this->figs->getKings().getPosW();
	pair<int, int> kingBpos = this->figs->getKings().getPosB();

	vector<pair<int, int>> whites;
	vector<pair<int, int>> blacks;

	vector<pair<int, int>> temporary;

	//  SECTION WHITE POSITIONS //
	for (size_t i = 0;i < 2;i++) {
		temporary = getPossiblePositionsOfFigure('R', Vector2i(figs->getRooks().getPosW()[i].first, figs->getRooks().getPosW()[i].second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 2;i++) {
		temporary = getPossiblePositionsOfFigure('K', Vector2i(figs->getKnights().getPosW()[i].first, figs->getKnights().getPosW()[i].second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 2;i++) {
		temporary = getPossiblePositionsOfFigure('B', Vector2i(figs->getBishops().getPosW()[i].first, figs->getBishops().getPosW()[i].second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 8;i++) {
		temporary = getPossiblePositionsOfFigure('P', Vector2i(figs->getPawns().getPosW()[i].first, figs->getPawns().getPosW()[i].second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < this->figs->getQueens().getWqueens();i++) {
		temporary = getPossiblePositionsOfFigure('Q', Vector2i(figs->getQueens().posWat(i).first, figs->getQueens().posWat(i).second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	temporary = getPossiblePositionsOfFigure('1', Vector2i(figs->getKings().getPosW().first, figs->getKings().getPosW().second));
	whites.insert(whites.end(), temporary.begin(), temporary.end());

	// SECTION BLACK POSITIONS //
	for (size_t i = 0;i < 2;i++) {
		temporary = getPossiblePositionsOfFigure('r', Vector2i(figs->getRooks().getPosB()[i].first, figs->getRooks().getPosB()[i].second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 2;i++) {
		temporary = getPossiblePositionsOfFigure('k', Vector2i(figs->getKnights().getPosB()[i].first, figs->getKnights().getPosB()[i].second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 2;i++) {
		temporary = getPossiblePositionsOfFigure('b', Vector2i(figs->getBishops().getPosB()[i].first, figs->getBishops().getPosB()[i].second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 8;i++) {
		temporary = getPossiblePositionsOfFigure('p', Vector2i(figs->getPawns().getPosB()[i].first, figs->getPawns().getPosB()[i].second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < this->figs->getQueens().getBqueens();i++) {
		temporary = getPossiblePositionsOfFigure('q', Vector2i(figs->getQueens().posBat(i).first, figs->getQueens().posBat(i).second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	temporary = getPossiblePositionsOfFigure('2', Vector2i(figs->getKings().getPosB().first, figs->getKings().getPosB().second));
	blacks.insert(blacks.end(), temporary.begin(), temporary.end());

	//------------------------------------------------------------------------------//
	vector<pair<int, int>>::iterator Wdanger = find(blacks.begin(),blacks.end(),kingWpos);
	vector<pair<int, int>>::iterator Bdanger = find(whites.begin(), whites.end(), kingBpos);

	if (Wdanger != blacks.end()) {
		this->figs->getKings().setWinDanger(1);
		this->figs->getKings().getKingShapeAt(0).setFillColor(Color(252, 3, 119));
	}
	else {
		this->figs->getKings().setWinDanger(0);
		this->figs->getKings().getKingShapeAt(0).setFillColor(Color::White);
	}

	if (Bdanger != whites.end()) {
		this->figs->getKings().setBinDanger(1);
		this->figs->getKings().getKingShapeAt(1).setFillColor(Color(252, 3, 119));
	}
	else {
		this->figs->getKings().setBinDanger(0);
		this->figs->getKings().getKingShapeAt(1).setFillColor(Color::White);
	};
};

void Game::deleteTakenFigureAt(int& row,int& column) {

	// condition != "." (TRUE) means that we have moved to a position on the board containing other figure so we have to delete it before updating the board. condition == "." (FALSE) means that we have moved to an empty position and quickly do the 2 else if's below then directly skip to the updateBoardPosition() function.
	if (figs->board[row][column] != '.') {
		char symbol = figs->board[row][column];

		switch (symbol) {
		case('R'):
			this->figs->getRooks().getWRookShapeAt(make_pair(row,column)).setPosition(Vector2f(-100,-100));
			replace(this->figs->getRooks().getPosW().begin(), this->figs->getRooks().getPosW().end(), make_pair(row, column), make_pair(-10, -10));
			break;
		case('r'):
			this->figs->getRooks().getBRookShapeAt(make_pair(row, column)).setPosition(Vector2f(-100, -100));
			replace(this->figs->getRooks().getPosB().begin(), this->figs->getRooks().getPosB().end(), make_pair(row, column), make_pair(-10, -10));
			break;
		case('K'):
			this->figs->getKnights().getWKnightShapeAt(make_pair(row, column)).setPosition(Vector2f(-100, -100));
			replace(this->figs->getKnights().getPosW().begin(), this->figs->getKnights().getPosW().end(), make_pair(row, column), make_pair(-10, -10));
			break;
		case('k'):;
			this->figs->getKnights().getBKnightShapeAt(make_pair(row, column)).setPosition(Vector2f(-100, -100));
			replace(this->figs->getKnights().getPosB().begin(), this->figs->getKnights().getPosB().end(), make_pair(row, column), make_pair(-10, -10));
			break;
		case('B'):
			this->figs->getBishops().getWBishopShapeAt(make_pair(row, column)).setPosition(Vector2f(-100, -100));
			replace(this->figs->getBishops().getPosW().begin(), this->figs->getBishops().getPosW().end(), make_pair(row, column), make_pair(-10, -10));
			break;
		case('b'):
			this->figs->getBishops().getBBishopShapeAt(make_pair(row, column)).setPosition(Vector2f(-100, -100));
			replace(this->figs->getBishops().getPosB().begin(), this->figs->getBishops().getPosB().end(), make_pair(row, column), make_pair(-10, -10));
			break;
		case('P'):
			this->figs->getPawns().getWPawnShapeAt(make_pair(row, column)).setPosition(Vector2f(-100, -100));
			replace(this->figs->getPawns().getPosW().begin(), this->figs->getPawns().getPosW().end(), make_pair(row, column), make_pair(-10, -10));
			break;
		case('p'):
			this->figs->getPawns().getBPawnShapeAt(make_pair(row, column)).setPosition(Vector2f(-100, -100));
			replace(this->figs->getPawns().getPosB().begin(), this->figs->getPawns().getPosB().end(), make_pair(row, column), make_pair(-10, -10));
			break;
		case('Q'):
			this->figs->getQueens().getBQueenShapeAt(make_pair(row, column)).setPosition(Vector2f(-100, -100));
			replace(this->figs->getQueens().getPosW().begin(), this->figs->getQueens().getPosW().end(), make_pair(row, column), make_pair(-10, -10));
			break;
		case('q'):
			this->figs->getQueens().getBQueenShapeAt(make_pair(row, column)).setPosition(Vector2f(-100, -100));
			replace(this->figs->getQueens().getPosB().begin(), this->figs->getQueens().getPosB().end(), make_pair(row, column), make_pair(-10, -10));
			break;
		}

	} // the extra else if condition below are to delete the pawn taken by en passant move. We need this else if's because en passant move need specific logic which we cant put in the switch case above.
	else if(this->pressedFigSymbol == 'P' && figs->board[row - 1][column] == 'p') { 

		// this is true if we have made en passant move (if there is a black pawn behind our white pawn).

		this->figs->getPawns().getBPawnShapeAt(figs->getPawns().getEnPassantPawnPos()).setPosition(Vector2f(-100, -100));

		replace(this->figs->getPawns().getPosB().begin(), this->figs->getPawns().getPosB().end(), figs->getPawns().getEnPassantPawnPos(), make_pair(-10, -10));

		figs->board[row - 1][column] = '.';// setting the position behind our pawn to empty because the updateBoardPosition() can not do it for us when the move is en passant.
	}
	else if (this->pressedFigSymbol == 'p' && figs->board[row + 1][column] == 'P') {

		// this is true if we have made en passant move(if there is a white pawn behind our black pawn).

		this->figs->getPawns().getWPawnShapeAt(figs->getPawns().getEnPassantPawnPos()).setPosition(Vector2f(-100, -100));

		replace(this->figs->getPawns().getPosW().begin(), this->figs->getPawns().getPosW().end(), figs->getPawns().getEnPassantPawnPos(), make_pair(-10, -10));

		figs->board[row + 1][column] = '.'; // setting the position behind our pawn to empty because the updateBoardPosition() can not do it for us when the move is en passant.
	}
};

void Game::placeFigureBack(char& symbol,pair<int,int>& oldPos) {

	switch (symbol) {
	case('R'):
		this->figs->getRooks().getWRookShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('r'):

		this->figs->getRooks().getBRookShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('K'):
		this->figs->getKnights().getWKnightShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('k'):;
		this->figs->getKnights().getBKnightShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('B'):
		this->figs->getBishops().getWBishopShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('b'):
		this->figs->getBishops().getBBishopShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('P'):
		this->figs->getPawns().getWPawnShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('p'):
		this->figs->getPawns().getBPawnShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('Q'):
		this->figs->getQueens().getWQueenShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('q'):
		this->figs->getQueens().getBQueenShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('1'):
		this->figs->getKings().getWKingShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('2'):
		this->figs->getKings().getBKingShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	}

}

void Game::updateBoardPosition(int& r, int& c) {
	//r stand for row and c stands for column. We need them to know the position of which the player wants to move the draged piece.

	pair<int, int> oldPos = pressedFigPossiblePositions.front(); // We get the old position of the moved piece.

	this->setDefaultColor();
	this->setOrangeColor(oldPos.first,oldPos.second,r,c);

	switch (this->pressedFigSymbol) {
	case('R'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'R';
		this->figs->getRooks().getWRookShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->getRooks().getPosW().begin(), figs->getRooks().getPosW().end(), oldPos, make_pair(r, c));
		break;
	case('r'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'r';
		this->figs->getRooks().getBRookShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->getRooks().getPosB().begin(), figs->getRooks().getPosB().end(), oldPos, make_pair(r, c));
		break;
	case('K'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'K';
		this->figs->getKnights().getWKnightShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->getKnights().getPosW().begin(), figs->getKnights().getPosW().end(), oldPos, make_pair(r, c));
		break;
	case('k'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'k';
		this->figs->getKnights().getBKnightShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->getKnights().getPosB().begin(), figs->getKnights().getPosB().end(), oldPos, make_pair(r, c));
		break;
	case('B'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'B';
		this->figs->getBishops().getWBishopShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->getBishops().getPosW().begin(), figs->getBishops().getPosW().end(), oldPos, make_pair(r, c));
		break;
	case('b'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'b';
		this->figs->getBishops().getBBishopShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->getBishops().getPosB().begin(), figs->getBishops().getPosB().end(), oldPos, make_pair(r, c));
		break;
	case('P'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'P';
		this->figs->getPawns().getWPawnShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->getPawns().getPosW().begin(), figs->getPawns().getPosW().end(), oldPos, make_pair(r, c));

		if (oldPos.first + 2 == r && oldPos.second == c) {
			// condition checks if the made move puts the pawn 2 postions forward. If TRUE then the pawn is now in En Passant so we raise the indicator and save the pawn position to help us calculate the next moves for the enemy getPawns(). If FALSE we skip to the else where we lower the indicator saying the pawn is in En Passant danger.

			figs->getPawns().raiseEnPassant();
			figs->getPawns().setEnPassantPawnPos(make_pair(r, c));
		}
		else {
			figs->getPawns().lowerEnPassant();
		}

		if (r == 7) {
			// condition TRUE when WHITE has arrived to the end of the board with out pawn. Now we execute the code below creating the player a Queen.

			this->figs->getPawns().getWPawnShapeAt(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			replace(this->figs->getPawns().getPosW().begin(), this->figs->getPawns().getPosW().end(), make_pair(r, c), make_pair(-10, -10));

			this->figs->board[r][c] = 'Q';

			this->figs->getQueens().addWqueen();
			this->figs->getQueens().getPosW()[figs->getQueens().getWqueens() - 1] = make_pair(r, c);

			RectangleShape* Q = this->figs->getQueens().getWQueenShapeAt(figs->getQueens().getWqueens() - 1);

			Q->setSize(Vector2f(90.f, 90.f));
			Q->setTexture(&this->figs->getQueens().getWhiteTexture());
			Q->setPosition(Vector2f(c * 100 + 5, r * 100 + 5));
		}

		break;
	case('p'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'p';
		this->figs->getPawns().getBPawnShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->getPawns().getPosB().begin(), figs->getPawns().getPosB().end(), oldPos, make_pair(r, c));

		if (oldPos.first - 2 == r && oldPos.second == c) {
			// condition checks if the made move puts the pawn 2 postions forward. If TRUE then the pawn is now in En Passant so we raise the indicator and save the pawn position to help us calculate the next moves for the enemy getPawns(). If FALSE we skip to the else where we lower the indicator saying the pawn is in En Passant danger.

			figs->getPawns().raiseEnPassant();
			figs->getPawns().setEnPassantPawnPos(make_pair(r, c));
		}
		else {
			figs->getPawns().lowerEnPassant();
		}

		if (r == 0) {
			// condition TRUE when BLACK has arrived to the end of the board with out pawn. Now we execute the code below creating the player a Queen.

			this->figs->getPawns().getBPawnShapeAt(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			replace(this->figs->getPawns().getPosB().begin(), this->figs->getPawns().getPosB().end(), make_pair(r, c), make_pair(-10, -10));

			this->figs->board[r][c] = 'q';

			this->figs->getQueens().addBqueen();
			this->figs->getQueens().getPosB()[figs->getQueens().getBqueens() - 1] = make_pair(r, c);

			RectangleShape* q = this->figs->getQueens().getBQueenShapeAt(figs->getQueens().getBqueens() - 1);

			q->setSize(Vector2f(90.f, 90.f));
			q->setTexture(&this->figs->getQueens().getBlackTexture());
			q->setPosition(Vector2f(c * 100 + 5, r * 100 + 5));
		}

		break;
	case('Q'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'Q';
		this->figs->getQueens().getWQueenShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->getQueens().getPosW().begin(), figs->getQueens().getPosW().end(), oldPos, make_pair(r, c));
		break;
	case('q'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'q';
		this->figs->getQueens().getBQueenShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->getQueens().getPosB().begin(), figs->getQueens().getPosB().end(), oldPos, make_pair(r, c));
		break;
	case('1'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = '1';
		this->figs->getKings().getWKingShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		this->figs->getKings().getPosW() = make_pair(r, c);

		if (r == 0 && c == 1 && figs->getKings().gethasWmoved() == 0) {
			this->figs->board[0][0] = '.';
			this->figs->board[0][2] = 'R';
			this->figs->getRooks().getWRookShapeAt(make_pair(0,0)).setPosition(Vector2f(2 * 100 + 5, 0 * 100 + 5));

			replace(figs->getRooks().getPosW().begin(), figs->getRooks().getPosW().end(), make_pair(0, 0), make_pair(0, 2));
		}

		if (r == 0 && c == 5 && figs->getKings().gethasWmoved() == 0) {
			this->figs->board[0][7] = '.';
			this->figs->board[0][4] = 'R';
			this->figs->getRooks().getWRookShapeAt(make_pair(0, 7)).setPosition(Vector2f(4 * 100 + 5, 0 * 100 + 5));

			replace(figs->getRooks().getPosW().begin(), figs->getRooks().getPosW().end(), make_pair(0, 7), make_pair(0, 4));
		}
		
		if (this->figs->getKings().gethasWmoved() == 0)
			this->figs->getKings().sethasWmoved(1);

		break;
	case('2'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = '2';
		this->figs->getKings().getBKingShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		this->figs->getKings().getPosB() = make_pair(r, c);

		if (r == 7 && c == 1 && figs->getKings().gethasBmoved() == 0) {
			this->figs->board[7][0] = '.';
			this->figs->board[7][2] = 'r';
			this->figs->getRooks().getBRookShapeAt(make_pair(7, 0)).setPosition(Vector2f(2 * 100 + 5, 7 * 100 + 5));

			replace(figs->getRooks().getPosB().begin(), figs->getRooks().getPosB().end(), make_pair(7, 0), make_pair(7, 2));
		}

		if (r == 7 && c == 5 && figs->getKings().gethasBmoved() == 0) {
			this->figs->board[7][7] = '.';
			this->figs->board[7][4] = 'r';
			this->figs->getRooks().getBRookShapeAt(make_pair(7, 7)).setPosition(Vector2f(4 * 100 + 5, 7 * 100 + 5));

			replace(figs->getRooks().getPosB().begin(), figs->getRooks().getPosB().end(), make_pair(7, 7), make_pair(7, 4));
		}

		if (this->figs->getKings().gethasBmoved() == 0)
			this->figs->getKings().sethasBmoved(1);

		break;
	}

};

void Game::glueFigToMouse(char& symbol) {

	updateMousePos();

	switch (this->pressedFigSymbol) {
	case('R'):
		this->figs->getRooks().getWRookShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('r'):
		this->figs->getRooks().getBRookShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('K'):
		this->figs->getKnights().getWKnightShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('k'):
		this->figs->getKnights().getBKnightShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('B'):
		this->figs->getBishops().getWBishopShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('b'):
		this->figs->getBishops().getBBishopShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('P'):
		this->figs->getPawns().getWPawnShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('p'):
		this->figs->getPawns().getBPawnShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('Q'):
		this->figs->getQueens().getWQueenShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('q'):
		this->figs->getQueens().getBQueenShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('1'):
		this->figs->getKings().getWKingShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('2'):
		this->figs->getKings().getBKingShapeAt(pressedFigPossiblePositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	}
};

void Game::getMouseSittingIndex(int& x,int& y,Vector2i& mousePos) {
	bool breakFor = 0;

	for (size_t row = 0;row < 8;row++) {
		for (size_t column = 0;column < 8;column++) {
			if (mousePos.x >= column * 100 && mousePos.y >= row * 100 && mousePos.x < (column + 1) * 100 && mousePos.y < (row + 1) * 100) {
				x = row; y = column; breakFor = 1;
				break;
			}
		}
		if (breakFor)
			break;
	}

};

bool Game::hasThePlayerPressedOnAValidFigure(int& r, int& c)
{
	if (playerTurn == 'W' && (figs->board[r][c] >= 98 && figs->board[r][c] <= 122 || figs->board[r][c] == '2' || figs->board[r][c] == '.'))
		return false;
	else if (playerTurn == 'B' && (figs->board[r][c] >= 65 && figs->board[r][c] <= 90 || figs->board[r][c] == '1' || figs->board[r][c] == '.'))
		return false;

	return true;
}

void Game::setOrangeColor(int& oldPosX, int& oldPosY, int& newPosX, int& newPosY)
{
	this->lastMoveTo = make_pair(newPosX, newPosY);
	this->lastMoveFrom = make_pair(oldPosX, oldPosY);
	RectangleShape* box = this->chessBoard->getBoardBox(newPosX, newPosY);

	this->lastMoveToColor = box->getFillColor();
	box->setFillColor(Color(255, 129, 3));

	box = this->chessBoard->getBoardBox(oldPosX, oldPosY);

	this->lastMoveFromColor = box->getFillColor();
	box->setFillColor(Color(255, 129, 3));
}

void Game::setDefaultColor()
{
	RectangleShape* box = this->chessBoard->getBoardBox(lastMoveTo.first, lastMoveTo.second);
	box->setFillColor(lastMoveToColor);

	box = this->chessBoard->getBoardBox(lastMoveFrom.first, lastMoveFrom.second);
	box->setFillColor(lastMoveFromColor);
}

// Constructors
Game::Game() {
  
	this->createVar();
	this->setWindow();
	this->setText();
};

void Game::createVar() {
	this->window = nullptr;
	this->chessBoard = new Board;
	this->figs = new Figures;
};

void Game::setWindow() {
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	this->window = new RenderWindow(VideoMode(800, 800), "Classic Chess", Style::Titlebar | Style::Close, settings );

	window->setFramerateLimit(144);
};

void Game::setText() {
	this->font.loadFromFile("Fonts/arial.ttf");
	this->text.setFont(font);
	this->text.setFillColor(Color(52, 235, 103));
	this->text.setCharacterSize(60);
	this->text.setStyle(Text::Bold | Text::Underlined);
	this->text.setPosition(Vector2f(240, 350));
}

// Destructor
Game::~Game() {
	delete window;
	delete chessBoard;
	delete figs;
}
