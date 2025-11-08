#include <string>
#include "Stairs.h"

using namespace std;

const string name = "Stairs";
const char fakeAscii = '.';
const char ascii = '\\';

Stairs::Stairs(): showStairs{false} {}
// Stairs::Stairs

void Stairs::use(PlayerCharacter*& player) {
} // Stairs::use

string Stairs::getName() {
    return name;
} // Stairs::getName

char Stairs::getChar() {
    if (showStairs) {
        color = "\e[0;34m";
        return ascii;
    } else {
        return fakeAscii;
    }
} // Stairs::getChar

void Stairs::reveal() {
    showStairs = true;
} // Stairs::reveal
