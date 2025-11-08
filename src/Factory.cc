#include "Factory.h"
#include <string>

using namespace std;

const int loseHP = -10;
const int gainHP = 10;
const int buff = 5;
const int debuff = -5;

const int small = 1;
const int normal = 2;
const int merchant = 4;
const int dragon = 6;

Item *createItem(const string &name) {
	// cerr << "creating Item" << endl;
	if (name == "RHpotion" || name == "0") { // RHpotion
		// cerr << "creating RHpotion" << endl;
		return new Potion(gainHP, 0, 0);
	} else if (name == "BApotion" || name == "1") {

		return new Potion(0, buff, 0);
	} else if (name == "BDpotion" || name == "2") {

		return new Potion(0, 0, buff);
	} else if (name == "PHpotion" || name == "3") {

		return new Potion(loseHP, 0, 0);
	} else if (name == "WApotion" || name == "4") {

		return new Potion(0, debuff, 0);
	} else if (name == "WDpotion" || name == "5") {

		return new Potion(0, 0, debuff);
	} else if (name == "normalGold" || name == "6") {
		// Create a gold item worth 2 gold
		return new Gold(normal);
	} else if (name == "smallGold" || name == "7") {
		// Create a gold item worth 1 gold
		return new Gold(small);
	} else if (name == "merchantGold" || name == "8") {
		// Create a gold item worth 4 gold
		return new Gold(merchant);
	} else if (name == "dragonGold" || name == "9") {
		// Create a gold item worth 6 gold
		Gold *g = new Gold(dragon, true);
        return g;
	} else if (name == "compass" || name == "C") {
		// cerr << "creating compass" << endl;
		return new Compass();
	} else if (name == "barrierSuit" || name == "B") {
		// cerr << "creating barrierSuit" << endl;
		return new BarrierSuit();
	} else if (name == "stairs") {
		// cerr << "creating stairs" << endl;
		return new Stairs();
	} else {
		// If we are here, the string is not an item
		return nullptr;
	}
}

PlayerCharacter *createPlayerCharacter(const string &name) {
	// cerr << "creating Player" << endl;
	if (name == "h") {
		// cerr << "creating HumanPlayer" << endl;
		return new HumanPlayer();
	} else if (name == "e") {
		// cerr << "creating ElfPlayer" << endl;
		return new ElfPlayer();
	} else if (name == "d") {
		// cerr << "creating DwarfPlayer" << endl;
		return new DwarfPlayer();
	} else if (name == "o") {
		// cerr << "creating OrcPlayer" << endl;
		return new OrcPlayer();
	} else {
		return nullptr;
	}
}

Enemy *createEnemy(const string &name) {
	// cerr << "creating Enemy" << endl;
	if (name == "V") {
		// cout << "creating Vampire" << endl;
		return new Vampire();
	} else if (name == "W") {
		// cout << "creating Werewolf" << endl;
		return new Werewolf();
	} else if (name == "T") {
		// cout << "creating Troll" << endl;
		return new Troll();
	} else if (name == "G") {
		// cout << "creating Goblin" << endl;
		return new Goblin();
	} else if (name == "M") {
		// cout << "creating Merchant" << endl;
		return new Merchant();
	} else if (name == "D") {
		// cout << "creating Dragon" << endl;
		return new Dragon();
	} else if (name == "X") {
		// cout << "creating Phoenix" << endl;
		return new Phoenix();
	} else {
		return nullptr;
	}
}
