//
// Created by franco on 25/6/20.
//

#ifndef ARGENTUM_RANGEWEAPON_H
#define ARGENTUM_RANGEWEAPON_H


#include "Weapon.h"

class RangeWeapon: public Weapon {
    public:
        RangeWeapon(std::string name, int minDamage,int maxDamage, int goldCost);
        int attack(Character* owner,Character *enemy,int strength,int level,float &mana,
                Position &holderPos) override;
        ~RangeWeapon() override = default;
};


#endif //ARGENTUM_RANGEWEAPON_H
