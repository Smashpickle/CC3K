#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H
#include "Character.h"
#include "Merchant.h"
#include <string>

class Cell;

class PlayerCharacter : public Character {
  protected:
  	int MaxHP;
	int addedAttack = 0;
	int addedDefence = 0;
	std::string name;
	bool hasBarrierSuit = false;
  public:
	friend class Item;

	// Constructor
	PlayerCharacter(int HP, int attack, int defence, int gold);

	// Destructor
	virtual ~PlayerCharacter() = 0;

	// Sets the MaxHP of the player.
	void setMaxHP(int newMaxHP);

	// std::vector<int> action() override;
	Category getCtgy() override;

	// Returns the ASCII value representation of the current player.
	char getChar() override;

	// Returns the MaxHP of the current player.
	int getMaxHP() const;

	// Returns the name of the current character.
	virtual std::string getName() override;

	// Adds gold to the player's inventory.
	virtual void addGold(int amount);

	// Heal/damages the player.
	virtual void heal(int amount);

	// Buffs/debuffs the player.
	virtual void buff(int buffAtk, int buffDef);

	// Buys from a merchant
	int buyFrom(Merchant *merchant);

	// Removes the buff/debuff potion's effects.
	void removePotionEffects();

	// Displays the current stats for the player.
	virtual void displayStats() const override;

	// Gets the final score of the player.
	virtual int getScore() const;
};

#endif
