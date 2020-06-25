#ifndef ARGENTUM_WEAPON_H
#define ARGENTUM_WEAPON_H

#include "Character.h"

class Character;

class Weapon {
    protected:
        int minDamage;
        int maxDamage;
        int calculateDamage(int strength);
    public:
        Weapon(int minDamage,int maxDamage);
        virtual int attack(Character *enemy,int strength,int level,int &mana,Position &holderPos) = 0;
        virtual ~Weapon() = default;
};


#endif //ARGENTUM_WEAPON_H
