#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "Piece.h"

class Bishop final: public Piece {
public:
	Bishop(PieceColor color);
	virtual ~Bishop();
	PieceType subType() override;
	char charRepr() override;
	std::vector<Position> getNormalMoves() override;
	std::vector<Position> getCaptureMoves() override;
};

#endif
