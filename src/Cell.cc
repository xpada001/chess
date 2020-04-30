#include <iostream>
#include "Cell.h"
#include "Piece.h"

using namespace std;

Cell::Cell(int r, int c, CellColor color): r{r}, c{c}, color{color} {}

Cell::~Cell() {}

bool Cell::hasPiece() const {
	return this->_hasPiece;
}

Piece *Cell::getPiece() {
	return this->piece;
}

void Cell::putPiece(Piece *p){
	this->piece = p;
	this->piece->_onChessBoard = true;
	this->_hasPiece = true;
	this->piece->setPosition(this->r, this->c);
	this->notifyObservers();
}

void Cell::removePiece() {
	this->piece->_onChessBoard = false;
	this->piece = nullptr;
	this->_hasPiece = false;
	this->notifyObservers();
}

CellColor Cell::getColor() {
	return this->color;
}

int Cell::getRow() {
	return this->r;
}

int Cell::getCol() {
	return this->c;
}

char Cell::charRepr() {
	if (this->hasPiece()) {
		return this->getPiece()->charRepr();
	} else {
		return ((this->getColor() == CellColor::Black) ? '_': ' ');
	}
}

ostream &operator<<(ostream &out, Cell &cell) {
	return out << cell.charRepr();
}
