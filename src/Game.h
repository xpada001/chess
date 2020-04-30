#ifndef _GAME_H_
#define _GAME_H_

#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "ChessBoard.h"
#include "Computer.h"
#include "Human.h"
#include "Tracker.h"
#include "ScoreBoard.h"

class Game {
	ChessBoard *chessBoard;
	Player *whitePlayer;
	Player *blackPlayer;
	Tracker *tracker;
	PieceColor whosturn = PieceColor::White;
	ScoreBoard *scoreBoard;
public:
	Game(std::string w, std::string b, ScoreBoard *sb);
	virtual ~Game();
	void setup();
	void start();
	bool draw();
private:
	void printChessBoard();
};

#endif
