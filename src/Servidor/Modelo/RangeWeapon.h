//
// Created by franco on 25/6/20.
//

#ifndef ARGENTUM_RANGEWEAPON_H
#define ARGENTUM_RANGEWEAPON_H


#include "Weapon.h"
enum Range {SHORT,LONG};

class RangeWeapon: public Weapon {
    Range range;
    public:
        RangeWeapon(int minDamage,int maxDamage,Range range);
        int attack(Character *enemy,int strength,int level,int &mana,Position &holderPos) override;
};


#endif //ARGENTUM_RANGEWEAPON_H
