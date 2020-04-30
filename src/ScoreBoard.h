#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

#include <iostream>
#include "Piece.h"
#include "Player.h"

class ScoreBoard {
    float pWscore;
    float pBscore;
public:
    ScoreBoard();
    virtual~ ScoreBoard();
    void incrScore(PieceColor color, float score);
    void printScore();
};

std::ostream &operator<<(std::ostream &out, ScoreBoard &b);

#endif
