#ifndef INFO_H
#define INFO_H

#include "Item.h"
#include <utility>

enum class Type { Door, Hole, Way, WallH, WallV, DNE, Ground };

// Information for the cell to return i.e. its type and position in grid.
struct Info {
	int r;
	int c;
	Type type;
	int chamberNumber;
	int chamberOffset;
	// Item* item;
	CellObject *cellObject;

	Info(int r, int c, Type t, int cn, int co, CellObject *object)
	    : r{r}, c{c}, type{t}, chamberNumber{cn}, chamberOffset{co},
	      cellObject{object} {}
};

#endif
