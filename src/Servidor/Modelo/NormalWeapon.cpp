//
// Created by franco on 18/6/20.
//

#include "NormalWeapon.h"

NormalWeapon::NormalWeapon(int minDamage,int maxDamage,RangeWeapon range) {
    this->minDamage = minDamage;
    this->maxDamage = maxDamage;
    this->range = range;
}

int NormalWeapon::attack(Character *enemy, int strength,int level, int *mana, Position &holderPos) {
    int damage = calculateDamage(strength);
    if(range == LONG) return 0;
    return enemy->receiveDamage(level,damage);
}

NormalWeapon::~NormalWeapon() {}
