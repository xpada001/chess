#include "Pawn.h"
#include <iostream>

using namespace std;

Pawn::Pawn(PieceColor color): Piece{color} {}

Pawn::~Pawn() {}

PieceType Pawn::subType() {
	return PieceType::Pawn;
}

char Pawn::charRepr() {
	return (this->getColor() == PieceColor::White) ? 'P' : 'p';
}

bool Pawn::movedTwoSteps() {
	if (this->moved()) {
		return abs(this->lastPositions.back().row - this->r) == 2;
	}
	return false;
}

vector<Position> Pawn::getNormalMoves() {
	vector<Position> moves;
	if (getColor() == PieceColor::White){
		if (!moved()){
			if (this->getChessBoard()->inRange(getRow()+2,getCol()) && !this->getChessBoard()->hasPiece(getRow()+2,getCol())){
				if (!this->getChessBoard()->hasPiece(getRow()+1,getCol())) moves.emplace_back(Position(getRow()+2,getCol()));
			}
		}
		if (this->getChessBoard()->inRange(getRow()+1,getCol()) && !this->getChessBoard()->hasPiece(getRow()+1,getCol())) moves.emplace_back(Position(getRow()+1,getCol()));
	}
	else{
		if (!moved()){
			if (this->getChessBoard()->inRange(getRow()-2,getCol()) && !this->getChessBoard()->hasPiece(getRow()-2,getCol())){
				if (!this->getChessBoard()->hasPiece(getRow()-1,getCol())) moves.emplace_back(Position(getRow()-2,getCol()));
			}
		}
		if (this->getChessBoard()->inRange(getRow()-1,getCol()) && !this->getChessBoard()->hasPiece(getRow()-1,getCol())) moves.emplace_back(Position(getRow()-1,getCol()));
	}
	return moves;
}

vector<Position> Pawn::getCaptureMoves() {
	vector<Position> moves;
	if (getColor() == PieceColor::White){
		if (this->getChessBoard()->hasPiece(getRow()+1,getCol()+1)){
			if (this->getChessBoard()->getPiece(getRow()+1,getCol()+1)->getColor() != this->getColor()) moves.emplace_back(Position(getRow()+1,getCol()+1));
		}
		if (this->getChessBoard()->hasPiece(getRow()+1,getCol()-1)){
			if (this->getChessBoard()->getPiece(getRow()+1,getCol()-1)->getColor() != this->getColor()) moves.emplace_back(Position(getRow()+1,getCol()-1));
		}
	}
	else{
		if (this->getChessBoard()->hasPiece(getRow()-1,getCol()+1)){
			if (this->getChessBoard()->getPiece(getRow()-1,getCol()+1)->getColor() != this->getColor()) moves.emplace_back(Position(getRow()-1,getCol()+1));
		}
		if (this->getChessBoard()->hasPiece(getRow()-1,getCol()-1)){
			if (this->getChessBoard()->getPiece(getRow()-1,getCol()-1)->getColor() != this->getColor()) moves.emplace_back(Position(getRow()-1,getCol()-1));
		}
	}
	for (auto &p: this->getEnPassantMoves()) moves.emplace_back(p);
	return moves;
}

vector<Position> Pawn::getEnPassantMoves() {
	vector<Position> moves;
	if (this->getChessBoard()->hasPiece(getRow(),getCol()+1)){
		Piece* p1 = this->getChessBoard()->getPiece(getRow(),getCol()+1);
		if (p1->subType() == PieceType::Pawn) {
			if (this->getColor() != p1->getColor() && static_cast<Pawn *>(p1)->movedTwoSteps() == true) {
				if (this->getColor() == PieceColor::Black) moves.emplace_back(Position(getRow()-1,getCol()+1));
				if (this->getColor() == PieceColor::White) moves.emplace_back(Position(getRow()+1,getCol()+1));
			}
		}
	}
	if (this->getChessBoard()->hasPiece(getRow(),getCol()-1)){
		Piece* p2 = this->getChessBoard()->getPiece(getRow(),getCol()-1);
		if (p2->subType() == PieceType::Pawn) {
			if (this->getColor() != p2->getColor() && static_cast<Pawn *>(p2)->movedTwoSteps() == true) {
				if (this->getColor() == PieceColor::Black) moves.emplace_back(Position(getRow()-1,getCol()-1));
				if (this->getColor() == PieceColor::White) moves.emplace_back(Position(getRow()+1,getCol()-1));
			}
		}
	}
	return moves;
}
