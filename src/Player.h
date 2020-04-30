#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "ChessBoard.h"
#include "Piece.h"
#include "Position.h"
#include "Tracker.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "King.h"
#include "InvalidMove.h"
#include "MoveHistory.h"
#include "Helpers.h"
#include <vector>

enum class PlayerType {
	Computer,
	Human
};

class Player {
	Player *opponent;
	ChessBoard *chessBoard;
	PieceColor color;
	std::vector<Piece*> pieces;
	bool _resigned = false;
	Tracker *_tracker;
	Piece *king = nullptr;
public:
	Player(ChessBoard *cb, PieceColor c);
	virtual ~Player();
	ChessBoard* getChessBoard(); // get current chessboard
	PieceColor getColor(); // get current player's color
	std::vector<Piece*> getPieces(); // get all pieces from player
	std::vector<Piece*> getActivePieces(); // get player's all active pieces that are on chessboard
	std::vector<Piece*> getInactivePieces(); // get player's all inactive pieces that are removed from chessboard
	void setOpponent(Player *p); // set p as player's opponent
	Player* getOpponent(); // get player's opponent
	void registerPiece(Piece *p); // declare player's ownership of piece p.
	void makeMove(std::string source, std::string target); // player makes a move for piece on source position to target position
	bool isChecked(); // returns true if player is checked by opponent
	bool isCheckmated(); // returns true if player is checkmated by opponent
	bool resigned(); // returns true if player resigned
	void resign(); // returns true if player resigns
	void setTracker(Tracker *t); // set t to be player's tracker of history
	std::vector<Position> getCaptureRange(); // get all opponent's possible moves
	void undo(); // undo player's last move
	bool stalemate(); // returns true if stalemate happened
	bool canPromotePawn(); // returns true if a pawn will be promoted
	void promotePawn(Piece *p, PieceType type); // promote player's piece p to be a piecetype type
	void promotePawn(Piece *p, PieceType type, Piece *c); // promote pawn while capturing enemy piece
	virtual PlayerType subType() = 0; // returns if player is a computer or a human
	Piece *getKing(); // returns the pointer to the king;
	void removePiece(std::string position);
	void putPiece(std::string pos, Piece *p);
private:
	bool isValidMove(std::string); // returns true if a move is valid move.
	bool isPositionInRange(int row, int col); // returns true if (row, col) is a valid position in the chessboard
	bool isPositionInRange(std::string);
	bool isPositionInRange(Position p);
};

#endif
