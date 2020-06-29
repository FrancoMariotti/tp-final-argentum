#include "MagicalWeapon.h"

MagicalWeapon::MagicalWeapon(std::string name, int minDamage, int maxDamage, int cost)
    :Weapon(name, minDamage,maxDamage) {
    this->cost = cost;
}

int MagicalWeapon::attack(Character *enemy,int strength,int level,int &mana,Position &holderPos) {
    if(mana < cost) return 0;
    mana -= cost;
    int damage = calculateDamage(strength);
    return enemy->receiveDamage(level,damage);
}

MagicalWeapon::~MagicalWeapon() = default;
