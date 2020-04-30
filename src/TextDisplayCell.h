#ifndef _TEXTDISPLAYCELL_H_
#define _TEXTDISPLAYCELL_H_

#include <iostream>
#include "Observer.h"
#include "Cell.h"

class TextDisplayCell: public Observer {
	Cell *cell;
	char _char;
public:
	TextDisplayCell();
	virtual ~TextDisplayCell();
	void notify() override;
	char getState() const;
	void setCell(Cell *c);
	friend std::ostream &operator<<(std::ostream &out, const TextDisplayCell &tdc);
};

#endif
