#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>
#include "Observer.h"

class Subject {
	std::vector<Observer*> observers;
public:
	void attach(Observer *o);
	void detach(Observer *o);
	void notifyObservers();
	virtual ~Subject() = 0;
};

#endif
