#include <iostream>
#include <string>
#include "DwarfPlayer.h"

using namespace std;

const int dwarfHP = 100;
const int dwarfATT = 20;
const int dwarfDEF = 30;
const int lowestHP = 1;
static const int startGold = 0;
const int adjustmentGold = 2;
const string dwarfName = "Dwarf";

DwarfPlayer::DwarfPlayer() : PlayerCharacter {dwarfHP, dwarfATT, 
										  dwarfDEF, startGold} {
	this->MaxHP = dwarfHP;
	this->addedAttack = 0;
	this->addedDefence = 0;
	this->name = dwarfName;	
} // DwarfPlayer::DwarfPlayer

void DwarfPlayer::addGold(int amount) {
    int adjustGold = amount * adjustmentGold;
    gold += adjustGold;
} // DwarfPlayer::addGold
