#include "MoveHistory.h"

using namespace std;

MoveHistory::MoveHistory(string s, string t, Piece *p): source{s}, target{t}, movedPiece{p} {}

MoveHistory::MoveHistory(string s, string t, Piece *p, Piece *m2): source{s}, target{t},
		movedPiece{p}, capturedPiece(m2), _hasCapturedPiece{true} {}

MoveHistory::MoveHistory(string s, string t, string s2, string t2, Piece *p, Piece *p2):
	source{s}, target{t}, source2{s2}, target2{t2}, movedPiece{p}, movedPiece2{p2}, _isCastling{true} {}

MoveHistory::MoveHistory(string s, string t, Piece *p, Piece *m2, bool isPromote): source{s}, target{t},
		movedPiece{p}, originalPiece(m2), _isPromoteMove{isPromote} {}

MoveHistory::MoveHistory(string s, string t, Piece *p, Piece *m2, Piece *m3): source{s}, target{t},
		movedPiece{p}, capturedPiece{m3}, originalPiece(m2), _hasCapturedPiece{true}, _isPromoteMove{true} {}

MoveHistory::~MoveHistory() {}

Piece *MoveHistory::getMovedPiece() {
	return this->movedPiece;
}

bool MoveHistory::hasCapturedPiece() {
	return this->_hasCapturedPiece;
}

Piece *MoveHistory::getCapturedPiece() {
	return this->capturedPiece;
}

string MoveHistory::getSource() {
	return this->source;
}

string MoveHistory::getTarget() {
	return this->target;
}

string MoveHistory::getSource2() {
	return this->source2;
}

string MoveHistory::getTarget2() {
	return this->target2;
}

bool MoveHistory::isCastling() {
	return this->_isCastling;
}

bool MoveHistory::isPromoteMove() {
	return this->_isPromoteMove;
}

Piece *MoveHistory::getMovedPiece2() {
	return this->movedPiece2;
}

Piece *MoveHistory::getOriginalPiece() {
	return this->originalPiece;
}
