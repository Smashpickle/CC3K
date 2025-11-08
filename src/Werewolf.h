#ifndef WEREWOLF_H
#define WEREWOLF_H
#include "Enemy.h"
#include <iostream>
#include <string>

class Werewolf : public Enemy {
  public:
	// Constructor
	Werewolf();

	// Displays the Werewolf's stats.
	void displayStats() const override;

	char getChar() override;

	std::string getName() override;
};

#endif
