#include "NormalWeapon.h"

NormalWeapon::NormalWeapon(int minDamage,int maxDamage):Weapon(minDamage,maxDamage) {}

int NormalWeapon::attack(Character *enemy, int strength,int level, int &mana,Position &holderPos) {
    if(enemy->distanceTo(holderPos) == 1) {
        int damage = calculateDamage(strength);
        return enemy->receiveDamage(level, damage);
    }
    return 0;
}

NormalWeapon::~NormalWeapon() = default;
