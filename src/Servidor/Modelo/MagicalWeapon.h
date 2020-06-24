#ifndef ARGENTUM_MAGICALWEAPON_H
#define ARGENTUM_MAGICALWEAPON_H
#include "Weapon.h"

class MagicalWeapon: public Weapon {
    int cost;
    public:
        MagicalWeapon(int minDamage,int maxDamage,int cost);
        int attack(Character *enemy,int strength,int level,int *mana,Position &holderPos) override;
        ~MagicalWeapon();
};


#endif //ARGENTUM_MAGICALWEAPON_H
