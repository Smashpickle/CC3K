#include "CellObject.h"
#include <vector>
#include "Cell.h"

using namespace std;

vector<int> CellObject::getCord() {
    vector<int> retval = {r, c};
    return retval;
} // CellObject::getCord

void CellObject::setCord(int r, int c) {
    this->r = r;
    this->c = c;
} // CellObject::setCord

string CellObject::getColorChar() {
    string retval = color;
    retval.push_back(getChar());
    retval += RESET;
    return retval;
} // CellObject::getColorChar
