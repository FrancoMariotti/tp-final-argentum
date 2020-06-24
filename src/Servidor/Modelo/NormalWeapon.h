//
// Created by franco on 18/6/20.
//

#ifndef ARGENTUM_COMMONWEAPON_H
#define ARGENTUM_COMMONWEAPON_H

#include "Weapon.h"

enum RangeWeapon {SHORT,LONG};

class NormalWeapon : public Weapon {
    //Range* range;
    RangeWeapon range;
    public:
        //NormalWeapon(int minDamage,int maxDamage,Range* range);
        NormalWeapon(int minDamage,int maxDamage,RangeWeapon range);
        int attack(Character *enemy,int strength,int level,int *mana,Position &holderPos) override;
        ~NormalWeapon() override;
};


#endif //ARGENTUM_COMMONWEAPON_H
