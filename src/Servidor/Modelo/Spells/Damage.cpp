//
// Created by franco on 29/6/20.
//

#include "Damage.h"
Damage::Damage() = default;

int Damage::use(Character* owner,Character *target, int strength, int level, int damage) {
    if(owner == target) return 0;
    return target->receiveDamage(level,damage);
}

Damage::~Damage() = default;