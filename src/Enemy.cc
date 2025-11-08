#include "Enemy.h"
#include <string>

Enemy::Enemy(int HP, int attack, int defense, int gold) :
    Character(HP, attack, defense, gold) {color = "\e[0;31m"; aggressive = true;}
// Enemy::Enemy

Category Enemy::getCtgy() {
    return Category::Enemy;
} // Enemy::getCtgy

void Enemy::turnOnAggro() {
    aggressive = true;
} // Enemy::turnOnAggro

void Enemy::giveCompass() {
    compass = true;
} // Enemy::giveCompass

bool Enemy::isAggro() {
    return aggressive;
} // Enemy::isAggro

bool Enemy::hasCompass() {
    return compass;
} // Enemy::hasCompass

int Enemy::getCount() {
    return counter;
} // Enemy::getCount

void Enemy::increaseCount() {
    counter++;
} // Enemy::increaseCount

bool Enemy::isMovable() {
    return moveable;
} // Enemy::isMovable
