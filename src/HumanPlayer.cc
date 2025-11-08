#include <string>
#include <iostream>
#include "HumanPlayer.h"

using namespace std;

const int humanHP = 140;
const int humanATT = 20;
const int humanDEF = 20;
const int lowestHP = 1;
const int doubleScore = 2;
static const int startGold = 0;
const string humanName = "Human";

HumanPlayer::HumanPlayer() : PlayerCharacter {humanHP, humanATT, 
											  humanDEF, startGold} {
	this->MaxHP = humanHP;
	this->addedAttack = 0;
	this->addedDefence = 0;
	this->name = humanName;	
} // HumanPlayer::HumanPlayer

int HumanPlayer::getScore() const {
	return this->getGold() * doubleScore;
} // HumanPlayer::getScore
