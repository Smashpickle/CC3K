#include "Phoenix.h"
#include <iostream>
#include <string>
using namespace std;

const char ascii = 'X';
const string name = "Phoenix";
const int defaultHP = 50;
const int defaultATK = 35;
const int defaultDEF = 20;
const int defaultGold = 0;

Phoenix::Phoenix() : Enemy(defaultHP, defaultATK, defaultDEF, defaultGold) {}
// Phoenix::Phoenix

// Displays the Phoenix's stats.
void Phoenix::displayStats() const {
	cout << "Race: Phoenix " << endl;
	cout << "HP: " << HP << ", ATK: " << attack << ", DEF: " << defence << endl;
} // Phoenix::displayStats

char Phoenix::getChar() { return ascii; }
// Phoenix::getChar

string Phoenix::getName() { return name; }
// Phoenix::getName
