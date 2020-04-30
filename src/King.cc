#include <iostream>
#include "King.h"

using namespace std;

King::King(PieceColor color): Piece{color} {}

King::~King() {}

PieceType King::subType() {
	return PieceType::King;
}

char King::charRepr() {
	return (this->getColor() == PieceColor::White) ? 'K' : 'k';
}

vector<Position> King::getNormalMoves() {
	vector<Position> moves;
	for (int i = getRow()-1 ; i <= getRow()+1 ; ++i){
		for (int j = getCol()-1 ; j <= getCol()+1 ; ++j){
			if (! (i == getRow() && j == getCol())){
				if (this->getChessBoard()->inRange(i,j) && !this->getChessBoard()->hasPiece(i,j)) moves.emplace_back(Position(i,j));
			}
		}
	}
	for (auto &p: this->getCastlingMoves()) moves.emplace_back(p);
	return moves;
}

vector<Position> King::getCaptureMoves() {
	vector<Position> moves;
	for (int i = getRow()-1 ; i <= getRow()+1 ; ++i){
		for (int j = getCol()-1 ; j <= getCol()+1 ; ++j){
			if (! (i == getRow() && j == getCol())){
				if (this->getChessBoard()->hasPiece(i,j)){
					if (this->getChessBoard()->getPiece(i,j)->getColor() != this->getColor()) moves.emplace_back(Position(i,j));
				}
			}
		}
	}
	return moves;
}

vector<Position> King::getCastlingMoves() {
	vector<Position> moves;
	bool hasPiecesBetween=true;
	if (!this->moved() && this->getChessBoard()->hasPiece(getRow(),0)){
		Piece* p1 = this->getChessBoard()->getPiece(getRow(),0);
		if (p1->subType() == PieceType::Rook && p1->getColor() == this->getColor()){
			for(int i = getCol()-1; i > 0; --i){
				if (this->getChessBoard()->hasPiece(getRow(),i)){
					hasPiecesBetween=false;
					break;
				}
			}
			if (hasPiecesBetween) moves.emplace_back(Position(getRow(),getCol()-2));
		}
	}
	hasPiecesBetween=true;
	if (!moved() && this->getChessBoard()->hasPiece(getRow(),this->getChessBoard()->getSize()-1)){
		Piece* p2 = this->getChessBoard()->getPiece(getRow(),this->getChessBoard()->getSize()-1);
		if (p2->subType() == PieceType::Rook && p2->getColor() == this->getColor()){
			for(int i = getCol()+1; i < this->getChessBoard()->getSize()-1; ++i){
				if (this->getChessBoard()->hasPiece(getRow(),i)){
					hasPiecesBetween=false;
					break;
				}
			}
			if (hasPiecesBetween) moves.emplace_back(Position(getRow(),getCol()+2));
		}
	}
	return moves;
}
