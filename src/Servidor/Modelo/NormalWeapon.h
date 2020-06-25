//
// Created by franco on 18/6/20.
//

#ifndef ARGENTUM_COMMONWEAPON_H
#define ARGENTUM_COMMONWEAPON_H

#include "Weapon.h"

class NormalWeapon : public Weapon {
    public:
        NormalWeapon(int minDamage,int maxDamage);
        int attack(Character *enemy,int strength,int level,int &mana,Position &holderPos)  override;
        ~NormalWeapon() override;
};


#endif //ARGENTUM_COMMONWEAPON_H
