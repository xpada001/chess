#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include <vector>
#include <map>
#include "Position.h"
#include "Player.h"
#include <string>
#include <algorithm>

class Computer: public Player {
	int difficulty;
public:
	Computer(ChessBoard *cb, PieceColor c, int d);
	virtual ~Computer();
	void playNextMove(); // computer performs a move from all possible moves based on preference
	std::map<std::string, std::vector<Position>> decisionMap;
	void printDecisionMap(); // print all the pieces that can move and their possible moves
	PlayerType subType() override;
private:
	void makeDecisionMap(); // chose a level based on the chosen difficulty
	void makeLevel1Map(); // select level 1 moves, which is random legal moves
	void makeLevel2Map(); // select level 2 moves, which prefers capturing moves and checks
	void makeLevel3Map(); // select level 3 moves, which prefers avoid capture, capturing moves and checks
	void makeLevel4Map(); // select level 4 moves, which prefers checks, capturing non-pawn piece, then capture pawn piece, avoid capture
	void loadCheckMovesMap(); // load all possible moves to check enemy
	void loadCaptureMovesMap(); // load all possible moves to capture enemy piece
	void loadAvoidCaptureMovesMap(); // load all possible moves to avoid being captured
	void loadNormalMovesMap(); // load all possible normal moves
	void loadAvoidCapturePawnMap(); // load all possible moves to capture pawn
	void deleteFromDecisionMap(std::string source, std::string target); // delete all possible moves
	std::vector<Position> getCheckMoves(Piece *p);
};

#endif
