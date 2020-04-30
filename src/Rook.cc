#include "Rook.h"

using namespace std;

Rook::Rook(PieceColor color): Piece{color} {}

Rook::~Rook() {}

PieceType Rook::subType() {
	return PieceType::Rook;
}

char Rook::charRepr() {
	return (this->getColor() == PieceColor::White) ? 'R' : 'r';
}

vector<Position> Rook::getNormalMoves() {
	vector<Position> moves;
	for (int row = this->getRow()+1; row < this->getChessBoard()->getSize(); ++row){
		if (!this->getChessBoard()->inRange(row,getCol()) || this->getChessBoard()->hasPiece(row, getCol())) break;
		moves.emplace_back(Position(row,getCol()));
	}
	for (int row = this->getRow()-1; row >= 0; --row){
		if (!this->getChessBoard()->inRange(row,getCol()) || this->getChessBoard()->hasPiece(row, getCol())) break;
		moves.emplace_back(Position(row,getCol()));
	}
	for (int col = this->getCol()-1; col >= 0; --col){
		if (!this->getChessBoard()->inRange(getRow(), col) || this->getChessBoard()->hasPiece(getRow(), col)) break;
		moves.emplace_back(Position(getRow(),col));
	}
	for (int col = this->getCol()-1; col < this->getChessBoard()->getSize(); --col){
		if (!this->getChessBoard()->inRange(getRow(), col) || this->getChessBoard()->hasPiece(getRow(), col)) break;
		moves.emplace_back(Position(getRow(),col));
	}
	return moves;
}

vector<Position> Rook::getCaptureMoves() {
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
	return moves;
}
