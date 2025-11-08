#ifndef MERCHANT_H
#define MERCHANT_H
#include "Enemy.h"
#include <iostream>
#include <string>

class Merchant : public Enemy {
	int numPotions = 3;

  public:
	// Constructor
	Merchant();

	// Displays the Merchant's stats.
	void displayStats() const override;

	int getNumPot();
	
	void setPot(int amount);
	
	char getChar() override;

	std::string getName() override;
};

#endif
