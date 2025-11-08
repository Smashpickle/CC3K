#include <string>
#include <iostream>
#include "OrcPlayer.h"

using namespace std;

const int OrcHP = 180;
const int OrcATT = 30;
const int OrcDEF = 25;
const int lowestHP = 1;
static const int startGold = 0;
const int adjustmentGold = 2;
const string orcName = "Orc";

OrcPlayer::OrcPlayer() : PlayerCharacter {OrcHP, OrcATT, OrcDEF, startGold} {
	this->MaxHP = OrcHP;
	this->addedAttack = 0;
	this->addedDefence = 0;
	this->name = orcName;
} // OrcPlayer::OrcPlayer

void OrcPlayer::addGold(int amount) {
    int adjustGold = amount / adjustmentGold;
	ogGold += adjustGold;
	gold = ogGold;
} // OrcPlayer::addGold

void OrcPlayer::displayStats() const {
	cout << "Race: " << name << " Gold: " << gold << endl;
	cout << "HP: " << HP << endl;
	cout << "Atk: " << attack + addedAttack << endl;
	cout << "Def: " << defence + addedDefence << endl;
} // PlayerCharacter::displayStats
