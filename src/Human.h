#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "Player.h"
#include "ChessBoard.h"

class Human: public Player {
public:
	Human(ChessBoard *cb, PieceColor c);
	PlayerType subType() override;
	virtual ~Human();
	void playNextMove(std::string source, std::string target);
};

#endif
