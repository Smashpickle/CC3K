#ifndef VAMPIRE_H
#define VAMPIRE_H
#include "Enemy.h"
#include <iostream>
#include <string>

class Vampire : public Enemy {
  public:
	// Constructor
	Vampire();

	// Displays the Vampire's stats.
	void displayStats() const override;

	char getChar() override;

	std::string getName() override;
};

#endif
