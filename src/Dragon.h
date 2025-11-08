#ifndef DRAGON_H
#define DRAGON_H
#include "Enemy.h"
#include <iostream>
#include <string>

class Dragon : public Enemy {
	std::vector<std::pair<int, int>> aggroZone;
	std::vector<std::pair<int, int>> guardedItemsCoord;
	bool hasBeenAttacked = false;

  public:
	// // Constructor
	Dragon();

	void setAggroZone(std::vector<std::pair<int, int>> zone);

	std::vector<std::pair<int, int>> getAggroZone();
	
	void setAggro(bool aggro);

	void setAttacked(bool aggro);

	bool getAttacked();

	void setGuarded(std::vector<std::pair<int, int>> guarded);

	std::vector<std::pair<int, int>> getGuarded();

	// Displays the Dragon's stats.
	void displayStats() const override;

	char getChar() override;

	std::string getName() override;
};

#endif
