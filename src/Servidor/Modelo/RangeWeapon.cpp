#include "RangeWeapon.h"
#include "Log.h"

RangeWeapon::RangeWeapon(int minDamage, int maxDamage, Range range):Weapon(minDamage,maxDamage) {
    this->range = range;
}

int RangeWeapon::attack(Character *enemy,int strength,int level,int &mana,Position &holderPos) {
    if((range == SHORT && enemy->distanceTo(holderPos) == 1) || range == LONG) {
        int damage = calculateDamage(strength);
        return enemy->receiveDamage(level, damage);
    }
    return 0;
}