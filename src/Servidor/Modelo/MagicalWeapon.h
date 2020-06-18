#ifndef ARGENTUM_MAGICALWEAPON_H
#define ARGENTUM_MAGICALWEAPON_H
#include "Weapon.h"

class magicalWeapon: public Weapon {
    private:
        int minDamage;
        int maxDamage;
        int cost;
};


#endif //ARGENTUM_MAGICALWEAPON_H
