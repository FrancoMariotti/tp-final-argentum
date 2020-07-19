//
// Created by franco on 29/6/20.
//

#ifndef ARGENTUM_SPELLTYPE_H
#define ARGENTUM_SPELLTYPE_H

#include "Servidor/Modelo/Character/Character.h"
#include "Servidor/Modelo/Equippables/MagicalWeapon.h"

class SpellType {
public:
    virtual ~SpellType() = default;
    virtual int use(Character* owner,Character *target,int strength,int level,int damage) = 0;
};


#endif //ARGENTUM_SPELLTYPE_H
