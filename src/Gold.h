#ifndef GOLD_H
#define GOLD_H
#include "Item.h"
#include "PlayerCharacter.h"
#include "Enemy.h"
#include <string>

class Gold : public Item {
	int amount;

  public:
	// Constructor
	Gold(int a, bool g = false);

    bool isAccessible() const;

	// Add gold to the player's total.
	void use(PlayerCharacter *&player) override;

	std::string getName() override;

	char getChar() override;
};

#endif
