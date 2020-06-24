#include "NpcWeapon.h"

NpcWeapon::NpcWeapon(int minDamage, int maxDamage) {
    this->minDamage = minDamage;
    this->maxDamage = maxDamage;
}

int NpcWeapon::attack(Character *enemy, int strength, int level, int *mana, Position &holderPos) {
    if(enemy->distanceTo(holderPos) == 1) {
        int damage = calculateDamage(strength);
        enemy->receiveDamage(level, damage);
    }
    return 0;
}

NpcWeapon::~NpcWeapon() = default;
