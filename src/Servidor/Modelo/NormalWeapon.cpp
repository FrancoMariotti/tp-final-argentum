//
// Created by franco on 18/6/20.
//

#include "NormalWeapon.h"

NormalWeapon::NormalWeapon(int minDamage, int maxDamage, Range *range) {
    this->minDamage = minDamage;
    this->maxDamage = maxDamage;
    this->range = range;
}

void NormalWeapon::attack(Character *enemy, int strength, int &mana, Position &holderPos) {
    int damage = Character::calculateDamage(strength,minDamage,maxDamage);
    range->attack(enemy,holderPos,damage);
}

NormalWeapon::~NormalWeapon() {
    delete range;
}
