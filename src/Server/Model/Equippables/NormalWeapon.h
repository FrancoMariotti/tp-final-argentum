//
// Created by franco on 18/6/20.
//

#ifndef ARGENTUM_COMMONWEAPON_H
#define ARGENTUM_COMMONWEAPON_H

#include "Weapon.h"
#include "Server/Model/Map/Position.h"

class PlayableCharacter;
class Npc;

class NormalWeapon : public Weapon {
    public:
        NormalWeapon(std::string name, int id, int minDamage,int maxDamage, int goldCost);
        int attack(Character* owner,Character *enemy,int strength,int level,float &mana,Position &holderPos)  override;
        ~NormalWeapon() override;
};


#endif //ARGENTUM_COMMONWEAPON_H
