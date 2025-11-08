#include "Compass.h"
#include <string>

using namespace std;

const string name = "Compass";
const char ascii = 'C';

Compass::Compass() {color = "\e[0;33m";}
// Compass::Compass

void Compass::use(PlayerCharacter *&player) {
} // Compass::use
 
char Compass::getChar() {
    return ascii;
} // Compass::getChar
//
string Compass::getName() {
    return name;
} // Compass::getName
