#include <iostream>
#include <string>
#include "ElfPlayer.h"

using namespace std;

const int elfHP = 140;
const int elfATT = 30;
const int elfDEF = 10;
const int lowestHP = 1;
static const int startGold = 0;
const string elfName = "Elf";

ElfPlayer::ElfPlayer() : PlayerCharacter {elfHP, elfATT, 
										  elfDEF, startGold} {
	this->MaxHP = elfHP;
	this->addedAttack = 0;
	this->addedDefence = 0;
	this->name = elfName;	
} // ElfPlayer::ElfPlayer

void ElfPlayer::buff(int buffAtk, int buffDef) {
	addedAttack = abs(buffAtk) + addedAttack;
	addedDefence = abs(buffDef) + addedDefence;
} // ElfPlayer::buff

void ElfPlayer::heal(int amount) {
	int posiAmount = abs(amount);
    if (HP + posiAmount > MaxHP) {
		HP = MaxHP;
	} else {
		HP += posiAmount;
	}
} // ElfPlayer::heal
