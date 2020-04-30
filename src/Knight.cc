#include "Knight.h"

using namespace std;

Knight::Knight(PieceColor color): Piece{color} {}

Knight::~Knight() {}

PieceType Knight::subType() {
	return PieceType::Knight;
}

char Knight::charRepr() {
	return (this->getColor() == PieceColor::White) ? 'N' : 'n';
}

vector<Position> Knight::getNormalMoves() {
	vector<Position> moves;
	// Implements moves here.
	for (int i = 1 ; i <= 2 ; ++i){
		for (int j = 1 ; j <= 2; ++j){
			if (i != j){
				if (this->getChessBoard()->inRange(getRow()+i,getCol()+j) && !this->getChessBoard()->hasPiece(getRow()+i,getCol()+j)){
					moves.emplace_back(getRow()+i,getCol()+j);
				}
				if (this->getChessBoard()->inRange(getRow()-i,getCol()+j) && !this->getChessBoard()->hasPiece(getRow()-i,getCol()+j)){
					moves.emplace_back(getRow()-i,getCol()+j);
				}
				if (this->getChessBoard()->inRange(getRow()+i,getCol()-j) && !this->getChessBoard()->hasPiece(getRow()+i,getCol()-j)){
					moves.emplace_back(getRow()+i,getCol()-j);
				}
				if (this->getChessBoard()->inRange(getRow()-i,getCol()-j) && !this->getChessBoard()->hasPiece(getRow()-i,getCol()-j)){
					moves.emplace_back(getRow()-i,getCol()-j);
				}
			}
		}
	}
	return moves;
}

vector<Position> Knight::getCaptureMoves() {
	vector<Position> moves;
	// Implements moves here.
	for (int i = 1 ; i <= 2 ; ++i){
		for (int j = 1 ; j <= 2; ++j){
			if (i != j){
				if (this->getChessBoard()->inRange(getRow()+i,getCol()+j) && this->getChessBoard()->hasPiece(getRow()+i,getCol()+j)){
					if (this->getChessBoard()->getPiece(getRow()+i,getCol()+j)->getColor() != this->getColor()){
						moves.emplace_back(getRow()+i,getCol()+j);
					}
				}
				if (this->getChessBoard()->inRange(getRow()-i,getCol()+j) && this->getChessBoard()->hasPiece(getRow()-i,getCol()+j)){
					if (this->getChessBoard()->getPiece(getRow()-i,getCol()+j)->getColor() != this->getColor()){
						moves.emplace_back(getRow()-i,getCol()+j);
					}
				}
				if (this->getChessBoard()->inRange(getRow()+i,getCol()-j) && this->getChessBoard()->hasPiece(getRow()+i,getCol()-j)){
					if (this->getChessBoard()->getPiece(getRow()+i,getCol()-j)->getColor() != this->getColor()){
						moves.emplace_back(getRow()+i,getCol()-j);
					}
				}
				if (this->getChessBoard()->inRange(getRow()-i,getCol()-j) && this->getChessBoard()->hasPiece(getRow()-i,getCol()-j)){
					if (this->getChessBoard()->getPiece(getRow()-i,getCol()-j)->getColor() != this->getColor()){
						moves.emplace_back(getRow()-i,getCol()-j);
					}
				}
			}
		}
	}
	return moves;
}
