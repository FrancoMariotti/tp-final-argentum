//
// Created by franco on 23/6/20.
//
#include "Weapon.h"

int Weapon::calculateDamage(int strength) {
    int range = this->maxDamage - minDamage;
    return strength * (std::rand() % range + minDamage);
}

