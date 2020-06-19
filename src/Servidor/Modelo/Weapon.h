//
// Created by franco on 18/6/20.
//

#ifndef ARGENTUM_WEAPON_H
#define ARGENTUM_WEAPON_H

#include "Character.h"
class Character;
class Calculator;

class Weapon {
    public:
        virtual void attack(Character *enemy,int strength,int &mana,Position &holderPos,Calculator calc) = 0;
        virtual ~Weapon() = default;
};
#endif //ARGENTUM_WEAPON_H
