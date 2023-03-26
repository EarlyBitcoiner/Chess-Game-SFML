
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

		if (this->mainEv.type == Event::MouseButtonReleased && this->mainEv.mouseButton.button == Mouse::Left && pressedFig == 1)
			ExecMouseButtonReleasedLogic();
		else if (this->pressedFig == 1) // We constantly go through this [else if] when we are dragging a figure.
			glueFigToMouse(this->pressedFigSymbol); // glues the pressed figure to the mouse cursor until the button is released.
	}

}

// Game Logic
vector<pair<int,int>> Game::getValidPositions(char fig,Vector2i pos) {

	vector<pair<int, int>> v;

	switch (fig) {
	case 'R':
		this->figs->rooks.GetAvailablePosW(figs->board, pos, v);
		break;	  
	case 'r':
		this->figs->rooks.GetAvailablePosB(figs->board, pos, v);
		break;
	case 'K':
		this->figs->knights.GetAvailablePosW(figs->board, pos, v);
		break;
	case 'k':
		this->figs->knights.GetAvailablePosB(figs->board, pos, v);
		break;
	case 'B':
		this->figs->bishops.GetAvailablePosW(figs->board, pos, v);
		break;
	case 'b':
		this->figs->bishops.GetAvailablePosB(figs->board, pos, v);
		break;
	case 'P':
		this->figs->pawns.GetAvailablePosW(figs->board, pos, v);
		break;
	case 'p':
		this->figs->pawns.GetAvailablePosB(figs->board, pos, v);
		break;
	case 'Q':
		this->figs->queens.GetAvailablePosW(figs->board, pos, v);
		break;
	case 'q':
		this->figs->queens.GetAvailablePosB(figs->board, pos, v);
		break;
	case '1':
		this->figs->kings.GetAvailablePosW(figs->board, pos, v);
		break;
	case '2':
		this->figs->kings.GetAvailablePosB(figs->board, pos, v);
		break;
	}

	return v;

};

void Game::ExecMouseButtonPressedLogic() {

	this->mousePosWindow.x = mainEv.mouseButton.x;
	this->mousePosWindow.y = mainEv.mouseButton.y;

	int r = 0, c = 0;

	mouseIndex(r, c, mousePosWindow); // returns the board index on which the mouse happen to be when called by assigning it in r and c.

	if (playerTurn == 'W' && (figs->board[r][c] >= 98 && figs->board[r][c] <= 122 || figs->board[r][c] == '2'))
		return;
	else if (playerTurn == 'B' && (figs->board[r][c] >= 65 && figs->board[r][c] <= 90 || figs->board[r][c] == '1'))
		return;
	else if (playerTurn == '.')
		return;

	if (figs->board[r][c] != '.') {
		this->pressedFig = 1; // by setting the value 1 we now know that the player pressed on a figure and will maybe drag it.
		this->pressedFigSymbol = figs->board[r][c]; //we get the symbol to know with what figure we have to work.
		this->validPositions = getValidPositions(figs->board[r][c], Vector2i(r, c)); // we get the valid position on which the pressed figure can move.
	}

};

void Game::ExecMouseButtonReleasedLogic() {
	this->pressedFig = 0;
	this->mousePosWindow.x = mainEv.mouseButton.x;
	this->mousePosWindow.y = mainEv.mouseButton.y;
	int r = 0, c = 0;

	mouseIndex(r, c, mousePosWindow); // returns the index of the board on which the mouse happen to be when called.
	vector<pair<int, int>>::iterator it = validPositions.begin();

	while (it != validPositions.end()) {
		it++;

		if (it == validPositions.end()) {
			pair<int, int> oldPos = validPositions.front();

			placeBack(this->pressedFigSymbol, oldPos); // places the figure's texture back on it's position after draging it with the mouse.
			break;
		}

		if (*it == make_pair(r, c)) {

			if (checkIfNextMoveIsValid(r, c, validPositions[0])) {

				deleteFigure(r, c); // removes a figure drawable capabilities if taken by another figure.(just sets the position to -100,-100)
				updateBoardPosition(r, c); // updates the board based on the moved figure and renders the figure on its new place.

				checkIfKingIsInDanger();

				(playerTurn == 'W') ? playerTurn = 'B' : playerTurn = 'W'; // if we arrive here that means the player which turn it is has made a valid move and now we change turns.
				break;
			}
			else {

				pair<int, int> oldPos = validPositions.front();
				placeBack(this->pressedFigSymbol, oldPos);

				break;
			}

		}
	}

	this->pressedFigSymbol = '0';
	this->validPositions.clear();
};

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
		window->draw(*figs->queens.getQueenWatIndex(i));
	}

	for (size_t i = 0;i < 8;i++) {
		window->draw(*figs->queens.getQueenBatIndex(i));
	}

	for (size_t i = 0;i < 2;i++) {
		window->draw(figs->kings.getKingAtIndex(i));

		window->draw(figs->rooks.getRookWatIndex(i));
		window->draw(figs->rooks.getRookBatIndex(i));

		window->draw(figs->bishops.getBishopWatIndex(i));
		window->draw(figs->bishops.getBishopBatIndex(i));

		window->draw(figs->knights.getKnightWatIndex(i));
		window->draw(figs->knights.getKnightBatIndex(i));
	}

	for (size_t i = 0;i < 8;i++) {
		window->draw(figs->pawns.getPawnWatIndex(i));
		window->draw(figs->pawns.getPawnBatIndex(i));
	}

	if (weHaveWinner) {
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

bool Game::checkIfNextMoveIsValid(int r, int c, pair<int,int> pos) {
	char boardCopy[8][8]; // making a variable to the board.

	// copying the board.
	for (size_t j = 0;j < 8;j++) {
		for (size_t k = 0;k < 8;k++) {
			boardCopy[j][k] = figs->board[j][k];
		}
	} 

	// updating the copy based on the made move.
	boardCopy[r][c] = figs->board[pos.first][pos.second];
	boardCopy[pos.first][pos.second] = '.';

	vector <pair<int, int>> current; // use this vector to iterate through the board and store the available positions of figure we iterate.

	pair<int, int> KingW; // making variable to store the position of the white king.
	pair<int, int> KingB; // making variable to store the position of the black king.

	(boardCopy[r][c] == '1') ? KingW = make_pair(r, c) : KingW = figs->kings.getPosW(); // finding and assigning the white king position.
	(boardCopy[r][c] == '2') ? KingB = make_pair(r, c) : KingB = figs->kings.getPosB(); // finding and assigning the black king position.

	// we iterate through every position on the board. j is for rows and k is for columns.
	for (int j = 0;j < 8;j++) {
		for (int k = 0;k < 8;k++) {
			// we only do switch case for position with figure on it.
			if (boardCopy[j][k] != '.') {
				// get the possible moves of the figure on the current position and saving them in the vector [current].
				switch (boardCopy[j][k]) {
				case 'R':
					this->figs->rooks.GetAvailablePosW(boardCopy, Vector2i(j, k), current);
					break;
				case 'r':
					this->figs->rooks.GetAvailablePosB(boardCopy, Vector2i(j, k), current);
					break;
				case 'K':
					this->figs->knights.GetAvailablePosW(boardCopy, Vector2i(j, k), current);
					break;
				case 'k':
					this->figs->knights.GetAvailablePosB(boardCopy, Vector2i(j, k), current);
					break;
				case 'B':
					this->figs->bishops.GetAvailablePosW(boardCopy, Vector2i(j, k), current);
					break;
				case 'b':
					this->figs->bishops.GetAvailablePosB(boardCopy, Vector2i(j, k), current);
					break;
				case 'P':
					this->figs->pawns.GetAvailablePosW(boardCopy, Vector2i(j, k), current);
					break;
				case 'p':
					this->figs->pawns.GetAvailablePosB(boardCopy, Vector2i(j, k), current);
					break;
				case 'Q':
					this->figs->queens.GetAvailablePosW(boardCopy, Vector2i(j, k), current);
					break;
				case 'q':
					this->figs->queens.GetAvailablePosB(boardCopy, Vector2i(j, k), current);
					break;
				case '1':
					this->figs->kings.GetAvailablePosW(boardCopy, Vector2i(j, k), current);
					break;
				case '2':
					this->figs->kings.GetAvailablePosB(boardCopy, Vector2i(j, k), current);
					break;
				}

				// checking if the vector current has any positions in it. We check bigger than 1 because there will be
				// always 1 position in it (of the figure we are checking).
				if (current.size() > 1) {

					// making sure whites is not putting his own king in danger.
					if (find(current.begin() + 1, current.end(), KingW) != current.end() && playerTurn == 'W') {
						return false;
					} // cheking if the king is still in check if it was.
					else if(find(current.begin() + 1, current.end(), KingW) != current.end() && playerTurn == 'W' && figs->kings.getWinDanger()) {
						return false;
					} // making sure blacks is not putting his own king in danger.
					else if (find(current.begin() + 1, current.end(), KingB) != current.end() && playerTurn == 'B') {
						return false;
					} // checking if the king is still in check if it was.
					else if (find(current.begin() + 1, current.end(), KingB) != current.end() && playerTurn == 'B' && figs->kings.getBinDanger()) {
						return false;
					}
				}

				// emptying the vector for the next iteartion
				current.clear();
			}
		}
	}

	// if we haven't returned false until now then the move is valid and our king is not in danger so we return true.
	return true;
}

void Game::checkIfGameEnded()
{
	if (this->figs->kings.getWinDanger()) {
		if (checkForCheckMate()) {
			this->text.setString("Black Wins!");
			playerTurn = '.';
			weHaveWinner = 1;
			return;
		};
	}
	else if (this->figs->kings.getBinDanger()) {
		if (checkForCheckMate()) {
			this->text.setString("White Wins!");
			playerTurn = '.';
			weHaveWinner = 1;
			return;
		};
	}
	else if (this->figs->kings.getWinDanger() == 0 && this->figs->kings.getBinDanger() == 0) {
		if (checkForStaleMate()) {
			this->text.setString("STALEMATE");
			playerTurn = '.';
			weHaveWinner = 1;
			return;
		}
	}
}

bool Game::checkForStaleMate() {
	vector <pair<int, int>> curr; // use this vector to iterate through the board and store the available positions of figure we iterate.

	if (figs->kings.getWinDanger() == 0) {

		for (int j = 0;j < 8;j++) {
			for (int k = 0;k < 8;k++) {
				// we only do switch case for position with figure on it.
				if (this->figs->board[j][k] != '.') {
					// get the possible moves of the figure on the current position and saving them in the vector [current].
					switch (figs->board[j][k]) {
					case 'R':
						this->figs->rooks.GetAvailablePosW(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'K':
						this->figs->knights.GetAvailablePosW(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'B':
						this->figs->bishops.GetAvailablePosW(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'P':
						this->figs->pawns.GetAvailablePosW(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'Q':
						this->figs->queens.GetAvailablePosW(this->figs->board, Vector2i(j, k), curr);
						break;
					case '1':
						this->figs->kings.GetAvailablePosW(this->figs->board, Vector2i(j, k), curr);
						break;
					}

					// checking if the vector current has any positions in it. We check bigger than 1 because there will be
					// always 1 position in it (of the figure we are checking).
					if (curr.size() > 1) {

						for (vector<pair<int, int>>::iterator it = curr.begin() + 1; it != curr.end(); it++) {

							if (checkIfNextMoveIsValid(it->first, it->second, curr.front())) {
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

	if (figs->kings.getBinDanger() == 0) {

		for (int j = 0;j < 8;j++) {
			for (int k = 0;k < 8;k++) {
				// we only do switch case for position with figure on it.
				if (this->figs->board[j][k] != '.') {
					// get the possible moves of the figure on the current position and saving them in the vector [current].
					switch (figs->board[j][k]) {
					case 'r':
						this->figs->rooks.GetAvailablePosB(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'k':
						this->figs->knights.GetAvailablePosB(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'b':
						this->figs->bishops.GetAvailablePosB(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'p':
						this->figs->pawns.GetAvailablePosB(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'q':
						this->figs->queens.GetAvailablePosB(this->figs->board, Vector2i(j, k), curr);
						break;
					case '2':
						this->figs->kings.GetAvailablePosB(this->figs->board, Vector2i(j, k), curr);
						break;
					}

					// checking if the vector current has any positions in it. We check bigger than 1 because there will be
					// always 1 position in it (of the figure we are checking).
					if (curr.size() > 1) {

						for (vector<pair<int, int>>::iterator it = curr.begin() + 1; it != curr.end(); it++) {

							if (checkIfNextMoveIsValid(it->first, it->second, curr.front())) {
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

	if (figs->kings.getWinDanger()) {

		for (int j = 0;j < 8;j++) {
			for (int k = 0;k < 8;k++) {
				// we only do switch case for position with figure on it.
				if (this->figs->board[j][k] != '.') {
					// get the possible moves of the figure on the current position and saving them in the vector [current].
					switch (figs->board[j][k]) {
					case 'R':
						this->figs->rooks.GetAvailablePosW(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'K':
						this->figs->knights.GetAvailablePosW(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'B':
						this->figs->bishops.GetAvailablePosW(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'P':
						this->figs->pawns.GetAvailablePosW(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'Q':
						this->figs->queens.GetAvailablePosW(this->figs->board, Vector2i(j, k), curr);
						break;
					case '1':
						this->figs->kings.GetAvailablePosW(this->figs->board, Vector2i(j, k), curr);
						break;
					}

					// checking if the vector current has any positions in it. We check bigger than 1 because there will be
					// always 1 position in it (of the figure we are checking).
					if (curr.size() > 1) {

						for (vector<pair<int, int>>::iterator it = curr.begin() + 1; it != curr.end(); it++) {

							if (checkIfNextMoveIsValid(it->first, it->second, curr.front())) {
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

	if (figs->kings.getBinDanger()) {

		for (int j = 0;j < 8;j++) {
			for (int k = 0;k < 8;k++) {
				// we only do switch case for position with figure on it.
				if (this->figs->board[j][k] != '.') {
					// get the possible moves of the figure on the current position and saving them in the vector [current].
					switch (figs->board[j][k]) {
					case 'r':
						this->figs->rooks.GetAvailablePosB(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'k':
						this->figs->knights.GetAvailablePosB(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'b':
						this->figs->bishops.GetAvailablePosB(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'p':
						this->figs->pawns.GetAvailablePosB(this->figs->board, Vector2i(j, k), curr);
						break;
					case 'q':
						this->figs->queens.GetAvailablePosB(this->figs->board, Vector2i(j, k), curr);
						break;
					case '2':
						this->figs->kings.GetAvailablePosB(this->figs->board, Vector2i(j, k), curr);
						break;
					}

					// checking if the vector current has any positions in it. We check bigger than 1 because there will be
					// always 1 position in it (of the figure we are checking).
					if (curr.size() > 1) {

						for (vector<pair<int, int>>::iterator it = curr.begin() + 1; it != curr.end(); it++) {

							if (checkIfNextMoveIsValid(it->first, it->second, curr.front())) {
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
	pair<int, int> kingWpos = this->figs->kings.getPosW();
	pair<int, int> kingBpos = this->figs->kings.getPosB();

	vector<pair<int, int>> whites;
	vector<pair<int, int>> blacks;

	vector<pair<int, int>> temporary;

	//  SECTION WHITE POSITIONS //
	for (size_t i = 0;i < 2;i++) {
		temporary = getValidPositions('R', Vector2i(figs->rooks.getPosW()[i].first, figs->rooks.getPosW()[i].second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 2;i++) {
		temporary = getValidPositions('K', Vector2i(figs->knights.getPosW()[i].first, figs->knights.getPosW()[i].second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 2;i++) {
		temporary = getValidPositions('B', Vector2i(figs->bishops.getPosW()[i].first, figs->bishops.getPosW()[i].second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 8;i++) {
		temporary = getValidPositions('P', Vector2i(figs->pawns.getPosW()[i].first, figs->pawns.getPosW()[i].second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < this->figs->queens.getWqueens();i++) {
		temporary = getValidPositions('Q', Vector2i(figs->queens.posWat(i).first, figs->queens.posWat(i).second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	temporary = getValidPositions('1', Vector2i(figs->kings.getPosW().first, figs->kings.getPosW().second));
	whites.insert(whites.end(), temporary.begin(), temporary.end());

	// SECTION BLACK POSITIONS //
	for (size_t i = 0;i < 2;i++) {
		temporary = getValidPositions('r', Vector2i(figs->rooks.getPosB()[i].first, figs->rooks.getPosB()[i].second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 2;i++) {
		temporary = getValidPositions('k', Vector2i(figs->knights.getPosB()[i].first, figs->knights.getPosB()[i].second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 2;i++) {
		temporary = getValidPositions('b', Vector2i(figs->bishops.getPosB()[i].first, figs->bishops.getPosB()[i].second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 8;i++) {
		temporary = getValidPositions('p', Vector2i(figs->pawns.getPosB()[i].first, figs->pawns.getPosB()[i].second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < this->figs->queens.getBqueens();i++) {
		temporary = getValidPositions('q', Vector2i(figs->queens.posBat(i).first, figs->queens.posBat(i).second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	temporary = getValidPositions('2', Vector2i(figs->kings.getPosB().first, figs->kings.getPosB().second));
	blacks.insert(blacks.end(), temporary.begin(), temporary.end());

	//------------------------------------------------------------------------------//
	vector<pair<int, int>>::iterator Wdanger = find(blacks.begin(),blacks.end(),kingWpos);
	vector<pair<int, int>>::iterator Bdanger = find(whites.begin(), whites.end(), kingBpos);

	if (Wdanger != blacks.end()) {
		this->figs->kings.setWinDanger(1);
		this->figs->kings.getKingAtIndex(0).setFillColor(Color(252, 3, 119));
	}
	else {
		this->figs->kings.setWinDanger(0);
		this->figs->kings.getKingAtIndex(0).setFillColor(Color::White);
	}

	if (Bdanger != whites.end()) {
		this->figs->kings.setBinDanger(1);
		this->figs->kings.getKingAtIndex(1).setFillColor(Color(252, 3, 119));
	}
	else {
		this->figs->kings.setBinDanger(0);
		this->figs->kings.getKingAtIndex(1).setFillColor(Color::White);
	};
};

void Game::deleteFigure(int& r,int& c) {

	// condition != "." (TRUE) means that we have moved to a position on the board containing other figure so we have to delete it before updating the board. condition == "." (FALSE) means that we have moved to an empty position and quickly do the 2 else if's below then directly skip to the updateBoardPosition() function.
	if (figs->board[r][c] != '.') {
		char symbol = figs->board[r][c];

		switch (symbol) {
		case('R'):
			this->figs->rooks.getRookWatPos(make_pair(r,c)).setPosition(Vector2f(-100,-100));
			replace(this->figs->rooks.getPosW().begin(), this->figs->rooks.getPosW().end(), make_pair(r, c), make_pair(-10, -10));
			break;
		case('r'):
			this->figs->rooks.getRookBatPos(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			replace(this->figs->rooks.getPosB().begin(), this->figs->rooks.getPosB().end(), make_pair(r, c), make_pair(-10, -10));
			break;
		case('K'):
			this->figs->knights.getKnightWatPos(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			replace(this->figs->knights.getPosW().begin(), this->figs->knights.getPosW().end(), make_pair(r, c), make_pair(-10, -10));
			break;
		case('k'):;
			this->figs->knights.getKnightBatPos(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			replace(this->figs->knights.getPosB().begin(), this->figs->knights.getPosB().end(), make_pair(r, c), make_pair(-10, -10));
			break;
		case('B'):
			this->figs->bishops.getBishopWatPos(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			replace(this->figs->bishops.getPosW().begin(), this->figs->bishops.getPosW().end(), make_pair(r, c), make_pair(-10, -10));
			break;
		case('b'):
			this->figs->bishops.getBishopBatPos(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			replace(this->figs->bishops.getPosB().begin(), this->figs->bishops.getPosB().end(), make_pair(r, c), make_pair(-10, -10));
			break;
		case('P'):
			this->figs->pawns.getPawnWatPos(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			replace(this->figs->pawns.getPosW().begin(), this->figs->pawns.getPosW().end(), make_pair(r, c), make_pair(-10, -10));
			break;
		case('p'):
			this->figs->pawns.getPawnBatPos(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			replace(this->figs->pawns.getPosB().begin(), this->figs->pawns.getPosB().end(), make_pair(r, c), make_pair(-10, -10));
			break;
		case('Q'):
			this->figs->queens.getQueenW(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			replace(this->figs->queens.getPosW().begin(), this->figs->queens.getPosW().end(), make_pair(r, c), make_pair(-10, -10));
			break;
		case('q'):
			this->figs->queens.getQueenB(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			replace(this->figs->queens.getPosB().begin(), this->figs->queens.getPosB().end(), make_pair(r, c), make_pair(-10, -10));
			break;
		}

	} // the extra else if condition below are to delete the pawn taken by en passant move. We need this else if's because en passant move need specific logic which we cant put in the switch case above.
	else if(this->pressedFigSymbol == 'P' && figs->board[r - 1][c] == 'p') { 

		// this is true if we have made en passant move (if there is a black pawn behind our white pawn).

		this->figs->pawns.getPawnBatPos(figs->pawns.getEnPassantPawnPos()).setPosition(Vector2f(-100, -100));

		replace(this->figs->pawns.getPosB().begin(), this->figs->pawns.getPosB().end(), figs->pawns.getEnPassantPawnPos(), make_pair(-10, -10));

		figs->board[r - 1][c] = '.';// setting the position behind our pawn to empty because the updateBoardPosition() can not do it for us when the move is en passant.
	}
	else if (this->pressedFigSymbol == 'p' && figs->board[r + 1][c] == 'P') {

		// this is true if we have made en passant move(if there is a white pawn behind our black pawn).

		this->figs->pawns.getPawnWatPos(figs->pawns.getEnPassantPawnPos()).setPosition(Vector2f(-100, -100));

		replace(this->figs->pawns.getPosW().begin(), this->figs->pawns.getPosW().end(), figs->pawns.getEnPassantPawnPos(), make_pair(-10, -10));

		figs->board[r + 1][c] = '.'; // setting the position behind our pawn to empty because the updateBoardPosition() can not do it for us when the move is en passant.
	}
};

void Game::placeBack(char& symbol,pair<int,int>& oldPos) {

	switch (symbol) {
	case('R'):
		this->figs->rooks.getRookWatPos(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('r'):

		this->figs->rooks.getRookBatPos(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('K'):
		this->figs->knights.getKnightWatPos(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('k'):;
		this->figs->knights.getKnightBatPos(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('B'):
		this->figs->bishops.getBishopWatPos(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('b'):
		this->figs->bishops.getBishopBatPos(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('P'):
		this->figs->pawns.getPawnWatPos(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('p'):
		this->figs->pawns.getPawnBatPos(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('Q'):
		this->figs->queens.getQueenW(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('q'):
		this->figs->queens.getQueenB(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('1'):
		this->figs->kings.getKingWatPos(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('2'):
		this->figs->kings.getKingBatPos(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	}

}

void Game::updateBoardPosition(int& r, int& c) {
	//r stand for row and c stands for column. We need them to know the position of which the player wants to move the draged piece.

	pair<int, int> oldPos = validPositions.front(); // We get the old position of the moved piece.

	this->setDefaultColor();
	this->setOrangeColor(oldPos.first,oldPos.second,r,c);

	switch (this->pressedFigSymbol) {
	case('R'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'R';
		this->figs->rooks.getRookWatPos(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->rooks.getPosW().begin(), figs->rooks.getPosW().end(), oldPos, make_pair(r, c));
		break;
	case('r'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'r';
		this->figs->rooks.getRookBatPos(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->rooks.getPosB().begin(), figs->rooks.getPosB().end(), oldPos, make_pair(r, c));
		break;
	case('K'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'K';
		this->figs->knights.getKnightWatPos(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->knights.getPosW().begin(), figs->knights.getPosW().end(), oldPos, make_pair(r, c));
		break;
	case('k'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'k';
		this->figs->knights.getKnightBatPos(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->knights.getPosB().begin(), figs->knights.getPosB().end(), oldPos, make_pair(r, c));
		break;
	case('B'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'B';
		this->figs->bishops.getBishopWatPos(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->bishops.getPosW().begin(), figs->bishops.getPosW().end(), oldPos, make_pair(r, c));
		break;
	case('b'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'b';
		this->figs->bishops.getBishopBatPos(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->bishops.getPosB().begin(), figs->bishops.getPosB().end(), oldPos, make_pair(r, c));
		break;
	case('P'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'P';
		this->figs->pawns.getPawnWatPos(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->pawns.getPosW().begin(), figs->pawns.getPosW().end(), oldPos, make_pair(r, c));

		if (oldPos.first + 2 == r && oldPos.second == c) {
			// condition checks if the made move puts the pawn 2 postions forward. If TRUE then the pawn is now in En Passant so we raise the indicator and save the pawn position to help us calculate the next moves for the enemy pawns. If FALSE we skip to the else where we lower the indicator saying the pawn is in En Passant danger.

			figs->pawns.raiseEnPassant();
			figs->pawns.setEnPassantPawnPos(make_pair(r, c));
		}
		else {
			figs->pawns.lowerEnPassant();
		}

		if (r == 7) {
			// condition TRUE when WHITE has arrived to the end of the board with out pawn. Now we execute the code below creating the player a Queen.

			this->figs->pawns.getPawnWatPos(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			replace(this->figs->pawns.getPosW().begin(), this->figs->pawns.getPosW().end(), make_pair(r, c), make_pair(-10, -10));

			this->figs->board[r][c] = 'Q';

			this->figs->queens.addWqueen();
			this->figs->queens.getPosW()[figs->queens.getWqueens() - 1] = make_pair(r, c);

			RectangleShape* Q = this->figs->queens.getQueenWatIndex(figs->queens.getWqueens() - 1);

			Q->setSize(Vector2f(90.f, 90.f));
			Q->setTexture(&this->figs->queens.getWhiteTexture());
			Q->setPosition(Vector2f(c * 100 + 5, r * 100 + 5));
		}

		break;
	case('p'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'p';
		this->figs->pawns.getPawnBatPos(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->pawns.getPosB().begin(), figs->pawns.getPosB().end(), oldPos, make_pair(r, c));

		if (oldPos.first - 2 == r && oldPos.second == c) {
			// condition checks if the made move puts the pawn 2 postions forward. If TRUE then the pawn is now in En Passant so we raise the indicator and save the pawn position to help us calculate the next moves for the enemy pawns. If FALSE we skip to the else where we lower the indicator saying the pawn is in En Passant danger.

			figs->pawns.raiseEnPassant();
			figs->pawns.setEnPassantPawnPos(make_pair(r, c));
		}
		else {
			figs->pawns.lowerEnPassant();
		}

		if (r == 0) {
			// condition TRUE when BLACK has arrived to the end of the board with out pawn. Now we execute the code below creating the player a Queen.

			this->figs->pawns.getPawnBatPos(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			replace(this->figs->pawns.getPosB().begin(), this->figs->pawns.getPosB().end(), make_pair(r, c), make_pair(-10, -10));

			this->figs->board[r][c] = 'q';

			this->figs->queens.addBqueen();
			this->figs->queens.getPosB()[figs->queens.getBqueens() - 1] = make_pair(r, c);

			RectangleShape* q = this->figs->queens.getQueenBatIndex(figs->queens.getBqueens() - 1);

			q->setSize(Vector2f(90.f, 90.f));
			q->setTexture(&this->figs->queens.getBlackTexture());
			q->setPosition(Vector2f(c * 100 + 5, r * 100 + 5));
		}

		break;
	case('Q'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'Q';
		this->figs->queens.getQueenW(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->queens.getPosW().begin(), figs->queens.getPosW().end(), oldPos, make_pair(r, c));
		break;
	case('q'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'q';
		this->figs->queens.getQueenB(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->queens.getPosB().begin(), figs->queens.getPosB().end(), oldPos, make_pair(r, c));
		break;
	case('1'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = '1';
		this->figs->kings.getKingWatPos(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		this->figs->kings.getPosW() = make_pair(r, c);

		if (r == 0 && c == 1 && figs->kings.gethasWmoved() == 0) {
			this->figs->board[0][0] = '.';
			this->figs->board[0][2] = 'R';
			this->figs->rooks.getRookWatPos(make_pair(0,0)).setPosition(Vector2f(2 * 100 + 5, 0 * 100 + 5));

			replace(figs->rooks.getPosW().begin(), figs->rooks.getPosW().end(), make_pair(0, 0), make_pair(0, 2));
		}

		if (r == 0 && c == 5 && figs->kings.gethasWmoved() == 0) {
			this->figs->board[0][7] = '.';
			this->figs->board[0][4] = 'R';
			this->figs->rooks.getRookWatPos(make_pair(0, 7)).setPosition(Vector2f(4 * 100 + 5, 0 * 100 + 5));

			replace(figs->rooks.getPosW().begin(), figs->rooks.getPosW().end(), make_pair(0, 7), make_pair(0, 4));
		}
		
		if (this->figs->kings.gethasWmoved() == 0)
			this->figs->kings.sethasWmoved(1);

		break;
	case('2'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = '2';
		this->figs->kings.getKingBatPos(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		this->figs->kings.getPosB() = make_pair(r, c);

		if (r == 7 && c == 1 && figs->kings.gethasBmoved() == 0) {
			this->figs->board[7][0] = '.';
			this->figs->board[7][2] = 'r';
			this->figs->rooks.getRookBatPos(make_pair(7, 0)).setPosition(Vector2f(2 * 100 + 5, 7 * 100 + 5));

			replace(figs->rooks.getPosB().begin(), figs->rooks.getPosB().end(), make_pair(7, 0), make_pair(7, 2));
		}

		if (r == 7 && c == 5 && figs->kings.gethasBmoved() == 0) {
			this->figs->board[7][7] = '.';
			this->figs->board[7][4] = 'r';
			this->figs->rooks.getRookBatPos(make_pair(7, 7)).setPosition(Vector2f(4 * 100 + 5, 7 * 100 + 5));

			replace(figs->rooks.getPosB().begin(), figs->rooks.getPosB().end(), make_pair(7, 7), make_pair(7, 4));
		}

		if (this->figs->kings.gethasBmoved() == 0)
			this->figs->kings.sethasBmoved(1);

		break;
	}

};

void Game::glueFigToMouse(char& symbol) {

	updateMousePos();

	switch (this->pressedFigSymbol) {
	case('R'):
		this->figs->rooks.getRookWatPos(validPositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('r'):
		this->figs->rooks.getRookBatPos(validPositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('K'):
		this->figs->knights.getKnightWatPos(validPositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('k'):
		this->figs->knights.getKnightBatPos(validPositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('B'):
		this->figs->bishops.getBishopWatPos(validPositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('b'):
		this->figs->bishops.getBishopBatPos(validPositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('P'):
		this->figs->pawns.getPawnWatPos(validPositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('p'):
		this->figs->pawns.getPawnBatPos(validPositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('Q'):
		this->figs->queens.getQueenW(validPositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('q'):
		this->figs->queens.getQueenB(validPositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('1'):
		this->figs->kings.getKingWatPos(validPositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	case('2'):
		this->figs->kings.getKingBatPos(validPositions.front()).setPosition(Vector2f(mousePosWindow.x - 45, mousePosWindow.y - 45));
		break;
	}
};

void Game::mouseIndex(int& x,int& y,Vector2i& mousePos) {
	bool breakFor = 0;

	for (size_t r = 0;r < 8;r++) {
		for (size_t c = 0;c < 8;c++) {
			if (mousePos.x >= c * 100 && mousePos.y >= r * 100 && mousePos.x < (c + 1) * 100 && mousePos.y < (r + 1) * 100) {
				x = r; y = c; breakFor = 1;
				break;
			}
		}
		if (breakFor)
			break;
	}

};

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

	this->window = new RenderWindow(VideoMode(800, 800), "Classic Chess", Style::Titlebar | Style::Close,settings);

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

void Game::setOrangeColor(int& oldPosX, int& oldPosY, int& newPosX, int& newPosY)
{
	this->lastMoveTo = make_pair(newPosX,newPosY);
	this->lastMoveFrom = make_pair(oldPosX, oldPosY);
	RectangleShape* box = this->chessBoard->getBoardBox(newPosX, newPosY);

	this->lastMoveToColor = box->getFillColor();
	box->setFillColor(Color(235, 212, 136));

	box = this->chessBoard->getBoardBox(oldPosX, oldPosY);

	this->lastMoveFromColor = box->getFillColor();
	box->setFillColor(Color(235, 212, 136));
}

void Game::setDefaultColor()
{
	RectangleShape* box = this->chessBoard->getBoardBox(lastMoveTo.first, lastMoveTo.second);
    box->setFillColor(lastMoveToColor);

	box = this->chessBoard->getBoardBox(lastMoveFrom.first, lastMoveFrom.second);
	box->setFillColor(lastMoveFromColor);
}
;