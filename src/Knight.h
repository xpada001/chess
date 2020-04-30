#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "Piece.h"

class Knight final: public Piece {
public:
	Knight(PieceColor color);
	virtual ~Knight();
	PieceType subType() override;
	char charRepr() override;
	std::vector<Position> getNormalMoves() override;
	std::vector<Position> getCaptureMoves() override;
};

#endif
