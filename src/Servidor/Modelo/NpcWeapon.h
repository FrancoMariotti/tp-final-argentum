//
// Created by franco on 24/6/20.
//

#ifndef ARGENTUM_NPCWEAPON_H
#define ARGENTUM_NPCWEAPON_H


#include "Weapon.h"

class NpcWeapon : public Weapon {
public:
    NpcWeapon(int minDamage,int maxDamage);
    int attack(Character *enemy,int strength,int level,int *mana,Position &holderPos) override;
    ~NpcWeapon() override;
};


#endif //ARGENTUM_NPCWEAPON_H
