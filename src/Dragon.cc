#include "Dragon.h"
#include <iostream>
#include <string>
using namespace std;

const string name = "Dragon";
const char ascii = 'D';
const int defaultHP = 150;
const int defaultATK = 20;
const int defaultDEF = 20;
const int defaultGold = 0;

Dragon::Dragon() : Enemy(defaultHP, defaultATK, defaultDEF, defaultGold) {
	moveable = false;
	aggressive = false;
} // Dragon::Dragon

void Dragon::setAggroZone(vector<pair<int, int>> zone) {
	aggroZone = zone;
} // Dragon::setAggroZone

void Dragon::setAggro(bool aggro) {
	aggressive = aggro;
} // Dragon::setAggro

vector<pair<int, int>> Dragon::getAggroZone() {
	return aggroZone;
} // Dragon::getAggroZone

void Dragon::setAttacked(bool aggro) {
	hasBeenAttacked = aggro;
} // Dragon::setAttacked

bool Dragon::getAttacked() {
	return hasBeenAttacked;
} // Dragon::getAttacked


void Dragon::setGuarded(vector<pair<int, int>> guarded) {
	guardedItemsCoord = guarded;
} // Dragon::setGuarded

vector<pair<int, int>> Dragon::getGuarded() {
	return guardedItemsCoord;
} // Dragon::getGuarded

// Displays the Dragon's stats.
void Dragon::displayStats() const {
	cout << "Race: Dragon " << endl;
	cout << "HP: " << HP << ", ATK: " << attack << ", DEF: " << defence << endl;
} // Dragon::displayStats

char Dragon::getChar() { return ascii; }
// Dragon::getChar

string Dragon::getName() { return name; }
// Dragon::getName
