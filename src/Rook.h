#ifndef _ROOK_H_
#define _ROOK_H_

#include "Piece.h"

class Rook final: public Piece {
public:
	Rook(PieceColor color);
	virtual ~Rook();
	PieceType subType() override;
	char charRepr() override;
	std::vector<Position> getNormalMoves() override;
	std::vector<Position> getCaptureMoves() override;
};

#endif
