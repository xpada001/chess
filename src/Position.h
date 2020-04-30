#ifndef _POSITION_H_
#define _POSITION_H_

#include <iostream>
#include <string>

class Position {
public:
	int row;
	int col;
	Position(int r, int c);
	Position(std::string posn);
	virtual ~Position();
	std::string toString();
	bool operator==(Position const &other) const;
	bool operator==(Position &&other);
	bool operator!=(Position const &other) const;
	bool operator!=(Position &&other);
	friend std::ostream& operator<<(std::ostream &out, Position &m);
	friend std::ostream& operator<<(std::ostream &out, Position &&m);
};

#endif
