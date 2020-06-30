//
// Created by franco on 29/6/20.
//

#include "Damage.h"
Damage::Damage() {}

int Damage::useOn(Character *target, int strength, int level, MagicalWeapon *weapon) {
    return weapon->use(this,target,strength,level);
}

Damage::~Damage() {}