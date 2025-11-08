#include "Cell.h"
#include "PlayerCharacter.h"
#include <iostream>
#include <string>

using namespace std;

const char ascii = '@';
const int zeroHP = 0;
const int NOGOLD = 1;
const int CANTBUY = 2;
const int FULLHP = 3;
const int AGGRO = 4;
const int SUCCESS = 5;
const int POTIONPRICE = 2;
const int NOPOTS = 0;

PlayerCharacter::PlayerCharacter(int HP, int attack, int defence, int gold) :
	Character{HP, attack, defence, gold} {
		color = "\e[0;34m";
} // PlayerCharacter::PlayerCharacter

PlayerCharacter::~PlayerCharacter() {}
// PlayerCharacter::~PlayerCharacter

void PlayerCharacter::setMaxHP(int newMaxHP) {
	MaxHP = newMaxHP;
} // PlayerCharacter::setMaxHP

Category PlayerCharacter::getCtgy() {
    return Category::Player;
} // Character::getCtgy

char PlayerCharacter::getChar() {
	return ascii;
} // PlayerCharacter::getChar

int PlayerCharacter::getMaxHP() const {
	return MaxHP;
} // PlayerCharacter::getMaxHP

string PlayerCharacter::getName() {
	return name;
} // PlayerCharacter::getName

void PlayerCharacter::addGold(int amount) {
    gold += amount;
} // PlayerCharacter::addGold

void PlayerCharacter::heal(int amount) {
    if (HP + amount > MaxHP) {
		HP = MaxHP;
	} else if (HP + amount < zeroHP) {
		HP = zeroHP;
	} else {
		HP += amount;
	}
} // PlayerCharacter::heal

void PlayerCharacter::buff(int buffAtk, int buffDef) {
	addedAttack = (buffAtk + addedAttack < -attack) ? -attack :
													  buffAtk + addedAttack;
	addedDefence = (buffDef + addedDefence < -defence) ? -defence :
													  buffDef + addedDefence;
} // PlayerCharacter::buff

int PlayerCharacter::buyFrom(Merchant *merchant) {
	cout << this->getName() << " Buying from " << merchant->getName() << endl;

	// Checks the current gold of the player.
	int currGold = this->getGold();

	if (merchant->isAggro()) {
		return AGGRO;
	}

	if (currGold < POTIONPRICE) {
		return NOGOLD;
	} else if (merchant->getNumPot() <= NOPOTS) {
		return CANTBUY;	
	} else if (this->getHP() == this->getMaxHP()) {
		return FULLHP;
	} else {
		merchant->setPot(merchant->getNumPot() - 1);
		cout << merchant->getName() << " has " << merchant->getNumPot() <<
			" potion(s) left!" << endl;
		this->heal(this->getMaxHP());
		this->setGold(this->getGold() - POTIONPRICE);
		merchant->setGold(this->getGold() + POTIONPRICE);
		return SUCCESS;
	}
} // PlayerCharacter::buyFrom


void PlayerCharacter::removePotionEffects() {
	addedAttack = 0;
	addedDefence = 0;
} // PlayerCharacter::removePotionEffects

void PlayerCharacter::displayStats() const {
	cout << "Race: " << name << " Gold: " << gold << endl;
	cout << "HP: " << HP << endl;
	cout << "Atk: " << attack + addedAttack << endl;
	cout << "Def: " << defence + addedDefence << endl;
} // PlayerCharacter::displayStats

int PlayerCharacter::getScore() const {
	return this->getGold();
} // PlayerCharacter::getScore
