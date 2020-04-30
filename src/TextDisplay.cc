#include <vector>
#include <iostream>
#include <sstream>
#include "TextDisplay.h"
#include "Cell.h"

using namespace std;

TextDisplay::TextDisplay(const int size, vector<vector<Cell>> *grid):
		size{size}, gridDisplay{vector<vector<TextDisplayCell>>(size, vector<TextDisplayCell>(size, TextDisplayCell()))}
		{
			for (int i = 0; i < this->size; ++i) {
				for (int j = 0; j < this->size; ++j) {
					gridDisplay[i][j].setCell(&((*grid)[i][j]));
					(*grid)[i][j].attach(&(gridDisplay[i][j]));
					gridDisplay[i][j].notify();
				}
			}
		}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	int rowCounter = td.size;
	for (auto lt=td.gridDisplay.rbegin(); lt != td.gridDisplay.rend(); ++lt) {
		out << rowCounter-- << ' ';
		for (auto const &c: *lt) {
			out << c;
		}
		out << endl;
	}
	char colLetter = 'a';
	out << "  ";
	for (int i = 0; i < td.size; ++i) {
		out << colLetter;
		colLetter += 1;
	}
	out << endl;
	return out;
}
