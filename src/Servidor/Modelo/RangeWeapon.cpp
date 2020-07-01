#include "RangeWeapon.h"
#include "Log.h"
#include "PlayableCharacter.h"
#include "Npc.h"

RangeWeapon::RangeWeapon(std::string name, int minDamage, int maxDamage, int goldCost)
    :Weapon(name, minDamage,maxDamage, goldCost) {
}

int RangeWeapon::attack(Character *enemy,int strength,int level,float &mana,Position &holderPos) {
    int damage = calculateDamage(strength);
    return enemy->receiveDamage(level, damage);
}
