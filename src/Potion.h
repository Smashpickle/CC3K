#ifndef POTION_H
#define POTION_H

#include "Item.h"
#include "PlayerCharacter.h"
#include <string>

class Potion : public Item {
	int healingAmount;
	int boostATK;
	int boostDEF;

  public:
	// Constructor
	Potion(int healingAmount, int boostATK, int boostDEF);
	
	// Applys the potion's effects.
	void use(PlayerCharacter *&player) override;

	std::string getName() override;

	char getChar() override;
};

#endif
