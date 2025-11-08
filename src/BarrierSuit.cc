#include "BarrierSuit.h"
#include "Compass.h"
#include "Factory.h"
#include "Item.h"
#include "PlayerCharacter.h"
#include <string>

using namespace std;

const string name = "BarrierSuit";
const char ascii = 'B';

BarrierSuit::BarrierSuit() {color = "\e[0;33m"; guarded = true;}
// BarrierSuit::BarrierSuit

void BarrierSuit::use(PlayerCharacter *&player) {
	if (guarded) {
        std::cout << "The dragon guarding the Barrier Suit is still alive!" << std::endl;
        return;
    }
	player->setBarrierSuit();
} // BarrierSuit::use

string BarrierSuit::getName() { return name; }
// BarrierSuit::getName

char BarrierSuit::getChar() { return ascii; }
// BarrierSuit::getChar
