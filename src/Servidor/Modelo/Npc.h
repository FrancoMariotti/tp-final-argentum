//
// Created by franco on 10/6/20.
//

#ifndef ARGENTUM_NPC_H
#define ARGENTUM_NPC_H

#include "Map.h"
#include "Character.h"
#include "Mobility.h"
#include "Equippable.h"
#include "NormalWeapon.h"
#include "NpcWeapon.h"
#include <string>

class Mobility;
class Map;

class Npc : public Character {
    Mobility *mobility;
    std::string specie;
    NpcWeapon weapon;
    Equippable armour;
    virtual int defend(int damage) override;
    public:
        Npc(Map* map,Mobility *mobility,int lifePoints,Position &initialPosition, int constitution,
            int strength,int agility,int intelligence, int level, std::string specie, int minDamage,
            int maxDamage, int minDefense, int maxDefense,int raceLifeFactor,int classLifeFactor,int raceManaFactor,
            int classManaFactor,int recoveryFactor,int meditationRecoveryFactor);
        void move();
        void attack(Character* character) override;
        //int calculateNpcGoldDrop(int npcMaxLp);
        //bool shouldDrop(int probability);
        ~Npc() override;
};



#endif //ARGENTUM_NPC_H
