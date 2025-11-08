#include "Item.h"

Category Item::getCtgy() {
    return Category::Item;
} // Item::getCtgy

void Item::turnOffGuarded() {
    guarded = false;
} // Item::turnOffGuarded

bool Item::isGuarded() {
    return guarded;
} // Item::isGuarded
