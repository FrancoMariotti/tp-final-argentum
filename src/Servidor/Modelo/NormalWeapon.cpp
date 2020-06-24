#include "NormalWeapon.h"

NormalWeapon::NormalWeapon(int minDamage,int maxDamage,RangeWeapon range) {
    this->minDamage = minDamage;
    this->maxDamage = maxDamage;
    this->range = range;
}

int NormalWeapon::attack(Character *enemy, int strength,int level, int *mana, Position &holderPos) {
    int experience = 0;
    int damage = calculateDamage(strength);
    if((range == SHORT && enemy->distanceTo(holderPos) == 1) || range == LONG) {
        experience = enemy->receiveDamage(level, damage);
    }
    return experience;
}

NormalWeapon::~NormalWeapon() {}
