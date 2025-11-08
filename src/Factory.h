#ifndef FACTORY_H
#define FACTORY_H
#include "BarrierSuit.h"
#include "Compass.h"
#include "Dragon.h"
#include "DwarfPlayer.h"
#include "ElfPlayer.h"
#include "Goblin.h"
#include "Gold.h"
#include "HumanPlayer.h"
#include "Merchant.h"
#include "OrcPlayer.h"
#include "Phoenix.h"
#include "Potion.h"
#include "Stairs.h"
#include "Troll.h"
#include "Vampire.h"
#include "Werewolf.h"
#include <string>

class Item;
class PlayerCharacter;
class Enemy;

Item *createItem(const std::string &name);
PlayerCharacter* createPlayerCharacter(const std::string &name);
Enemy* createEnemy(const std::string &name);

#endif
