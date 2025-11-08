#include "Subject.h"
#include "Observer.h"
#include <vector>
#include <string>

using namespace std;

void Subject::attach(Observer *o) { observers.emplace_back(o); }
// Subject::attach

void Subject::notifyObservers() {
    for (auto &ob : observers) ob->notify(*this);
} // Subject::notifyObservers

void Subject::clear() {
    observers.clear();
} // Subject::clear
