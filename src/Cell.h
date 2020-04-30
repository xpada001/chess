#ifndef _CELL_H_
#define _CELL_H_

#include <iostream>
#include "Subject.h"
#include "Observer.h"

class Piece;

enum class CellColor {
	Black,
	White
};

class Cell final: public Subject {
	int r;
	int c;
	CellColor color;
	bool _hasPiece = false;
	Piece *piece;
public:
	Cell(int r, int c, CellColor color);
	virtual ~Cell();
	bool hasPiece() const; // returns true if the cell has a piece
	Piece* getPiece(); // get the piece from the cell
	void putPiece(Piece *p); // put a piece on the cell
	void removePiece(); // remove a piece from the cell
	CellColor getColor(); // get the color of the cell
	int getRow(); // get the row number
	int getCol(); // get the column number
	char charRepr(); // returns a char representation of the cell
	friend std::ostream &operator<<(std::ostream &out, Cell &cell); // used to print the cell
};

#endif
