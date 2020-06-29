//
// Created by franco on 29/6/20.
//

#ifndef ARGENTUM_HEAL_H
#define ARGENTUM_HEAL_H


#include "SpellType.h"

class Heal: public SpellType {
public:
    int giveAbilityTo(MagicalWeapon *weapon,Character *target,int strength,int level);
};


#endif //ARGENTUM_HEAL_H
