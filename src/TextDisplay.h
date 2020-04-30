#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include <vector>
#include "TextDisplayCell.h"

class TextDisplay {
	const int size;
	std::vector<std::vector<TextDisplayCell>> gridDisplay;
public:
	TextDisplay(const int size, std::vector<std::vector<Cell>> *grid);
	~TextDisplay();
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
