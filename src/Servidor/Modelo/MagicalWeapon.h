#ifndef ARGENTUM_MAGICALWEAPON_H
#define ARGENTUM_MAGICALWEAPON_H

#include "Weapon.h"

class MagicalWeapon: public Weapon {
    int cost;
    public:
        MagicalWeapon(int minDamage,int maxDamage,int cost);
        void attack(Character *enemy,int strength,int level,int *mana,Position &holderPos) override;
        ~MagicalWeapon() override;
};


#endif //ARGENTUM_MAGICALWEAPON_H
