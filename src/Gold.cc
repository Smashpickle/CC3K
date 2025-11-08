#include "Gold.h"
#include <iostream>
#include <string>


using namespace std;

const string name = "Gold";
const char ascii = 'G';

Gold::Gold(int a, bool g) : amount(a) { color = "\e[0;33m"; guarded = g;}
// Gold::Gold

bool Gold::isAccessible() const { return !guarded; }
// Gold::isAccessible

void Gold::use(PlayerCharacter *&player) {
	if (guarded) {
		// Guarded item – cannot pick it up until its guardian is dead.
		cout << "The dragon guarding this hoard is still alive!" << endl;
		return;
	}
	player->addGold(amount);
} // Gold::use

string Gold::getName() { return name; }
// Gold::getName

char Gold::getChar() { return ascii; }
// Gold::getChar
