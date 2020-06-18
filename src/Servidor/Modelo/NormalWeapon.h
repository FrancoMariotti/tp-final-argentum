//
// Created by franco on 18/6/20.
//

#ifndef ARGENTUM_COMMONWEAPON_H
#define ARGENTUM_COMMONWEAPON_H

#include "Weapon.h"
#include "Range.h"

class CommonWeapon : public Weapon {
    int minDamage;
    int maxDamage;
    Range* range;
    public:
        CommonWeapon(int minDamage,int maxDamage,Range* range);
        void attack(Character enemy, Position holderPos) override;
        ~CommonWeapon();
};


#endif //ARGENTUM_COMMONWEAPON_H
