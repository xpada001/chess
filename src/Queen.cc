#include "Queen.h"

using namespace std;

Queen::Queen(PieceColor color): Piece{color} {}

Queen::~Queen() {}

PieceType Queen::subType() {
	return PieceType::Queen;
}

char Queen::charRepr() {
	return (this->getColor() == PieceColor::White) ? 'Q' : 'q';
}

vector<Position> Queen::getNormalMoves() {
	vector<Position> moves;
	for (int row = this->getRow()+1; row < this->getChessBoard()->getSize(); ++row){
		if (this->getChessBoard()->hasPiece(row, getCol())) break;
		moves.emplace_back(Position(row,getCol()));
	}
	for (int row = this->getRow()-1; row >= 0; --row){
		if (this->getChessBoard()->hasPiece(row, getCol())) break;
		moves.emplace_back(Position(row,getCol()));
	}
	for (int col = this->getCol()-1; col >= 0; --col){
		if (this->getChessBoard()->hasPiece(getRow(), col))	break;
		moves.emplace_back(Position(getRow(),col));
	}
	for (int col = this->getCol()+1; col < this->getChessBoard()->getSize(); ++col){
		if (this->getChessBoard()->hasPiece(getRow(), col))	break;
		moves.emplace_back(Position(getRow(),col));
	}
	int diag=getRow();
	for(int i = this->getCol()+1; i < this->getChessBoard()->getSize(); ++i){
		diag++;
		if (!this->getChessBoard()->inRange(diag, i) || this->getChessBoard()->hasPiece(diag, i)) break;
		moves.emplace_back(Position(diag,i));
	}
	diag=getRow();
	for(int i = this->getCol()-1; i >= 0; --i){
		diag++;
		if (!this->getChessBoard()->inRange(diag, i) || this->getChessBoard()->hasPiece(diag, i)) break;
		moves.emplace_back(Position(diag,i));
	}
	diag=getRow();
	for(int i = this->getCol()-1; i >= 0; --i){
		diag--;
		if (!this->getChessBoard()->inRange(diag, i) || this->getChessBoard()->hasPiece(diag, i)) break;
		moves.emplace_back(Position(diag,i));
	}
	diag=getRow();
	for(int i = this->getCol()+1; i < this->getChessBoard()->getSize(); ++i){
		diag--;
		if (!this->getChessBoard()->inRange(diag, i) || this->getChessBoard()->hasPiece(diag, i)) break;
		moves.emplace_back(Position(diag,i));
	}
	return moves;
}

vector<Position> Queen::getCaptureMoves() {
	vector<Position> moves;
	for (int row = this->getRow()+1; row < this->getChessBoard()->getSize(); ++row){
		if (this->getChessBoard()->hasPiece(row, getCol())){
			if (this->getChessBoard()->getPiece(row, getCol())->getColor() == this->getColor())	break;
			moves.emplace_back(Position(row,getCol()));
			break;
		}
	}
	for (int row = this->getRow()-1; row >= 0; --row){
		if (this->getChessBoard()->hasPiece(row, getCol())){
			if (this->getChessBoard()->getPiece(row, getCol())->getColor() == this->getColor())	break;
			moves.emplace_back(Position(row,getCol()));
			break;
		}
	}
	for (int col = this->getCol()-1; col >= 0; --col){
		if (this->getChessBoard()->hasPiece(getRow(), col)){
			if (this->getChessBoard()->getPiece(getRow(), col)->getColor() == this->getColor())	break;
			moves.emplace_back(Position(getRow(), col));
			break;
		}
	}
	for (int col = this->getCol()+1; col < this->getChessBoard()->getSize(); ++col){
		if (this->getChessBoard()->hasPiece(getRow(), col)){
			if (this->getChessBoard()->getPiece(getRow(), col)->getColor() == this->getColor())	break;
			moves.emplace_back(Position(getRow(), col));
			break;
		}
	}
	int diag=getRow();
	for(int i = this->getCol()+1; i < this->getChessBoard()->getSize(); ++i){
		diag++;
		if (this->getChessBoard()->hasPiece(diag, i)){
			if (this->getChessBoard()->getPiece(diag, i)->getColor() == this->getColor()) break;
			moves.emplace_back(Position(diag, i));
			break;
		}
	}
	diag=getRow();
	for(int i = this->getCol()-1; i >= 0; --i){
		diag++;
		if (this->getChessBoard()->hasPiece(diag, i)){
			if (this->getChessBoard()->getPiece(diag, i)->getColor() == this->getColor()) break;
			moves.emplace_back(Position(diag, i));
			break;
		}
	}
	diag=getRow();
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
