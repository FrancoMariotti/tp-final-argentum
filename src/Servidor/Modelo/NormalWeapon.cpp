//
// Created by franco on 18/6/20.
//

#include "NormalWeapon.h"

CommonWeapon::CommonWeapon(int minDamage, int maxDamage, Range *range) {
    this->minDamage = minDamage;
    this->maxDamage = maxDamage;
    this->range = range;
}

void CommonWeapon::attack(Character *enemy, int strength, int &mana, Position &holderPos, Calculator calc) {
    int damage = calc.damage(strength,minDamage,maxDamage);
    range->attack(enemy,holderPos,damage);
}

CommonWeapon::~CommonWeapon() {}
