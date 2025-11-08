#include "Vampire.h"
#include <iostream>
#include <string>
using namespace std;

const char ascii = 'V';
const string name = "Vampire";
const int defaultHP = 50;
const int defaultATK = 25;
const int defaultDEF = 25;
const int defaultGold = 0;

Vampire::Vampire() : Enemy(defaultHP, defaultATK, defaultDEF, defaultGold) {}
// Vampire::Vampire

// Displays the Vampire's stats.
void Vampire::displayStats() const {
	cout << "Race: Dragon " << endl;
	cout << "HP: " << HP << ", ATK: " << attack << ", DEF: " << defence << endl;
} // Vampire::displayStats

char Vampire::getChar() { return ascii; }
// Vampire::getChar

string Vampire::getName() { return name; }
// Vampire::getName
