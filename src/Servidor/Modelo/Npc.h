#ifndef ARGENTUM_NPC_H
#define ARGENTUM_NPC_H
#include "Character.h"
#include "Equippable.h"
#include "NormalWeapon.h"
#include "Protection.h"
#include <string>

//class Map;

class Npc : public Character {
    float mana;
    float updateTime;
    std::string specie;
    NormalWeapon weapon;
    Protection armour;
    Merchant* merchant;
    std::vector<std::string> possiblePotionsToDrop;
    std::vector<std::string> possibleItemsToDrop;
private:
    int defend(int damage);
    void attack(Character* character) override;
    float calculateNpcGoldDrop();
    bool shouldDrop(float probability);
    void die();
public:
    Npc(const std::string& id,Map* map,Position &initialPosition, int constitution,
            int strength,int agility,int intelligence, int level, std::string specie, int minDamage,
            int maxDamage, int minDefense, int maxDefense,int raceLifeFactor,int classLifeFactor,int raceManaFactor,
            int classManaFactor,int recoveryFactor,int meditationRecoveryFactor,Observer* observer,
            std::vector<std::string> potionsToDrop, std::vector<std::string> itemsToDrop);
    void move(float loopTime);
    int receiveDamage(int enemyLevel, int damage) override;
    int receiveAttackFrom(PlayableCharacter *enemy) override;
    void addMerchant(Merchant* newMerchant);
    ~Npc() override;

};

#endif //ARGENTUM_NPC_H
