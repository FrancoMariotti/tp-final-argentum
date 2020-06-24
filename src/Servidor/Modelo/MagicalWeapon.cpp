//
// Created by franco on 18/6/20.
//

#include "MagicalWeapon.h"

MagicalWeapon::MagicalWeapon(int minDamage, int maxDamage, int cost) {
    this->minDamage = minDamage;
    this->maxDamage = maxDamage;
    this->cost = cost;
}

int MagicalWeapon::attack(Character *enemy,int strength,int level,int *mana,Position &holderPos) {
    if(*mana < cost) return 0;
    *mana -= cost;
    int damage = calculateDamage(strength);
    return enemy->receiveDamage(level,damage);
}

MagicalWeapon::~MagicalWeapon() {}
