#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(ChessBoard *cb, PieceColor c): chessBoard{cb}, color{c}, pieces{vector<Piece *>()} {}

Player::~Player() {}

ChessBoard* Player::getChessBoard() {
	return this->chessBoard;
}

PieceColor Player::getColor() {
	return this->color;
}

vector<Piece*> Player::getPieces() {
	return this->pieces;
}

vector<Piece*> Player::getActivePieces() {
	vector<Piece*> result {};
	for (auto const &p: this->pieces) {
		if (p->onChessBoard()) result.emplace_back(p);
	}
	return result;
}

vector<Piece*> Player::getInactivePieces() {
	vector<Piece*> result {};
	for (auto const &p: this->pieces) {
		if (!p->onChessBoard()) result.emplace_back(p);
	}
	return result;
}

void Player::setOpponent(Player *p) {
	this->opponent = p;
}

Player *Player::getOpponent() {
	return this->opponent;
}

void Player::registerPiece(Piece *p) {
	pieces.emplace_back(p);
}

void Player::makeMove(string source, string target) {
	if (!(this->isPositionInRange(source))) {
			throw SourceOutOfRange();
	} else {
		if (!this->chessBoard->hasPiece(source)) {
			throw PieceDoesNotExist();
		} else {
			if (this->chessBoard->getPiece(source)->getColor() != this->getColor()) {
				throw MovingEnemyPiece();
			} else if (Position(source) == Position(target)) {
				throw SamePositionMove();
			}
		}
	}
	if (!(this->isPositionInRange(target))) {
				throw TargetOutOfRange();
		} else {
			if (this->chessBoard->hasPiece(target) && this->chessBoard->getPiece(target)->getColor() == this->getColor()) {
				throw CapturingAllyPiece();
			}
	}
	bool illegalMove = true;
	for (unsigned int i = 0; i < this->chessBoard->getPiece(source)->getAllAvailableMoves().size(); ++i) {
		if (Position(target) == this->chessBoard->getPiece(source)->getAllAvailableMoves()[i]) {
			illegalMove = false;
			break;
		}
	}
	if (illegalMove) {
		throw IllegalMove();
	}
	// enpassant case
	bool isEnPassant = false;
	if (this->chessBoard->getPiece(source)->subType() == PieceType::Pawn) {
		bool isCaptureMove = false;
		for (auto &m: this->chessBoard->getPiece(source)->getCaptureMoves()) {
			if (m.toString() == target) {
				isCaptureMove = true;
			}
		}
		if (isCaptureMove && !this->chessBoard->hasPiece(target)) {
			isEnPassant = true;
		}
	}
	//castling case
	bool isCastling = false;
	if (this->chessBoard->getPiece(source)->subType() == PieceType::King){
		int start = Position(source).col;
		int end = Position(target).col;
		isCastling = abs(end - start) == 2;
	}
	if (this->chessBoard->hasPiece(target)) {
		this->_tracker->push(MoveHistory(source, target, this->chessBoard->getPiece(source), this->chessBoard->getPiece(target)));
	} else {
		// target position has no piece
		if (isEnPassant) {
			auto enemyPawnPosition = Position(target);
			if (this->getColor() == PieceColor::Black) {
				++enemyPawnPosition.row;
			} else {
				--enemyPawnPosition.row;
			}
			this->_tracker->push(MoveHistory(source, target, this->chessBoard->getPiece(source), this->chessBoard->getPiece(enemyPawnPosition.toString())));
			this->chessBoard->removePiece(enemyPawnPosition.toString());
		} else if (isCastling){
			int row = this->chessBoard->getPiece(source)->getRow();
			if (Position(target).col == 6){
				int lastRow = this->chessBoard->getSize() - 1;
				this->chessBoard->movePiece(row, lastRow, row, lastRow - 2);
				this->_tracker->push(MoveHistory(source, target, Position(row, lastRow).toString(), Position(row, lastRow - 2).toString(), this->getKing(), this->chessBoard->getPiece(row, 5)));
			} else {
				this->chessBoard->movePiece(row, 0, row, 3);
				this->_tracker->push(MoveHistory(source, target, Position(row, 0).toString(), Position(row, 3).toString(), this->getKing(), this->chessBoard->getPiece(row, 3)));
			}
		}
		else {
			this->_tracker->push(MoveHistory(source, target, this->chessBoard->getPiece(source)));
		}
	}
	this->chessBoard->movePiece(source, target);
	if (this->isChecked()) {
		throw CheckedMove();
	}
}

bool Player::canPromotePawn() {
	bool flag = false;
	for (auto &piece: this->getActivePieces()) {
		if (piece->subType() == PieceType::Pawn) {
			if (this->getColor() == PieceColor::White) {
				if (piece->getRow() == 7) {
					flag = true;
					break;
				}
			} else {
				if (piece->getRow() == 0) {
					flag = true;
					break;
				}
			}
		}
	}
	return flag;
}

void Player::promotePawn(Piece *p, PieceType type) {
	string posn = p->getPosition();
	this->chessBoard->removePiece(posn);
	Piece *newPiece;
	if (type == PieceType::Queen){
		newPiece = new Queen(this->getColor());
	} else if (type == PieceType::Rook){
		newPiece = new Rook(this->getColor());
	} else if (type == PieceType::Knight){
		newPiece = new Knight(this->getColor());
	} else {
		newPiece = new Bishop(this->getColor());
	}
	MoveHistory h = this->_tracker->pop();
	this->registerPiece(newPiece);
	this->_tracker->push(MoveHistory(h.getSource(), h.getTarget(), newPiece, p, true));
	this->chessBoard->putPiece(posn, newPiece);
}

void Player::promotePawn(Piece *p, PieceType type, Piece *c) {
	this->promotePawn(p, type);
	auto h = this->_tracker->pop();
	this->_tracker->push(MoveHistory(h.getSource(), h.getTarget(), h.getOriginalPiece(), p, c));
}

bool Player::isChecked() {
	bool checked = false;
	for (auto piece: this->opponent->getActivePieces()) {
		for (auto pos: piece->getCaptureMoves()) {
			if (this->getKing()->getPosition() == pos.toString()) {
				checked = true;
				break;
			}
		}
	}
	return checked;

}

bool Player::isCheckmated() {
	bool checkmated = true;
	for (auto piece: this->getActivePieces()) {
		if (!checkmated) {
			break;
		}
		for (auto pos: piece->getAllAvailableMoves()) {
			try {
				this->makeMove(piece->getPosition(), pos.toString());
			} catch (CheckedMove &e) {
				this->undo();
			}
			if (!this->isChecked()) {
				checkmated = false;
				this->undo();
				break;
			}
		}
	}
	return checkmated;
}

bool Player::resigned() {
	return this->_resigned;
}

void Player::resign() {
	this->_resigned = true;
}

void Player::setTracker(Tracker *t) {
	this->_tracker = t;
}

bool Player::isPositionInRange(int row, int col) {
	int n = this->chessBoard->getSize();
	return (row >= 0 && row < n && col >= 0 && col < n);
}

bool Player::isPositionInRange(string p) {
	return this->isPositionInRange(Position(p));
}

bool Player::isPositionInRange(Position p) {
	return this->isPositionInRange(p.row, p.col);
}

vector<Position> Player::getCaptureRange() {
	return this->chessBoard->getCaptureRange(this->getColor());
}

void Player::undo() {
	MoveHistory h = this->_tracker->pop();
	if (h.isPromoteMove()) {
		this->chessBoard->removePiece(h.getTarget());
		this->chessBoard->putPiece(h.getSource(), h.getOriginalPiece());
		h.getOriginalPiece()->lastPositions.pop_back();
		if (h.hasCapturedPiece()) {
			Piece *cp = h.getCapturedPiece();
			this->chessBoard->putPiece(cp->getRow(), cp->getCol(), cp);
		}
		return;
	}
	this->chessBoard->movePiece(h.getTarget(), h.getSource());
	h.getMovedPiece()->lastPositions.pop_back();
	h.getMovedPiece()->lastPositions.pop_back();
	if (h.hasCapturedPiece()) {
		Piece *cp = h.getCapturedPiece();
		this->chessBoard->putPiece(cp->getRow(), cp->getCol(), cp);
	}
	if (h.isCastling()) {
		this->chessBoard->movePiece(h.getTarget2(), h.getSource2());
		h.getMovedPiece2()->lastPositions.pop_back();
		h.getMovedPiece2()->lastPositions.pop_back();
	}
}

Piece *Player::getKing() {
	return this->king;
}

bool Player::stalemate() {
	if (!this->isChecked()) {
		bool flag = true;
		for (auto piece: this->getActivePieces()){
			auto v = piece->getAllAvailableMoves();
			if (v.empty()) continue;
			for (auto pos: v){
				try {
					this->makeMove(piece->getPosition(), pos.toString());
					flag = false;
					this->undo();
					break;
				} catch (CheckedMove &e) {
					this->undo();
				}
			}
		}
		return flag;
	}
	return false;
}

void Player::removePiece(string posn) {
	if (this->chessBoard->getPiece(posn)->subType() == PieceType::King) {
		this->king = nullptr;
	}
	this->chessBoard->removePiece(posn);
}

void Player::putPiece(string posn, Piece *p) {
	if (p->subType() == PieceType::King) {
		this->king = p;
	}
	this->chessBoard->putPiece(posn, p);
}

