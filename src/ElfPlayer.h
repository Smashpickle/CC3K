#ifndef ELFPLAYER_H
#define ELFPLAYER_H
#include "PlayerCharacter.h"
#include <iostream>
#include <string>

class ElfPlayer : public PlayerCharacter {
  public:
	// Constructor
	ElfPlayer();

	// Buffs/debuffs the player.
	virtual void buff(int buffAtk, int buffDef) override;

	// Gain or lose HP from using a Potion.
	virtual void heal(int amount) override;
};

#endif
