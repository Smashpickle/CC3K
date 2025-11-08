#ifndef ITEM_H
#define ITEM_H

#include <string>

// #include "player.h"
#include "CellObject.h"

class PlayerCharacter;

class Item : public CellObject {
  protected:
	bool guarded = false;

  public:
	// Pure virtual method that subclasses must implement to define the
	//   effect of the item.
	virtual void use(PlayerCharacter *&player) = 0;

	Category getCtgy() override;

	virtual ~Item() = default;

	void turnOffGuarded();

	bool isGuarded();
};

#endif
