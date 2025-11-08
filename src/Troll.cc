#include "Troll.h"
#include <iostream>
#include <string>
using namespace std;

const char ascii = 'T';
const string name = "Troll";
const int defaultHP = 120;
const int defaultATK = 25;
const int defaultDEF = 15;
const int defaultGold = 0;

Troll::Troll() : Enemy(defaultHP, defaultATK, defaultDEF, defaultGold) {}
// Troll::Troll

// Displays the Troll's stats.
void Troll::displayStats() const {
	cout << "Race: Merchant " << endl;
	cout << "HP: " << HP << ", ATK: " << attack << ", DEF: " << defence << endl;
} // Troll::displayStats

char Troll::getChar() { return ascii; }
// Troll::getChar

string Troll::getName() { return name; }
// Troll::getName
