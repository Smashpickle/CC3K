#ifndef ORCPLAYER_H
#define ORCPLAYER_H
#include "Character.h"
#include "PlayerCharacter.h"
#include <string>

class OrcPlayer : public PlayerCharacter {
	float ogGold = 0;
  public:
	// Constructor
	OrcPlayer();

	// Gold is worth half value.
	virtual void addGold(int amount) override;

	virtual void displayStats() const override;
};

#endif
