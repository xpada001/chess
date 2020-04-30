#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_

#include <vector>
#include <iostream>
#include <string>
#include "Cell.h"
#include "TextDisplay.h"
#include "GraphicsDisplay.h"
#include "Position.h"

enum class PieceColor;

class Piece;

class ChessBoard {
	int size;
	std::vector<std::vector<Cell>> grid;
	GraphicsDisplay *gd;
	TextDisplay *td;
public:
	ChessBoard(int size); // constructor
	virtual ~ChessBoard(); // destructor
	bool hasPiece(int r, int c); // return true is (r, c) has a piece
	bool hasPiece(std::string posn); // string version
	bool inRange(int r, int c); // return true if (r, c) is in the chessBoard
	Piece* getPiece(int r, int c); // get piece from (r, c)
	Piece* getPiece(std::string posn); // string version
	void putPiece(int r, int c, Piece *p); // put a piece to (r, c)
	void putPiece(std::string posn, Piece *p); // string version
	void removePiece(int r, int c); // remove a piece from (r, c)
	void removePiece(std::string posn); // string version
	void movePiece(int sr, int sc, int tr, int tc); // move a piece from (sr, sc) to (tr, tc), if a piece already exists in (tr, tc)
													// it is removed from the chessboard
	void movePiece(std::string source, std::string target); // string version
	int getSize(); // get chessboard size
	std::vector<Piece *> getActivePieces(PieceColor color); // get all active pieces of a color
	std::vector<Position> getCaptureRange(PieceColor color); // get all capture position of a color
	friend std::ostream &operator<< (std::ostream &out, ChessBoard &c); // used to print a chessboard
};

#endif
