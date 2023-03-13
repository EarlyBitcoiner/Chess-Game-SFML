
#include "Game.h"
#include "Board.h"
#include "Figures.h"

#include <set>

void Game::poolEvents() {

	while (this->window->pollEvent(mainEv)) { // we stay here until all events are gone through.

		if (this->mainEv.type == Event::Closed) {
			this->window->close(); break;
		}  // this condition is true only if we press the X of the window to close it. 

		if (this->mainEv.type == Event::MouseButtonPressed && this->mainEv.mouseButton.button == Mouse::Left) {

			this->mousePosWindow.x = mainEv.mouseButton.x;
			this->mousePosWindow.y = mainEv.mouseButton.y;

			int r=0, c=0;

			mouseIndex(r, c, mousePosWindow); // returns the board index on which the mouse happen to be when called by assigning it in r and c.

			if (playerTurn == 'W' && (figs->board[r][c] >= 98 && figs->board[r][c] <= 122 || figs->board[r][c]== '2'))
				break;
			else if (playerTurn == 'B' && (figs->board[r][c] >= 65 && figs->board[r][c] <= 90 || figs->board[r][c] == '1'))
				break;

			if (figs->board[r][c] != '.') {
				this->pressedFig = 1; // by setting the value 1 we now know that the player pressed on a figure and will maybe drag it.
				this->pressedFigSymbol = figs->board[r][c]; //we get the symbol to know with what figure we have to work.
				this->validPositions = getValidPositions(figs->board[r][c], Vector2i(r, c)); // we get the valid position on which the pressed figure can move.
			}

		}

		if (this->mainEv.type == Event::MouseButtonReleased && this->mainEv.mouseButton.button == Mouse::Left && pressedFig == 1) {
			
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

					if (isNextMoveValid(r,c,validPositions[0])) {

						deleteFigure(r, c); // removes a figure drawable capabilities if taken by another figure.(just sets the position to -100,-100)
						updateBoardPosition(r, c); // updates the board based on the moved figure and renders the figure on its new place.

						isKingInDanger();

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
		}
		else if (this->pressedFig == 1) { // We constantly go through this [else if] when we are dragging a figure.
			glueFigToMouse(this->pressedFigSymbol); // glues the pressed figure to the mouse cursor until the button is released.
		}
	}

}

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

void Game::update() {

	poolEvents();
	//cout << "mouse is at " << Mouse::getPosition(*window).x << " " << Mouse::getPosition(*window).y << endl;
}

void Game::render() {
	// Erase drawings
	window->clear();
	
	// Draw Board
	for (size_t r = 0;r < 8;r++) {
		for (size_t c = 0;c < 8;c++) {
			window->draw(this->chessBoard->board[r][c]);
		}
	}

	// Draw Figures
	for (size_t i = 0;i < figs->queens.Wqueens;i++) {
		window->draw(figs->queens.queenW[i]);
	}

	for (size_t i = 0;i < figs->queens.Bqueens;i++) {
		window->draw(figs->queens.queenB[i]);
	}

	for (size_t i = 0;i < 2;i++) {
		window->draw(figs->kings.king[i]);

		window->draw(figs->rooks.rookW[i]);
		window->draw(figs->rooks.rookB[i]);

		window->draw(figs->bishops.bishopW[i]);
		window->draw(figs->bishops.bishopB[i]);

		window->draw(figs->knights.knightW[i]);
		window->draw(figs->knights.knightB[i]);
	}

	for (size_t i = 0;i < 8;i++) {
		window->draw(figs->pawns.pawnW[i]);
		window->draw(figs->pawns.pawnB[i]);
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

bool Game::isNextMoveValid(int r, int c, pair<int,int> pos) {
	char boardCopy[8][8];

	for (size_t j = 0;j < 8;j++) {
		for (size_t k = 0;k < 8;k++) {
			boardCopy[j][k] = figs->board[j][k];
		}
	}

	boardCopy[r][c] = figs->board[pos.first][pos.second];
	boardCopy[pos.first][pos.second] = '.';

	vector <pair<int, int>> current; 

	pair<int, int> KingW;
	pair<int, int> KingB;

	(boardCopy[r][c] == '1') ? KingW = make_pair(r, c) : KingW = figs->kings.posW;
	(boardCopy[r][c] == '2') ? KingB = make_pair(r, c) : KingB = figs->kings.posB;

	for (int j = 0;j < 8;j++) {
		for (int k = 0;k < 8;k++) {
			if (boardCopy[j][k] != '.') {
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

				if (current.size() > 1) {
					if (find(current.begin() + 1, current.end(), KingW) != current.end() && playerTurn == 'W') {
						return false;
					}
					else if(find(current.begin() + 1, current.end(), KingW) != current.end() && playerTurn == 'W' && figs->kings.inDangerW == 1) {
						return false;
					}
					else if (find(current.begin() + 1, current.end(), KingB) != current.end() && playerTurn == 'B') {
						return false;
					}
					else if (find(current.begin() + 1, current.end(), KingB) != current.end() && playerTurn == 'B' && figs->kings.inDangerB == 1) {
						return false;
					}
				}

				current.clear();
			}
		}
	}

	return true;
};

void Game::isKingInDanger() {
	pair<int, int> kingWpos = this->figs->kings.posW;
	pair<int, int> kingBpos = this->figs->kings.posB;

	vector<pair<int, int>> whites;
	vector<pair<int, int>> blacks;

	vector<pair<int, int>> temporary;

	//  SECTION WHITE POSITIONS //
	for (size_t i = 0;i < 2;i++) {
		temporary = getValidPositions('R', Vector2i(figs->rooks.posW[i].first, figs->rooks.posW[i].second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 2;i++) {
		temporary = getValidPositions('K', Vector2i(figs->knights.posW[i].first, figs->knights.posW[i].second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 2;i++) {
		temporary = getValidPositions('B', Vector2i(figs->bishops.posW[i].first, figs->bishops.posW[i].second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 8;i++) {
		temporary = getValidPositions('P', Vector2i(figs->pawns.posW[i].first, figs->pawns.posW[i].second));
		whites.insert(whites.end(), temporary.begin(), temporary.end());
	}

	temporary = getValidPositions('Q', Vector2i(figs->queens.posW[0].first, figs->queens.posW[0].second));
	whites.insert(whites.end(), temporary.begin(), temporary.end());

	temporary = getValidPositions('1', Vector2i(figs->kings.posW.first, figs->kings.posW.second));
	whites.insert(whites.end(), temporary.begin(), temporary.end());

	// SECTION BLACK POSITIONS //
	for (size_t i = 0;i < 2;i++) {
		temporary = getValidPositions('r', Vector2i(figs->rooks.posB[i].first, figs->rooks.posB[i].second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 2;i++) {
		temporary = getValidPositions('k', Vector2i(figs->knights.posB[i].first, figs->knights.posB[i].second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 2;i++) {
		temporary = getValidPositions('b', Vector2i(figs->bishops.posB[i].first, figs->bishops.posB[i].second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	for (size_t i = 0;i < 8;i++) {
		temporary = getValidPositions('p', Vector2i(figs->pawns.posB[i].first, figs->pawns.posB[i].second));
		blacks.insert(blacks.end(), temporary.begin(), temporary.end());
	}

	temporary = getValidPositions('q', Vector2i(figs->queens.posB[0].first, figs->queens.posB[0].second));
	blacks.insert(blacks.end(), temporary.begin(), temporary.end());

	temporary = getValidPositions('2', Vector2i(figs->kings.posB.first, figs->kings.posB.second));
	blacks.insert(blacks.end(), temporary.begin(), temporary.end());

	//------------------------------------------------------------------------------//
	vector<pair<int, int>>::iterator Wdanger = find(blacks.begin(),blacks.end(),kingWpos);
	vector<pair<int, int>>::iterator Bdanger = find(whites.begin(), whites.end(), kingBpos);

	if (Wdanger != blacks.end())
		this->figs->kings.inDangerW = 1;
	else
		this->figs->kings.inDangerW = 0;

	if (Bdanger != whites.end())
		this->figs->kings.inDangerB = 1;
	else
		this->figs->kings.inDangerB = 0;
};

void Game::deleteFigure(int& r,int& c) {

	if (figs->board[r][c] != '.') {
		char symbol = figs->board[r][c];

		switch (symbol) {
		case('R'):
			this->figs->rooks.getRookW(make_pair(r,c)).setPosition(Vector2f(-100,-100));
			break;
		case('r'):

			this->figs->rooks.getRookB(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			break;
		case('K'):
			this->figs->knights.getKnightW(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			break;
		case('k'):;
			this->figs->knights.getKnightB(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			break;
		case('B'):
			this->figs->bishops.getBishopW(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			break;
		case('b'):
			this->figs->bishops.getBishopB(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			break;
		case('P'):
			this->figs->pawns.getPawnW(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			break;
		case('p'):
			this->figs->pawns.getPawnB(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			break;
		case('Q'):
			this->figs->queens.getQueenW(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			break;
		case('q'):
			this->figs->queens.getQueenB(make_pair(r, c)).setPosition(Vector2f(-100, -100));
			break;
		}
	}
};

void Game::placeBack(char& symbol,pair<int,int>& oldPos) {

	switch (symbol) {
	case('R'):
		this->figs->rooks.getRookW(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('r'):

		this->figs->rooks.getRookB(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('K'):
		this->figs->knights.getKnightW(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('k'):;
		this->figs->knights.getKnightB(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('B'):
		this->figs->bishops.getBishopW(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('b'):
		this->figs->bishops.getBishopB(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('P'):
		this->figs->pawns.getPawnW(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('p'):
		this->figs->pawns.getPawnB(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('Q'):
		this->figs->queens.getQueenW(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('q'):
		this->figs->queens.getQueenB(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('1'):
		this->figs->kings.getKingW(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	case('2'):
		this->figs->kings.getKingB(validPositions.front()).setPosition(Vector2f(oldPos.second * 100 + 5, oldPos.first * 100 + 5));
		break;
	}

}

void Game::updateBoardPosition(int& r, int& c) {
	//r stand for row and c stands for column.

	pair<int, int> oldPos = validPositions.front();

	switch (this->pressedFigSymbol) {
	case('R'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'R';
		this->figs->rooks.getRookW(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->rooks.posW.begin(), figs->rooks.posW.end(), oldPos, make_pair(r, c));
		break;
	case('r'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'r';
		this->figs->rooks.getRookB(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->rooks.posB.begin(), figs->rooks.posB.end(), oldPos, make_pair(r, c));
		break;
	case('K'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'K';
		this->figs->knights.getKnightW(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->knights.posW.begin(), figs->knights.posW.end(), oldPos, make_pair(r, c));
		break;
	case('k'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'k';
		this->figs->knights.getKnightB(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->knights.posB.begin(), figs->knights.posB.end(), oldPos, make_pair(r, c));
		break;
	case('B'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'B';
		this->figs->bishops.getBishopW(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->bishops.posW.begin(), figs->bishops.posW.end(), oldPos, make_pair(r, c));
		break;
	case('b'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'b';
		this->figs->bishops.getBishopB(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->bishops.posB.begin(), figs->bishops.posB.end(), oldPos, make_pair(r, c));
		break;
	case('P'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'P';
		this->figs->pawns.getPawnW(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->pawns.posW.begin(), figs->pawns.posW.end(), oldPos, make_pair(r, c));

		if (r == 7) {
			this->figs->board[r][c] = 'Q';

			this->figs->pawns.getPawnW(make_pair(r, c)).setPosition(Vector2f(-100, -100));

			this->figs->queens.Wqueens++;
			this->figs->queens.posW[figs->queens.Wqueens - 1] = make_pair(r, c);
			this->figs->queens.queenW[figs->queens.Wqueens - 1].setSize(Vector2f(90.f, 90.f));
			this->figs->queens.queenW[figs->queens.Wqueens - 1].setTexture(&this->figs->queens.texture[0]);
			this->figs->queens.queenW[figs->queens.Wqueens - 1].setPosition(Vector2f(c * 100 + 5, r * 100 + 5));
		}

		break;
	case('p'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'p';
		this->figs->pawns.getPawnB(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->pawns.posB.begin(), figs->pawns.posB.end(), oldPos, make_pair(r, c));

		if (r == 0) {
			this->figs->board[r][c] = 'q';

			this->figs->pawns.getPawnB(make_pair(r, c)).setPosition(Vector2f(-100, -100));

			this->figs->queens.Bqueens++;
			this->figs->queens.posB[figs->queens.Bqueens - 1] = make_pair(r, c);
			this->figs->queens.queenB[figs->queens.Bqueens - 1].setSize(Vector2f(90.f, 90.f));
			this->figs->queens.queenB[figs->queens.Bqueens - 1].setTexture(&this->figs->queens.texture[1]);
			this->figs->queens.queenB[figs->queens.Bqueens - 1].setPosition(Vector2f(c * 100 + 5, r * 100 + 5));
		}

		break;
	case('Q'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'Q';
		this->figs->queens.getQueenW(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->queens.posW.begin(), figs->queens.posW.end(), oldPos, make_pair(r, c));
		break;
	case('q'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = 'q';
		this->figs->queens.getQueenB(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		replace(figs->queens.posB.begin(), figs->queens.posB.end(), oldPos, make_pair(r, c));
		break;
	case('1'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = '1';
		this->figs->kings.getKingW(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		this->figs->kings.posW = make_pair(r, c);

		if (r == 0 && c == 1 && figs->kings.hasMovedW == 0) {
			this->figs->board[0][0] = '.';
			this->figs->board[0][2] = 'R';
			this->figs->rooks.getRookW(make_pair(0,0)).setPosition(Vector2f(2 * 100 + 5, 0 * 100 + 5));

			replace(figs->rooks.posW.begin(), figs->rooks.posW.end(), make_pair(0,0), make_pair(0, 2));
		}

		if (r == 0 && c == 5 && figs->kings.hasMovedW == 0) {
			this->figs->board[0][7] = '.';
			this->figs->board[0][4] = 'R';
			this->figs->rooks.getRookW(make_pair(0, 7)).setPosition(Vector2f(4 * 100 + 5, 0 * 100 + 5));

			replace(figs->rooks.posW.begin(), figs->rooks.posW.end(), make_pair(0, 7), make_pair(0, 4));
		}
		
		if (this->figs->kings.hasMovedW == 0)
			this->figs->kings.hasMovedW = 1;

		break;
	case('2'):
		this->figs->board[oldPos.first][oldPos.second] = '.';
		this->figs->board[r][c] = '2';
		this->figs->kings.getKingB(validPositions.front()).setPosition(Vector2f(c * 100 + 5, r * 100 + 5));

		this->figs->kings.posB = make_pair(r, c);

		if (r == 7 && c == 1 && figs->kings.hasMovedB == 0) {
			this->figs->board[7][0] = '.';
			this->figs->board[7][2] = 'r';
			this->figs->rooks.getRookB(make_pair(7, 0)).setPosition(Vector2f(2 * 100 + 5, 7 * 100 + 5));

			replace(figs->rooks.posB.begin(), figs->rooks.posB.end(), make_pair(7, 0), make_pair(7, 2));
		}

		if (r == 7 && c == 5 && figs->kings.hasMovedB == 0) {
			this->figs->board[7][7] = '.';
			this->figs->board[7][4] = 'r';
			this->figs->rooks.getRookB(make_pair(7, 7)).setPosition(Vector2f(4 * 100 + 5, 7 * 100 + 5));

			replace(figs->rooks.posB.begin(), figs->rooks.posB.end(), make_pair(7, 7), make_pair(7, 4));
		}

		if (this->figs->kings.hasMovedB == 0)
			this->figs->kings.hasMovedB = 1;

		break;
	}

};

void Game::glueFigToMouse(char& symbol) {

	updateMousePos();

	switch (this->pressedFigSymbol) {
	case('R'):
		this->figs->rooks.getRookW(validPositions.front()).setPosition(Vector2f(mousePosWindow.x, mousePosWindow.y));
		break;
	case('r'):
		this->figs->rooks.getRookB(validPositions.front()).setPosition(Vector2f(mousePosWindow.x, mousePosWindow.y));
		break;
	case('K'):
		this->figs->knights.getKnightW(validPositions.front()).setPosition(Vector2f(mousePosWindow.x, mousePosWindow.y));
		break;
	case('k'):
		this->figs->knights.getKnightB(validPositions.front()).setPosition(Vector2f(mousePosWindow.x, mousePosWindow.y));
		break;
	case('B'):
		this->figs->bishops.getBishopW(validPositions.front()).setPosition(Vector2f(mousePosWindow.x, mousePosWindow.y));
		break;
	case('b'):
		this->figs->bishops.getBishopB(validPositions.front()).setPosition(Vector2f(mousePosWindow.x, mousePosWindow.y));
		break;
	case('P'):
		this->figs->pawns.getPawnW(validPositions.front()).setPosition(Vector2f(mousePosWindow.x, mousePosWindow.y));
		break;
	case('p'):
		this->figs->pawns.getPawnB(validPositions.front()).setPosition(Vector2f(mousePosWindow.x, mousePosWindow.y));
		break;
	case('Q'):
		this->figs->queens.getQueenW(validPositions.front()).setPosition(Vector2f(mousePosWindow.x, mousePosWindow.y));
		break;
	case('q'):
		this->figs->queens.getQueenB(validPositions.front()).setPosition(Vector2f(mousePosWindow.x, mousePosWindow.y));
		break;
	case('1'):
		this->figs->kings.getKingW(validPositions.front()).setPosition(Vector2f(mousePosWindow.x, mousePosWindow.y));
		break;
	case('2'):
		this->figs->kings.getKingB(validPositions.front()).setPosition(Vector2f(mousePosWindow.x, mousePosWindow.y));
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

};

void Game::createVar() {
	this->window = nullptr;
	this->chessBoard = new Board;
	this->figs = new Figures;
};

void Game::setWindow() {
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	this->window = new RenderWindow(VideoMode(1100, 900), "Classic Chess", Style::Titlebar | Style::Close,settings);

	window->setFramerateLimit(144);
};

// Destructor
Game::~Game() {
	delete window;
};