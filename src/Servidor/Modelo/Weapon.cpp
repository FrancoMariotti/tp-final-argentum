#include "Weapon.h"

Weapon::Weapon(int minDamage, int maxDamage) {
    this->minDamage = minDamage;
    this->maxDamage = maxDamage;
}

int Weapon::calculateDamage(int strength) {
    int range = this->maxDamage - minDamage;
    return strength * (std::rand() % range + minDamage);
}

