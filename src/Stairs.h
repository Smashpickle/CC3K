#ifndef STAIRS_H
#define STAIRS_H
#include <string>
#include "Item.h"
#include "PlayerCharacter.h"

class Stairs: public Item {
    bool showStairs;

  public:
    Stairs();
    // Lets the Player advance to the next floor.
    void use(PlayerCharacter*& player) override;

    std::string getName() override;

    char getChar() override;

    void reveal();
};

#endif
