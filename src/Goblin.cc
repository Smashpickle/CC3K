#include "Goblin.h"
#include <iostream>
#include <string>
using namespace std;

const char ascii = 'N';
const string name = "Goblin";
const int defaultHP = 70;
const int defaultATK = 5;
const int defaultDEF = 10;
const int defaultGold = 0;

Goblin::Goblin(): Enemy(defaultHP, defaultATK, defaultDEF, defaultGold) {}

// Displays the Goblin's stats.
void Goblin::displayStats() const {
	cout << "Race: Goblin " << " Gold: " << gold << endl;
	cout << "HP: " << HP << endl;
	cout << "Atk: " << attack << endl;
	cout << "Def: " << defence << endl;
} // Goblin::displayStats

char Goblin::getChar() {
	return ascii;
} // Goblin::getChar

string Goblin::getName() {
	return name;
} // Goblin::getName
