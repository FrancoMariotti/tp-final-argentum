#include "RangeWeapon.h"
#include "Log.h"
#include "PlayableCharacter.h"
#include "Npc.h"

RangeWeapon::RangeWeapon(std::string name, int minDamage, int maxDamage, Range range, int goldCost)
    :Weapon(name, minDamage,maxDamage, goldCost) {
    this->range = range;
}

int RangeWeapon::attack(Character *enemy,int strength,int level,int &mana,Position &holderPos) {
    if((range == SHORT && enemy->distanceTo(holderPos) == 1) || range == LONG) {
        int damage = calculateDamage(strength);
        return enemy->receiveDamage(level, damage);
    }
    return 0;
}