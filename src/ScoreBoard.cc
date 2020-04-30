#include "ScoreBoard.h"

using namespace std;

ScoreBoard::ScoreBoard(): pWscore{0}, pBscore{0} {}

ScoreBoard::~ScoreBoard() {}

void ScoreBoard::incrScore(PieceColor color, float score){
	if (color == PieceColor::White) {
		this->pWscore += score;
	} else {
		this->pBscore += score;
	}
}

void ScoreBoard::printScore() {
    cout << "Final Score:" << endl;
    cout << "White : " << this->pWscore << endl;
    cout << "Black : " << this->pBscore << endl;
}

std::ostream &operator<<(std::ostream &out, ScoreBoard &b) {
	b.printScore();
	return out;
}

