#ifndef _TRACKER_H_
#define _TRACKER_H_

#include <vector>
#include <stdexcept>
#include "MoveHistory.h"

class NoHistoryStored: public std::exception {};

class Tracker {
	std::vector<MoveHistory> _stack;
public:
	Tracker();
	virtual ~Tracker();
	void push(MoveHistory h); // store history h into tracker
	MoveHistory pop(); // returns the last history stored
	int length(); // returns the length of history moves.
};

#endif
