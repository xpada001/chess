#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.h"

class Pawn final: public Piece {
public:
	Pawn(PieceColor color);
	virtual ~Pawn();
	PieceType subType() override;
	char charRepr() override;
	bool movedTwoSteps();
	std::vector<Position> getNormalMoves() override;
	std::vector<Position> getCaptureMoves() override;
private:
	std::vector<Position> getEnPassantMoves();
};

#endif
