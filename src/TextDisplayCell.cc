#include "TextDisplayCell.h"
#include <iostream>

using namespace std;

TextDisplayCell::TextDisplayCell() {}

TextDisplayCell::~TextDisplayCell() {}

void TextDisplayCell::notify() {
	this->_char = this->cell->charRepr();
}

char TextDisplayCell::getState() const {
	return this->_char;
}

void TextDisplayCell::setCell(Cell *c) {
	this->cell = c;
}

ostream &operator<<(ostream &out, const TextDisplayCell &tdc) {
	return out << tdc.getState();
}
