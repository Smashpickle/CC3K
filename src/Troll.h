#ifndef TROLL_H
#define TROLL_H
#include "Enemy.h"
#include <iostream>
#include <string>

class Troll : public Enemy {
  public:
	// Constructor
	Troll();

	// Displays the Troll's stats.
	void displayStats() const override;

	char getChar() override;

	std::string getName() override;
};

#endif
