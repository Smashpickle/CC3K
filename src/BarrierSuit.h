#ifndef BARRIER_SUIT_H
#define BARRIER_SUIT_H
#include "Factory.h"
#include "Item.h"
#include "Enemy.h"
#include "PlayerCharacter.h"
#include <string>

class BarrierSuit : public Item {
  public:
	BarrierSuit();

	// Uses the Barrier Suit to decrease damage taken by 50%.
	void use(PlayerCharacter *&player) override;

	char getChar() override;

	std::string getName() override;
};

#endif
