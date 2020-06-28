#ifndef ARGENTUM_NPC_H
#define ARGENTUM_NPC_H

#include "Map.h"
#include "Character.h"
#include "Equippable.h"
#include "NormalWeapon.h"
#include "Protection.h"
#include <string>

class Mobility;
class Map;

class Npc : public Character {
    std::string specie;
    NormalWeapon weapon;
    Protection armour;
    int defend(int damage) override;
    void attack(Character* character) override;
public:
    Npc(Map* map,Position &initialPosition, int constitution,
            int strength,int agility,int intelligence, int level, std::string specie, int minDamage,
            int maxDamage, int minDefense, int maxDefense,int raceLifeFactor,int classLifeFactor,int raceManaFactor,
            int classManaFactor,int recoveryFactor,int meditationRecoveryFactor);
    void move();
    int calculateNpcGoldDrop(int npcMaxLp);
    bool shouldDrop(int probability);
    ~Npc() override;
};



#endif //ARGENTUM_NPC_H
