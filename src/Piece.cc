#include "Piece.h"

using namespace std;

Piece::Piece(PieceColor c): color{c} {}

Piece::~Piece() {}

void Piece::setPosition(int r, int c) {
	this->r = r;
	this->c = c;
}

string Piece::getPosition() {
	return Position(r, c).toString();
}

vector<Position> Piece::getAllAvailableMoves() {
	vector<Position> moves;
	moves = this->getCaptureMoves();
	for (auto m: this->getNormalMoves()) {
		moves.emplace_back(m);
	}
	return moves;
}


vector<Position> Piece::getAvoidCaptureMoves() {
	PieceColor color = (this->getColor() == PieceColor::White) ? PieceColor::Black : PieceColor::White;
	auto enemyCaptureRange = this->getChessBoard()->getCaptureRange(color);
	vector<Position> avoidCaptureMoves;
	for (auto p: this->getAllAvailableMoves()) {
		bool found = false;
		for (auto q: enemyCaptureRange){
			if (p == q) {
				found = true;
				break;
			}
		}
		if (!found) avoidCaptureMoves.emplace_back(p);
	}
	return avoidCaptureMoves;
}

PieceColor Piece::getColor() {
	return this->color;
}

void Piece::setChessBoard(ChessBoard *b) {
	this->chessBoard = b;
}

ChessBoard* Piece::getChessBoard() {
	return this->chessBoard;
}

bool Piece::onChessBoard() {
	return this->_onChessBoard;
}

int Piece::getRow() {
	return this->r;
}

int Piece::getCol() {
	return this->c;
}

bool Piece::moved() {
	return !this->lastPositions.empty();
}
