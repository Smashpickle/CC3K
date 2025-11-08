#ifndef COMPASS_H
#define COMPASS_H
#include "Factory.h"
#include "Item.h"
#include "Floor.h"
#include "PlayerCharacter.h"
#include "Stairs.h"
#include <string>

class Compass : public Item {
	Stairs * stairs;
  public:
	// Constructor
	Compass();

	// Uses the compass to reveal the Stairscase.
	void use(PlayerCharacter *&player) override;

	char getChar() override;

	std::string getName() override;
};

#endif
