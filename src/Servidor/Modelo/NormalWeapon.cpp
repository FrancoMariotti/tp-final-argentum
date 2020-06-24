#include "NormalWeapon.h"

NormalWeapon::NormalWeapon(int minDamage,int maxDamage,RangeWeapon range) {
    this->minDamage = minDamage;
    this->maxDamage = maxDamage;
    this->range = range;
}

int NormalWeapon::attack(Character *enemy, int strength,int level, int *mana, Position &holderPos) {
    int experience = 0;
    if((range == SHORT && enemy->distanceTo(holderPos) == 1) || range == LONG) {
        int damage = calculateDamage(strength);
        experience = enemy->receiveDamage(level, damage);
    }
    return experience;
}

NormalWeapon::~NormalWeapon() {}
