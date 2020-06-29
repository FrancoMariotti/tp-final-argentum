//
// Created by franco on 29/6/20.
//

#include "Damage.h"
Damage::Damage() {}

int Damage::giveAbilityTo(MagicalWeapon *weapon, Character *target, int strength, int level) {
    return weapon->use(this,target,strength,level);
}

Damage::~Damage() {}