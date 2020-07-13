#include "RangeWeapon.h"
#include "Log.h"
#include "PlayableCharacter.h"
#include "Npc.h"

RangeWeapon::RangeWeapon(std::string name, int id, int minDamage, int maxDamage, int goldCost)
    :Weapon(name, id, minDamage,maxDamage, goldCost) {
}

int RangeWeapon::attack(Character* owner,Character *enemy,int strength,int level,float &mana,Position &holderPos) {
    if(owner == enemy) return 0;
    int damage = calculateDamage(strength);
    return enemy->receiveDamage(level, damage);
}
