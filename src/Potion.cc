#include "Potion.h"
#include <string>

using namespace std;

const string name = "Potion";
const char ascii = 'P';

Potion::Potion(int healingAmount, int boostATK, int boostDEF)
    : healingAmount(healingAmount), boostATK{boostATK}, boostDEF{boostDEF} {
	color = "\e[0;32m";
} // Potion::Potion

void Potion::use(PlayerCharacter *&player) {
	player->heal(healingAmount);
	// Level specific buffs/debuffs
	if (boostATK != 0 || boostDEF != 0) {
		player->buff(boostATK, boostDEF);
	}
} // Potion::use

string Potion::getName() { return name; }
// Potion::getName

char Potion::getChar() { return ascii; }
// Potion::getChar
