#include "Character.h"
#include <iostream>
#include <cmath>

using namespace std;

const int BARRIERSUIT = 2;

Character::Character(int HP, int attack, int defence, int gold):
    HP{HP}, attack{attack}, defence{defence}, gold{gold} {
} // Character::Character

Character::~Character() {}
// Character::~Character

void Character::takeDamage(int damage) {
	cout << "Damage: " << damage << endl;
    HP -= damage;
	if (HP < 0)
		HP = 0;
	cout << getName() << " HP: " << HP << endl;
} // Character::takeDamage

void Character::attackCharacter(Character *target) {
	// Damage calculation logic
	cout << this->getName() << " Attacking " << target->getName() << endl;
	// cerr << damage << " Damage Dealt to " << target->getName() << endl;
	int atk = attack;
	int def = target->getDefence();
	double factor = 100.0 / (100.0 + def);
	double totalDamage = (atk * factor);

	// Checks if the target has the Barrier Suit.
	if (target->getBarrierSuit()) {
		totalDamage = ceil(totalDamage / BARRIERSUIT);
	} else {
		totalDamage = ceil(totalDamage);
	}
	int damage = static_cast<int>(totalDamage);
	target->takeDamage(damage);

} // Character::attackCharacter

int Character::getHP() const {
    return HP;
} // Character::getHP

void Character::setHP(int newHP) {
    HP = newHP;
} // Character::setHP

void Character::setAttack(int newAtt) {
	cout << "Setting Attack" << endl;
    attack = newAtt;
} // Character::setHP

void Character::setDefence(int newDef) {
	cout << "Setting Defence" << endl;
    defence = newDef;
} // Character::setHP

int Character::getAttack() const {
	cout << "base attack: " << attack << endl;
    return attack;
} // Character::getDefence

int Character::getDefence() const {
	cout << "base defence: " << defence << endl;
    return defence;
} // Character::getDefence

void Character::setGold(int newGold) {
	gold = newGold;
} // Character::setGold

int Character::getGold() const {
	return gold;
} // Character::getGold

void Character::setBarrierSuit() {
	hasBarrierSuit = true;
} // Character::setBarrierSuit

bool Character::getBarrierSuit() {
	return hasBarrierSuit;
} // Character::getBarrierSuit
