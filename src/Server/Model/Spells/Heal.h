//
// Created by franco on 29/6/20.
//

#ifndef ARGENTUM_HEAL_H
#define ARGENTUM_HEAL_H

#include "SpellType.h"

class Heal: public SpellType {
public:
    int use(Character *owner,Character *target, int strength, int level,int damage) override;
};


#endif //ARGENTUM_HEAL_H
