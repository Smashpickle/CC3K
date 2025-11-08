#ifndef GOBLIN_H
#define GOBLIN_H
#include "Enemy.h"
#include <iostream>
#include <string>

class Goblin : public Enemy {
  public:
	// Constructor
	Goblin();

	// Displays the Goblin's stats.
	void displayStats() const override;

	char getChar() override;

	std::string getName() override;
};

#endif
