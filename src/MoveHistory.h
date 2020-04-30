#ifndef _MOVEHISTORY_H_
#define _MOVEHISTORY_H_

#include <string>

class Piece;

class MoveHistory final {
	std::string source;
	std::string target;
	std::string source2;
	std::string target2;
	Piece* movedPiece;
	Piece* movedPiece2;
	Piece* capturedPiece;
	Piece* originalPiece;
	bool _hasCapturedPiece = false;
	bool _isCastling = false;
	bool _isPromoteMove = false;
public:
	MoveHistory(std::string s, std::string t, Piece *m);
	MoveHistory(std::string s, std::string t, Piece *m, Piece *m2);
	MoveHistory(std::string s, std::string t, std::string s2, std::string t2, Piece *m, Piece *m2);
	MoveHistory(std::string s, std::string t, Piece *m, Piece *m2, bool isPromote);
	MoveHistory(std::string s, std::string t, Piece *m, Piece *m2, Piece *m3);
	bool hasCapturedPiece(); // returns true if there a capture pieces in past move
	Piece *getMovedPiece(); // returns the moved piece, used only if past move captured an opponent's piece.
	Piece *getCapturedPiece(); // returns the captured piece
	std::string getSource(); // returns the starting position of the past move
	std::string getTarget(); // returns the ending position of the past move
	bool isCastling(); // returns true if the past move is a castling move
	bool isPromoteMove(); // returns true if the past move is a pawn promotion move
	std::string getSource2(); // used if past move is a castling move, which will get the starting position of the involved rook's starting position
	std::string getTarget2(); // used if past move is a castling move, which will return the ending position of the involved rook's ending position.
	Piece *getMovedPiece2(); // used if past move is a castling move, which will get the involved rook object
	Piece *getOriginalPiece(); // used if past move is a pawn promotion, which will get the involved pawn object before the promotion
	virtual ~MoveHistory();
};

#endif
