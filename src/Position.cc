#include "Position.h"
#include <sstream>

using namespace std;

Position::Position(int r, int c): row{r}, col{c} {}

Position::Position(string posn) {
	stringstream ss{posn};
	char colLetter;
	char rowLetter;
	ss.get(colLetter);
	ss.get(rowLetter);
	this->col = colLetter - 97;
	this->row = rowLetter - '0' - 1;
}

Position::~Position() {}

string Position::toString() {
	stringstream ss;
	char letter = 'a';
	letter += col;
	ss << letter << row + 1;
	return ss.str();
}

bool Position::operator==(Position const &other) const {
	return this->row == other.row && this->col == other.col;
};

bool Position::operator==(Position &&other) {
	return this->row == other.row && this->col == other.col;
};

bool Position::operator!=(Position const &other) const {
	return !(*this == other);
}

bool Position::operator!=(Position &&other) {
	return !(*this == other);
}

ostream& operator<<(ostream &out, Position &m) {
	return out << m.toString();
}

ostream& operator<<(ostream &out, Position &&m) {
	return out << m.toString();
}
