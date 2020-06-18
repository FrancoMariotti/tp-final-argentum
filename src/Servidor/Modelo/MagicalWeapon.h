#ifndef ARGENTUM_MAGICALWEAPON_H
#define ARGENTUM_MAGICALWEAPON_H
#include "Weapon.h"

class MagicalWeapon: public Weapon {
    int minDamage;
    int maxDamage;
    int cost;
    public:
        MagicalWeapon();
        void attack(Character enemy, Position holderPos) override;
        ~MagicalWeapon();
};


#endif //ARGENTUM_MAGICALWEAPON_H
