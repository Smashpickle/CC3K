#ifndef DWARFPLAYER_H
#define DWARFPLAYER_H
#include "PlayerCharacter.h"
#include <iostream>
#include <string>

class DwarfPlayer : public PlayerCharacter {
  public:
	// Constructor
	DwarfPlayer();

	// Gold is doubled in value.
	virtual void addGold(int amount) override;
};

#endif
