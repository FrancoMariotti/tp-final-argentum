#include "NormalWeapon.h"

NormalWeapon::NormalWeapon(int minDamage,int maxDamage):Weapon(minDamage,maxDamage) {}

void NormalWeapon::attack(Character *enemy, int strength,int level, int *mana,Position &holderPos) {
    if(enemy->distanceTo(holderPos) == 1) {
        int damage = calculateDamage(strength);
        enemy->receiveDamage(level, damage);
    }
}

NormalWeapon::~NormalWeapon() = default;
