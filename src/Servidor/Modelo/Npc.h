#ifndef ARGENTUM_NPC_H
#define ARGENTUM_NPC_H
#include "Map.h"
#include "Character.h"
#include "Equippable.h"
#include "NormalWeapon.h"
#include "Protection.h"
#include <string>

class Map;

class Npc : public Character {
    int mana;
    std::string specie;
    NormalWeapon weapon;
    Protection armour;
    int defend(int damage) override;
    void attack(Character* character) override;
    int calculateNpcGoldDrop(int npcMaxLp);
    bool shouldDrop(int probability);
    int updateTime;
public:
    Npc(std::string id,Map* map,Position &initialPosition, int constitution,
            int strength,int agility,int intelligence, int level, std::string specie, int minDamage,
            int maxDamage, int minDefense, int maxDefense,int raceLifeFactor,int classLifeFactor,int raceManaFactor,
            int classManaFactor,int recoveryFactor,int meditationRecoveryFactor,Observer* observer);
    void move(float looptime);
    int receiveDamage(int enemyLevel, int damage) override;
    int receiveAttackFrom(PlayableCharacter *enemy) override;

    ~Npc() override;
};



#endif //ARGENTUM_NPC_H
