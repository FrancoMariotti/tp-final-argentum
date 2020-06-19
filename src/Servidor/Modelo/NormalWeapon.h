//
// Created by franco on 18/6/20.
//

#ifndef ARGENTUM_COMMONWEAPON_H
#define ARGENTUM_COMMONWEAPON_H

#include "Weapon.h"
#include "Range.h"

class NormalWeapon : public Weapon {
    int minDamage;
    int maxDamage;
    Range* range;
    public:
        NormalWeapon(int minDamage,int maxDamage,Range* range);
        void attack(Character *enemy,int strength,int &mana,Position &holderPos,Calculator calc) override;
        ~NormalWeapon() override;
};


#endif //ARGENTUM_COMMONWEAPON_H
