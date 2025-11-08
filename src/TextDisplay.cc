#include "Subject.h"
#include "TextDisplay.h"
#include <iostream>
#include "Cell.h"

using namespace std;

const int FIRSTROW = 0;
const int LASTROW = 25;
const int FIRSTCOLUMN = 0;
const int LASTCOLUMN = 79;
const std::string RESET = "\e[0m";

TextDisplay::TextDisplay() {
    theDisplay.resize(LASTROW);
    for (auto& row : theDisplay) {
        row.resize(LASTCOLUMN, "~");
    }
} // TextDisplay::TextDisplay

void TextDisplay::notify(const Subject& whoNotified)  {
    Info info = whoNotified.getInfo();

    if (info.cellObject) {
        cerr << "Row:" << info.r << " Col:" << info.c << endl;
        cerr << "ASCII:" << info.cellObject->getColorChar() << RESET << endl;
    }
    const Cell& cell = static_cast<const Cell&> (whoNotified);
    theDisplay[info.r][info.c] = cell.getColorChar();
} // TextDisplay::notify

ostream& operator<< (ostream& out, TextDisplay& td) {
    for (vector<string>& row : td.theDisplay) {
        for (string& cell : row) {
            out << cell;
        }
        out << RESET<< endl;
    }
    return out;
}
