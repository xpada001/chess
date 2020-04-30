#ifndef _KING_H_
#define _KING_H_

#include "Piece.h"

class King final: public Piece {
public:
	King(PieceColor color);
	virtual ~King();
	PieceType subType() override;
	char charRepr() override;
	std::vector<Position> getNormalMoves() override;
	std::vector<Position> getCaptureMoves() override;
private:
	std::vector<Position> getCastlingMoves();
};

#endif
