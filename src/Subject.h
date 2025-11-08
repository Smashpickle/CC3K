#ifndef SUBJECT_H
#define SUBJECT_H
#include "Info.h"
#include <string>
#include <vector>

class Observer;

class Subject {
  protected:
	std::vector<Observer *> observers;

  public:
	void attach(Observer *o);

	// Calls notify() on all the Subject's observers.
	void notifyObservers();

	// Returns the current info of the Subject being observed.
	virtual Info getInfo() const = 0;

	virtual ~Subject() = default;

	void clear();
};

#endif
