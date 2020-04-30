#include "Tracker.h"

using namespace std;

Tracker::Tracker() {}

Tracker::~Tracker() {}

void Tracker::push(MoveHistory h) {
	this->_stack.emplace_back(h);
}

MoveHistory Tracker::pop() {
	if (this->length() == 0) {
		throw NoHistoryStored();
	}
	MoveHistory h = this->_stack.back();
	this->_stack.pop_back();
	return h;
}

int Tracker::length() {
	return this->_stack.size();
}
