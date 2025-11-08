#include "Merchant.h"
#include <iostream>
#include <string>
using namespace std;

const char ascii = 'M';
const string name = "Merchant";
const int defaultHP = 30;
const int defaultATK = 70;
const int defaultDEF = 5;
const int defaultGold = 0;

Merchant::Merchant() : Enemy(defaultHP, defaultATK, defaultDEF, defaultGold) {
	aggressive = false;
} // Merchant::Merchant

// Displays the Merchant's stats.
void Merchant::displayStats() const {
	cout << "Race: Merchant " << endl;
	cout << "HP: " << HP << ", ATK: " << attack << ", DEF: " << defence << endl;
} // Merchant::displayStats

int Merchant::getNumPot() {
	return numPotions;
} // Merchant::getNumPot
	
void Merchant::setPot(int amount) {
	if (amount < 0) {
		numPotions = 0;
	} else {
		numPotions = amount;
	}
} // Merchant::setPot

char Merchant::getChar() { return ascii; }
// Merchant::getChar

string Merchant::getName() { return name; }
// Merchant::getName
