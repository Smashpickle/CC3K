#include "Werewolf.h"
#include <iostream>
#include <string>
using namespace std;

const char ascii = 'W';
const string name = "Werewolf";
const int defaultHP = 120;
const int defaultATK = 30;
const int defaultDEF = 5;
const int defaultGold = 0;

Werewolf::Werewolf() : Enemy(defaultHP, defaultATK, defaultDEF, defaultGold) {}
// Werewolf::Werewolf

// Displays the Werewolf's stats.
void Werewolf::displayStats() const {
	cout << "Race: Dragon " << endl;
	cout << "HP: " << HP << ", ATK: " << attack << ", DEF: " << defence << endl;
} // Werewolf::displayStats

char Werewolf::getChar() { return ascii; }
// Werewolf::getChar

string Werewolf::getName() { return name; }
// Werewolf::getName
