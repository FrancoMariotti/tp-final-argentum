//
// Created by franco on 29/6/20.
//

#ifndef ARGENTUM_SPELLTYPE_H
#define ARGENTUM_SPELLTYPE_H

#include "Character.h"
#include "MagicalWeapon.h"

class SpellType {
public:
    virtual int use(Character *target,int strength,int level,int damage) = 0;
};


#endif //ARGENTUM_SPELLTYPE_H
