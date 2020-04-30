#include "Human.h"
#include <string>

using namespace std;

Human::Human(ChessBoard *cb, PieceColor c): Player(cb, c) {}

Human::~Human() {}

PlayerType Human::subType() {
	return PlayerType::Human;
}

void Human::playNextMove(string source, string target) {
	char promoteType;
	Piece *targetPiece = nullptr;
	if (this->getChessBoard()->hasPiece(target) && this->getChessBoard()->getPiece(target)->getColor() != this->getColor()) {
		targetPiece = this->getChessBoard()->getPiece(target);
	}
	this->makeMove(source, target);
	if (this->canPromotePawn()) {
		cin >> promoteType;
		Piece *originalPiece = this->getChessBoard()->getPiece(target);
		PieceType type;
		promoteType = tolower(promoteType);
		switch (promoteType) {
		case 'q':
			type = PieceType::Queen;
			break;
		case 'b':
			type = PieceType::Bishop;
			break;
		case 'r':
			type = PieceType::Rook;
			break;
		case 'n':
			type = PieceType::Knight;
			break;
		}
		if (targetPiece) {
			this->promotePawn(originalPiece, type, targetPiece);
		} else {
			this->promotePawn(originalPiece, type);
		}
	}
}
