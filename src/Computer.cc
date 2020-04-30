#include "Computer.h"
#include <iostream>
#include "Helpers.h"
#include "InvalidMove.h"

using namespace std;

Computer::Computer(ChessBoard *cb, PieceColor c, int d): Player(cb, c), difficulty{d} {}

Computer::~Computer() {}

void Computer::makeDecisionMap() {
	switch (this->difficulty) {
	case 1:
		this->makeLevel1Map();
		break;
	case 2:
		this->makeLevel2Map();
		break;
	case 3:
		this->makeLevel3Map();
		break;
	case 4:
		this->makeLevel4Map();
		break;
	}
}

void Computer::playNextMove() {
	this->makeDecisionMap();
	auto pair = Helpers::choose(this->decisionMap);
	string source = pair.first;
	Piece *piece = this->getChessBoard()->getPiece(source);
	string target = Helpers::choose(pair.second).toString();
	this->decisionMap.clear();
	this->makeMove(source, target);
	// auto promote
	if (piece->subType() == PieceType::Pawn) {
		vector<PieceType> allPieceType = {PieceType::Queen, PieceType::Rook, PieceType::Knight, PieceType::Bishop};
		if (this->canPromotePawn()) {
			auto type = Helpers::choose(allPieceType);
			this->promotePawn(piece, type);
		}
	}
}

void Computer::printDecisionMap() {
	cout << "///" << ((this->getColor() == PieceColor::White) ? "White" : "Black") << " Moves///" << endl;
	for (auto &pair: this->decisionMap) {
		cout << "@" << pair.first << ": ";
		cout << "( ";
		for (auto &pos: pair.second) {
			cout << pos << ' ';
		}
		cout << ")\n";
	}
	cout << "///ENDMOVES///\n";
}

PlayerType Computer::subType() {
	return PlayerType::Computer;
}

void Computer::loadCheckMovesMap() {
	bool found = false;
	for (auto &p: this->getActivePieces()) {
		vector<Position> moves;
		auto test = this->getCheckMoves(p);
		for (auto &pos: test){
			try {
				this->makeMove(p->getPosition(), pos.toString());
				this->undo();
				found = true;
				moves.emplace_back(pos);
			} catch (CheckedMove &e) {
				this->undo();
			}
		}
		if (found) {
			this->decisionMap[p->getPosition()] = moves;
			found = false;
		}
	}
}

void Computer::loadNormalMovesMap() {
	for (auto &p: this->getActivePieces()) {
		auto moves = p->getAllAvailableMoves();
		if (!moves.empty()) {
			this->decisionMap[p->getPosition()] = moves;
		}
	}
}

void Computer::loadCaptureMovesMap() {
	bool found = false;
	for (auto &p: this->getActivePieces()){
		vector<Position> moves;
		auto test = p->getCaptureMoves();
		for (auto &pos: test){
			try {
				this->makeMove(p->getPosition(), pos.toString());
				this->undo();
				found = true;
				moves.emplace_back(pos);
			} catch (CheckedMove &e) {
				this->undo();
			}
		}
		if (found) {
			this->decisionMap[p->getPosition()] = moves;
			found = false;
		}
	}
}

void Computer::loadAvoidCaptureMovesMap() {
	bool found = false;
	for (auto &p: this->getActivePieces()){
		vector<Position> moves;
		auto test = p->getAvoidCaptureMoves();
		for (auto &pos: test){
			try {
				this->makeMove(p->getPosition(), pos.toString());
				this->undo();
				found = true;
				moves.emplace_back(pos);
			} catch (CheckedMove &e) {
				this->undo();
			}
		}
		if (found) {
			this->decisionMap[p->getPosition()] = moves;
			found = false;
		}
	}
}

void Computer::loadAvoidCapturePawnMap() {
	for (auto &pair: this->decisionMap) {
		for (auto &posn: pair.second) {
			if (this->getChessBoard()->hasPiece(posn.toString()) && this->getChessBoard()->getPiece(posn.toString())->subType() == PieceType::Pawn) {
				this->deleteFromDecisionMap(pair.first, posn.toString());
			}
		}
	}
}

void Computer::makeLevel1Map() {
	this->loadNormalMovesMap();
}

void Computer::makeLevel2Map() {
	this->loadCheckMovesMap();
	if (!this->decisionMap.empty()) return;
	this->loadCaptureMovesMap();
	if (!this->decisionMap.empty()) return;
	this->loadNormalMovesMap();
}

void Computer::makeLevel3Map() {
	this->loadCheckMovesMap();
	if (!this->decisionMap.empty()) return;
	this->loadAvoidCaptureMovesMap();
	if (!this->decisionMap.empty()) return;
	this->loadCaptureMovesMap();
	if (!this->decisionMap.empty()) return;
	this->loadNormalMovesMap();
}

void Computer::makeLevel4Map() {
	this->loadCheckMovesMap();
	if (!this->decisionMap.empty()) return;
	this->loadCaptureMovesMap();
	if (!this->decisionMap.empty()) {
		this->loadAvoidCapturePawnMap();
	}
	if (this->decisionMap.empty()) {
		this->loadCaptureMovesMap();
	}
	if (!this->decisionMap.empty()) return;
	this->loadNormalMovesMap();
}

void Computer::deleteFromDecisionMap(std::string source, std::string target) {
	for (unsigned int i = 0; i < this->decisionMap[source].size(); ++i) {
		if (this->decisionMap[source][i].toString() == target) {
			this->decisionMap[source].erase(this->decisionMap[source].begin() + i);
		}
	}
	if (this->decisionMap[source].empty()) {
		this->decisionMap.erase(source);
	}
}

vector<Position> Computer::getCheckMoves(Piece *p) {
	vector<Position> checkMoves;
	for (auto &pos: p->getAllAvailableMoves()) {
		try {
			this->makeMove(p->getPosition(), pos.toString());
			if (this->getOpponent()->isChecked()) {
				checkMoves.emplace_back(Position(p->getPosition()));
			}
		} catch (CheckedMove &e) {}
		this->undo();
	}
	return checkMoves;
}
