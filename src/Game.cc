#include "Game.h"

using namespace std;

Game::Game(string w, string b, ScoreBoard *sb): tracker{new Tracker()}, scoreBoard{sb} {
	this->chessBoard = new ChessBoard(8);
	if (w == "human") {
		this->whitePlayer = new Human(this->chessBoard, PieceColor::White);
	}
	if (b == "human") {
		this->blackPlayer = new Human(this->chessBoard, PieceColor::Black);
	}
	if (w == "computer1") {
		this->whitePlayer = new Computer(this->chessBoard, PieceColor::White, 1);
	}
	if (w == "computer2") {
		this->whitePlayer = new Computer(this->chessBoard, PieceColor::White, 2);
	}
	if (w == "computer3") {
		this->whitePlayer = new Computer(this->chessBoard, PieceColor::White, 3);
	}
	if (w == "computer4") {
		this->whitePlayer = new Computer(this->chessBoard, PieceColor::White, 4);
	}
	if (b == "computer1") {
		this->blackPlayer = new Computer(this->chessBoard, PieceColor::Black, 1);
	}
	if (b == "computer2") {
		this->blackPlayer = new Computer(this->chessBoard, PieceColor::Black, 2);
	}
	if (b == "computer3") {
		this->blackPlayer = new Computer(this->chessBoard, PieceColor::Black, 3);
	}
	if (b == "computer4") {
		this->blackPlayer = new Computer(this->chessBoard, PieceColor::Black, 4);
	}
	this->blackPlayer->setTracker(this->tracker);
	this->whitePlayer->setTracker(this->tracker);
	this->blackPlayer->setOpponent(this->whitePlayer);
	this->whitePlayer->setOpponent(this->blackPlayer);
}

bool Game::draw(){
	return this->whitePlayer->getActivePieces().size() == 1 && this->blackPlayer->getActivePieces().size() == 1;
}

void Game::setup() {
	this->printChessBoard();
	string operation;
	char piece;
	string position;
	string colour;
	while (cin >> operation) {
		if (cin.eof()) {
			break;
		}
		if (operation == "+") {
			cin >> piece;
			cin >> position;
			Piece *p;
			switch (piece) {
			case 'K':
				p = new King(PieceColor::White);
				this->whitePlayer->registerPiece(p);
				break;
			case 'k':
				p = new King(PieceColor::Black);
				this->blackPlayer->registerPiece(p);
				break;
			case 'Q':
				p = new Queen(PieceColor::White);
				this->whitePlayer->registerPiece(p);
				break;
			case 'q':
				p = new Queen(PieceColor::Black);
				this->blackPlayer->registerPiece(p);
				break;
			case 'B':
				p = new Bishop(PieceColor::White);
				this->whitePlayer->registerPiece(p);
				break;
			case 'b':
				p = new Bishop(PieceColor::Black);
				this->blackPlayer->registerPiece(p);
				break;
			case 'N':
				p = new Knight(PieceColor::White);
				this->whitePlayer->registerPiece(p);
				break;
			case 'n':
				p = new Knight(PieceColor::Black);
				this->blackPlayer->registerPiece(p);
				break;
			case 'R':
				p = new Rook(PieceColor::White);
				this->whitePlayer->registerPiece(p);
				break;
			case 'r':
				p = new Rook(PieceColor::Black);
				this->blackPlayer->registerPiece(p);
				break;
			case 'P':
				p = new Pawn(PieceColor::White);
				this->whitePlayer->registerPiece(p);
				break;
			case 'p':
				p = new Pawn(PieceColor::Black);
				this->blackPlayer->registerPiece(p);
				break;
			}
			if (p->subType() == PieceType::King) {
				if (p->getColor() == PieceColor::White
						&& this->whitePlayer->getKing()) {
					cout << "White player already has a king!" << endl;
					continue;
				}
				if (p->getColor() == PieceColor::Black
						&& this->blackPlayer->getKing()) {
					cout << "Black player already has a king!" << endl;
					continue;
				}
			}
			if (this->chessBoard->hasPiece(position)) {
				this->chessBoard->getPiece(position)->getColor() == PieceColor::White ?
						this->whitePlayer->removePiece(position) :
						this->blackPlayer->removePiece(position);
			}
			p->getColor() == PieceColor::White ?
					this->whitePlayer->putPiece(position, p) :
					this->blackPlayer->putPiece(position, p);
			this->printChessBoard();
		} else if (operation == "-") {
			cin >> position;
			if (this->chessBoard->hasPiece(position)) {
				this->chessBoard->getPiece(position)->getColor() == PieceColor::White ?
						this->whitePlayer->removePiece(position) :
						this->blackPlayer->removePiece(position);
			}
			this->printChessBoard();
		} else if (operation == "=") {
			cin >> colour;
			if (colour == "white") {
				this->whosturn = PieceColor::White;
			}
			if (colour == "black") {
				this->whosturn = PieceColor::Black;
			}
		} else if (operation == "done") {
			auto isInvalidPawnRow = [this](int row) {
				return (row == 0 || row == this->chessBoard->getSize() - 1);
			};
			bool hasInvalidPawn = false;
			for (auto &piece : this->blackPlayer->getActivePieces()) {
				if (piece->subType() == PieceType::Pawn) {
					if (isInvalidPawnRow(Position(piece->getPosition()).row)) {
						hasInvalidPawn = true;
						break;
					}
				}
			}
			for (auto &piece : this->whitePlayer->getActivePieces()) {
				if (piece->subType() == PieceType::Pawn) {
					if (isInvalidPawnRow(Position(piece->getPosition()).row)) {
						hasInvalidPawn = true;
						break;
					}
				}
			}
			if (hasInvalidPawn) {
				cout << "Unable to start game since at least pawn cannot be in the first or last row." << endl;
				continue;
			}
			if (this->whitePlayer->getKing() && this->blackPlayer->getKing()) {
				if (this->whitePlayer->isChecked() || this->blackPlayer->isChecked()) {
					cout << "Unable to start game since at least one player is checked." << endl;
					continue;
				}
			} else {
				cout << "Unable to start game since at least one player does not have king." << endl;
				continue;
			}
			return;
		} else {
			cout << "Invalid command." << endl;
			continue;
		}
	}
}

void Game::start() {
	cout << "Game start!" << endl;
	bool whiteComputerTryMove = false;
	bool blackComputerTryMove = false;
	while (true) {
		if (this->whitePlayer->stalemate() || this->blackPlayer->stalemate()) {
			cout << "Stalemate!" << endl;
			this->scoreBoard->incrScore(whitePlayer->getColor(), 0.5);
			this->scoreBoard->incrScore(blackPlayer->getColor(), 0.5);
			break;
		}
		if (this->draw()) {
			cout << "Draw." <<endl;
			this->scoreBoard->incrScore(whitePlayer->getColor(), 0.5);
			this->scoreBoard->incrScore(blackPlayer->getColor(), 0.5);
			break;
		}
		Player *currentPlayer = ((this->whosturn == PieceColor::White) ? this->whitePlayer : this->blackPlayer);
		if (currentPlayer->isCheckmated()) {
			cout << "Checkmate! " << ((currentPlayer->getColor() == PieceColor::White) ? "Black" : "White") << " wins!" << endl;
			this->scoreBoard->incrScore(currentPlayer->getOpponent()->getColor(), 1);
			break;
		}
		if (currentPlayer->resigned()) {
			cout << ((currentPlayer->getColor() == PieceColor::White) ? "Black" : "White") << " wins!" << endl;
			this->scoreBoard->incrScore(currentPlayer->getOpponent()->getColor(), 1);
			break;
		}
		if (currentPlayer->subType() == PlayerType::Computer) {
			bool tryMove = currentPlayer->getColor() == PieceColor::White ? whiteComputerTryMove : blackComputerTryMove;
			if (!tryMove) {
				string command;
				cin >> command;
				if (cin.eof()) {
					break;
				}
				if (command == "move") {

				} else {
					cout << "Invalid command." << endl;
					continue;
				}
			}
			try {
				static_cast<Computer *>(currentPlayer)->playNextMove();
				this->whosturn = currentPlayer->getOpponent()->getColor();
				currentPlayer->getColor() == PieceColor::White ? whiteComputerTryMove = false : blackComputerTryMove = false;
				this->printChessBoard();
			} catch (CheckedMove &e) {
				this->whitePlayer->undo();
				this->whosturn = currentPlayer->getColor();
				currentPlayer->getColor() == PieceColor::White ? whiteComputerTryMove = true : blackComputerTryMove = true;
				continue;
			}
		} else {
			string command;
			string source;
			string target;
			cin >> command;
			if (cin.eof()) {
				break;
			}
			if (command == "move") {
				cin >> source;
				cin >> target;
				try {
					static_cast<Human *>(currentPlayer)->playNextMove(source, target);
				} catch (SourceOutOfRange &e) {
					cout << source << " is out of range!" << endl;
					this->whosturn = currentPlayer->getColor();
					continue;
				} catch (PieceDoesNotExist &e) {
					cout << source << " does not exist!" << endl;
					this->whosturn = currentPlayer->getColor();
					continue;
				} catch (MovingEnemyPiece &e) {
					cout << source << " is an enemy piece!" << endl;
					this->whosturn = currentPlayer->getColor();
					continue;
				} catch (CapturingAllyPiece &e) {
					cout << target << " is an ally piece!" << endl;
					this->whosturn = currentPlayer->getColor();
					continue;
				} catch (TargetOutOfRange &e) {
					cout << target << " is out of range!" << endl;
					this->whosturn = currentPlayer->getColor();
					continue;
				} catch (SamePositionMove &e) {
					cout << "you did not move!" << endl;
					this->whosturn = currentPlayer->getColor();
					continue;
				} catch (IllegalMove &e) {
					cout << target << " is an illegal move!" << endl;
					this->whosturn = currentPlayer->getColor();
					continue;
				} catch (CheckedMove &e) {
					cout << "your king will be checked!" << endl;
					currentPlayer->undo();
					this->whosturn = currentPlayer->getColor();
					continue;
				}
				whosturn = currentPlayer->getOpponent()->getColor();
				if (currentPlayer->getOpponent()->isChecked()) {
					cout << ((currentPlayer->getColor() == PieceColor::White) ? "Black" : "White") << " is in check." << endl;
				}
				this->printChessBoard();
			} else if (command == "undo") {
				if (this->tracker->length() >= 2) {
					try {
						currentPlayer->undo();
						currentPlayer->undo();
						this->printChessBoard();
					} catch (NoHistoryStored &e) {
						cout << "Cannot undo anymore." << endl;
					}
				} else {
					cout << "Cannot undo anymore." << endl;
				}
			} else if (command == "resign") {
				currentPlayer->resign();
			} else {
				cout << "Invalid command." << endl;
			}
		}
	}
}

Game::~Game() {
	vector<Piece*> whitePlayerPieces = whitePlayer->getPieces();
	vector<Piece*> blackPlayerPieces = blackPlayer->getPieces();
	delete whitePlayer;
	delete blackPlayer;
	for (auto *p: whitePlayerPieces) {
		delete p;
	}
	for (auto *p: blackPlayerPieces) {
		delete p;
	}
	delete this->tracker;
	delete chessBoard;
}

void Game::printChessBoard() {
	cout << *(this->chessBoard);
}
