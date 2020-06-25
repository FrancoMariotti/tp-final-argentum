#include "RangeWeapon.h"

RangeWeapon::RangeWeapon(int minDamage, int maxDamage, Range range):Weapon(minDamage,maxDamage) {
    this->range = range;
}

void RangeWeapon::attack(Character *enemy,int strength,int level,int *mana,Position &holderPos) {
    int experience = 0;
    if((range == SHORT && enemy->distanceTo(holderPos) == 1) || range == LONG) {
        int damage = calculateDamage(strength);
        experience = enemy->receiveDamage(level, damage);
    }
}