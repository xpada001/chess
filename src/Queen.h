#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "Piece.h"

class Queen final: public Piece {
public:
	Queen(PieceColor color);
	virtual ~Queen();
	PieceType subType() override;
	char charRepr() override;
	std::vector<Position> getNormalMoves() override;
	std::vector<Position> getCaptureMoves() override;
};

#endif
