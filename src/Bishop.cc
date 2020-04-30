#include "Bishop.h"

using namespace std;

Bishop::Bishop(PieceColor color): Piece{color} {}

Bishop::~Bishop() {}

PieceType Bishop::subType() {
	return PieceType::Bishop;
}

char Bishop::charRepr() {
	return (this->getColor() == PieceColor::White) ? 'B' : 'b';
}

vector<Position> Bishop::getNormalMoves() {
	vector<Position> moves;
	int diag = getRow();
	for(int i = this->getCol()+1; i < this->getChessBoard()->getSize(); ++i){
		diag++;
		if (!this->getChessBoard()->inRange(diag, i) || this->getChessBoard()->hasPiece(diag, i)) break;
		moves.emplace_back(Position(diag,i));
	}
	diag = getRow();
	for(int i = this->getCol()-1; i >= 0; --i){
		diag++;
		if (!this->getChessBoard()->inRange(diag, i) || this->getChessBoard()->hasPiece(diag, i)) break;
		moves.emplace_back(Position(diag,i));
	}
	diag = getRow();
	for(int i = this->getCol()-1; i >= 0; --i){
		diag--;
		if (!this->getChessBoard()->inRange(diag, i) || this->getChessBoard()->hasPiece(diag, i)) break;
		moves.emplace_back(Position(diag,i));
	}
	diag = getRow();
	for(int i = this->getCol()+1; i < this->getChessBoard()->getSize(); ++i){
		diag--;
		if (!this->getChessBoard()->inRange(diag, i) || this->getChessBoard()->hasPiece(diag, i)) break;
		moves.emplace_back(Position(diag,i));
	}
	return moves;
}

vector<Position> Bishop::getCaptureMoves() {
	vector<Position> moves;
	int diag = getRow();
	for(int i = this->getCol()+1; i < this->getChessBoard()->getSize(); ++i){
		diag++;
		if (this->getChessBoard()->hasPiece(diag, i)){
			if (this->getChessBoard()->getPiece(diag, i)->getColor() == this->getColor()) break;
			moves.emplace_back(Position(diag, i));
			break;
		}
	}
	diag = getRow();
	for(int i = this->getCol()-1; i >= 0; --i){
		diag++;
		if (this->getChessBoard()->hasPiece(diag, i)){
			if (this->getChessBoard()->getPiece(diag, i)->getColor() == this->getColor()) break;
			moves.emplace_back(Position(diag, i));
			break;
		}
	}
	diag = getRow();
	for(int i = this->getCol()-1; i >= 0; --i){
		diag--;
		if (this->getChessBoard()->hasPiece(diag, i)){
			if (this->getChessBoard()->getPiece(diag, i)->getColor() == this->getColor()) break;
			moves.emplace_back(Position(diag, i));
			break;
		}
	}
	diag=getRow();
	for(int i = this->getCol()+1; i < this->getChessBoard()->getSize(); ++i){
		diag--;
		if (this->getChessBoard()->hasPiece(diag, i)){
			if (this->getChessBoard()->getPiece(diag, i)->getColor() == this->getColor()) break;
			moves.emplace_back(Position(diag, i));
			break;
		}
	}
	return moves;
}
