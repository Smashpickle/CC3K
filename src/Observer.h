#ifndef OBSERVER_H
#define OBSERVER_H
#include <string>

class Subject;

class Observer {
  public:
	// Pass in the Subject that called notify()
	virtual void notify(const Subject &whoNotified) = 0;
	// Destructor
	virtual ~Observer() = default;
};

#endif
