//
// Created by franco on 29/6/20.
//

#include "Damage.h"
Damage::Damage() {}

int Damage::use(Character *target, int strength, int level, int damage) {
    return target->receiveDamage(level,damage);
}

Damage::~Damage() {}