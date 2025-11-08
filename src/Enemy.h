#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include <string>

class Enemy : public Character {
  protected:
	bool aggressive;
	bool compass = false;
	bool moveable = true;

  public:
	int counter = 0;
	Enemy(int HP, int attack, int Defence, int gold);
	Category getCtgy() override;
	void turnOnAggro();
	void giveCompass();
	bool isAggro();
	bool hasCompass();
	int getCount();
	void increaseCount();
	bool isMovable();
};

#endif
