#include "MagicalWeapon.h"

MagicalWeapon::MagicalWeapon(int minDamage, int maxDamage, int cost):Weapon(minDamage,maxDamage) {
    this->cost = cost;
}

void MagicalWeapon::attack(Character *enemy,int strength,int level,int *mana,Position &holderPos) {
    if(*mana < cost) return;
    *mana -= cost;
    int damage = calculateDamage(strength);
     enemy->receiveDamage(level,damage);
}

MagicalWeapon::~MagicalWeapon() = default;
