#include <vector>
#include <iostream>
#include "ChessBoard.h"
#include "TextDisplay.h"
#include "Position.h"
#include "Cell.h"
#include "Piece.h"

using namespace std;

ChessBoard::ChessBoard(int size): size{size} {
	for (int i = 0; i < size; ++i) {
		grid.emplace_back(vector<Cell>());
		for (int j = 0; j < size; ++j) {
			grid[i].emplace_back(Cell(i, j, (i + j) % 2 == 0 ? CellColor::Black : CellColor::White));
		}
	}
	td = new TextDisplay(size, &this->grid);
#ifdef GRAPHICS
	gd = new GraphicsDisplay(size, &this->grid, 100);
#endif
}

ChessBoard::~ChessBoard() {
	delete td;
#ifdef GRAPHICS
	delete gd;
#endif
}

int ChessBoard::getSize() {
	return this->size;
}

bool ChessBoard::hasPiece(int r, int c) {
	if (!(r >= 0 && r < size && c >= 0 && c < size)) return false;
	return this->grid[r][c].hasPiece();
}

bool ChessBoard::hasPiece(string posn) {
	return this->hasPiece(Position(posn).row, Position(posn).col);
}

bool ChessBoard::inRange(int r, int c){
 	return (r >= 0 && r < this->getSize()) && (c >= 0 && c < this->getSize());
}

Piece *ChessBoard::getPiece(int r, int c) {
	return this->grid[r][c].getPiece();
}

Piece *ChessBoard::getPiece(string posn) {
	return this->getPiece(Position(posn).row, Position(posn).col);
}

void ChessBoard::putPiece(int r, int c, Piece *p) {
	this->grid[r][c].putPiece(p);
	p->setChessBoard(this);
}

void ChessBoard::putPiece(string posn, Piece *p) {
	this->putPiece(Position(posn).row, Position(posn).col, p);
}

void ChessBoard::removePiece(int r, int c) {
	this->grid[r][c].removePiece();
}

void ChessBoard::removePiece(string posn) {
	this->removePiece(Position(posn).row, Position(posn).col);
}

void ChessBoard::movePiece(int sr, int sc, int tr, int tc) {
	Piece *p = this->getPiece(sr, sc);
	this->removePiece(sr, sc);
	if (this->hasPiece(tr, tc)) {
		this->removePiece(tr, tc);
	}
	this->putPiece(tr, tc, p);
	auto pos = Position(sr, sc);
	p->lastPositions.emplace_back(pos);
}

void ChessBoard::movePiece(string source, string target) {
	this->movePiece(Position(source).row, Position(source).col,
			        Position(target).row, Position(target).col);
}

vector<Piece*> ChessBoard::getActivePieces(PieceColor color) {
	vector<Piece*> result {};
	for (auto &r: this->grid) {
		for (auto &c: r) {
			if (c.hasPiece() && c.getPiece()->getColor() == color) {
				result.emplace_back(c.getPiece());
			}
		}
	}
	return result;
}

vector<Position> ChessBoard::getCaptureRange(PieceColor color) {
	vector<Position> captureRange;
	for (auto piece: this->getActivePieces(color)) {
		bool unique = true;
		for (auto pos: piece->getAllAvailableMoves()) {
			for (auto &p: captureRange) {
				if (p == pos) {
					unique = false;
					break;
				}
			}
			if (unique) captureRange.emplace_back(pos);
		}
	}
	return captureRange;
}

ostream &operator<< (ostream &out, ChessBoard &c) {
#ifdef GRAPHICS
	c.gd->refresh();
#endif
	return out << *(c.td);
}

