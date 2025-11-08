#ifndef CHARACTER_H
#define CHARACTER_H
#include "CellObject.h"
#include <string>

class Character : public CellObject {
  protected:
	int HP;
	int attack;
	int defence;
	int gold;
	Category type; // The type of the character (e.g., player or enemy).
	bool hasBarrierSuit = false;

  public:
	// Constructor
	Character(int HP, int attack, int Defence, int gold);

	// Destructor
	virtual ~Character();

	// Display the character's current stats.
	virtual void displayStats() const = 0;

	// Makes the character take damage.
	virtual void takeDamage(int damage);

	// Attacks another character.
	void attackCharacter(Character *target);

	// Returns the character's current HP.
	int getHP() const;

	// Returns the character's current attack.
	int getAttack() const;

	// Returns the character's current defence.
	int getDefence() const;

	// Returns the characters's current Gold.
	virtual int getGold() const;

	// Sets the character's HP.
	virtual void setHP(int newHP);

	// Sets the character's attack.
	virtual void setAttack(int newAtt);

	// Sets the character's Defence.
	virtual void setDefence(int newDef);

	// Sets the character's Gold.
	virtual void setGold(int newGold);

	// Sets the player to have the Barrier Suit.
	void setBarrierSuit();

	// Checks whether or now the character has the Barrier Suit.
	bool getBarrierSuit();	
};

#endif
