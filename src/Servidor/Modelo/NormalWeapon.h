//
// Created by franco on 18/6/20.
//

#ifndef ARGENTUM_COMMONWEAPON_H
#define ARGENTUM_COMMONWEAPON_H

#include "Weapon.h"

class commonWeapon : public Weapon {
    int minDamage;
    int maxDamage;
    Range range;
public:
    virtual void attack(Character enemy, Position holderPos) override;
};


#endif //ARGENTUM_COMMONWEAPON_H
