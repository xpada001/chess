#ifndef _PIECE_H_
#define _PIECE_H_

#include <vector>
#include <iostream>
#include "Position.h"
#include "ChessBoard.h"

enum class PieceColor {
	Black,
	White
};

enum class PieceType {
	King,
	Queen,
	Bishop,
	Knight,
	Rook,
	Pawn
};

class Piece {
	PieceColor color;
	ChessBoard *chessBoard;
	bool _onChessBoard = false;
protected:
	int r;
	int c;
	std::vector<Position> lastPositions;
public:
	explicit Piece(PieceColor c);
	virtual ~Piece();
	virtual PieceType subType() = 0;
	virtual char charRepr() = 0;
	virtual std::vector<Position> getNormalMoves() = 0; // get piece's moves that do not capture opponent's piece nor avoid being captured.
	virtual std::vector<Position> getCaptureMoves() = 0; // get piece's moves that will capture opponent's piece
	std::vector<Position> getAllAvailableMoves(); // get piece's all available moves
	std::vector<Position> getAvoidCaptureMoves(); // get piece's moves that will avoid being captured from opponent's pieces
	PieceColor getColor(); // get piece's color (either white or black)
	void setPosition(int r, int c); // set piece's position to (r,c)
	std::string getPosition(); // get piece's current position
	void setChessBoard(ChessBoard *b); //chessboard will call this to notify piece about the current chessBoard b.
	ChessBoard* getChessBoard(); // get information of current chessBoard object
	bool onChessBoard(); // returns true if piece is on the chessboard.
	int getRow(); // get piece's row
	int getCol(); // get piece's column
	bool moved(); // returns true if the piece has being moved.
	friend class Cell;
	friend void ChessBoard::movePiece(int sr, int sc, int tr, int tc); // move piece from (sr,sc) to (tr, tc)
	friend class Player;
};

#endif
