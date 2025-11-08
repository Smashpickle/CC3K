#ifndef PHOENIX_H
#define PHOENIX_H
#include "Enemy.h"
#include <iostream>
#include <string>

class Phoenix : public Enemy {
  public:
	// Constructor
	Phoenix();

	// Displays the Phoenix's stats.
	void displayStats() const override;

	char getChar() override;

	std::string getName() override;
};

#endif
