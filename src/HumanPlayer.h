#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "Character.h"
#include "PlayerCharacter.h"
#include <iostream>
#include <string>

class HumanPlayer : public PlayerCharacter {
  public:
	// Constructor
	HumanPlayer();

	// Doubles the score of the Human player.
	virtual int getScore() const override;
};

#endif
