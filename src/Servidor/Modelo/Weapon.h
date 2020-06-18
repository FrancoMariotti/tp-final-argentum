//
// Created by franco on 18/6/20.
//

#ifndef ARGENTUM_WEAPON_H
#define ARGENTUM_WEAPON_H
#include "Character.h"

class Weapon {
    public:
        virtual void attack(Character enemy, Position holderPos) = 0;
};
#endif //ARGENTUM_WEAPON_H
