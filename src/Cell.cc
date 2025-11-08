#include "Cell.h"
#include "CellObject.h"
#include "Info.h"
#include "iostream"

using namespace std;

Cell::Cell(int r, int c, Type type, int chamberNumber, int chamberOffset,
           CellObject *cellObject)
    : r{r}, c{c}, type{type}, chamberNumber{chamberNumber},
      chamberOffset{chamberOffset}, cellObject{cellObject} {
	  }
// Cell::Cell

Info Cell::getInfo() const {
	Info cellInfo{r, c, type, chamberNumber, chamberOffset, cellObject};
	return cellInfo;
} // Cell::getInfo

Cell::~Cell() {}
// Cell::~Cell

CellObject *Cell::getObject() { return cellObject; }
// Cell::getObject

void Cell::setObject(CellObject *o) {
	cellObject = o;
	if (o) {
		o->setCord(r, c);
	}
	notifyObservers();
} // Cell::setObject

void Cell::removeObject() {
	cellObject = nullptr;
	notifyObservers();
} // Cell::removeObject

string Cell::getColorChar() const {
	if (cellObject != nullptr)
		return cellObject->getColorChar();
	if (type == Type::Ground)
		return ".";
	if (type == Type::WallH)
		return "-";
	if (type == Type::WallV)
		return "|";
	if (type == Type::Way)
		return "#";
	if (type == Type::Hole)
		return " ";
	if (type == Type::Door)
		return "+";
	// if unknown type cell return ? to indicate error
	else
		return "?";
} // Cell::getChar

// Also computes the chamber size
void Cell::spreadChamberNumber(int cn, int *cs,
							   std::vector<std::vector<Cell*>> &vacantChamberCells) {
	// Need to keep track of the cells that have already been visited
	if (type == Type::Ground && this->chamberNumber == -1) {
		*cs += 1;
		vacantChamberCells[cn].push_back(this);
		chamberNumber = cn;
		chamberOffset = *cs;
		for (auto nb : observers) {
			Cell *target = static_cast<Cell *>(nb);
			target->spreadChamberNumber(cn, cs, vacantChamberCells);
		}
	}
} // Cell::spreadChamberNumber

void Cell::setChamberOffset(int co) { chamberOffset = co; }

vector<int> Cell::getCord() {
	vector<int> retval = {r, c};
	return retval;
} // Cell::getCord

void Cell::notify(const Subject &whoNotified) {}
// Cell::notify
