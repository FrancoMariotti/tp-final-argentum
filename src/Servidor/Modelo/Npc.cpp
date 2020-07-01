#include "Npc.h"
#include <utility>
#include <Proxy/src/common_message_structs.h>
#include "PlayableCharacter.h"
#include "Servidor/Common/Utils.h"
#include "Drop.h"
#include "Map.h"

#define GOLD_DROP_PROBABILITY 0.8
#define POTION_DROP_PROBABILITY 0.01
#define OBJECT_DROP_PROBABILITY 0.01
#define MAX_RANGE 4
#define NPC_UPDATE_TIME 600


Npc::Npc(const std::string& id,Map* map,Position &initialPosition,int constitution,
         int strength,int agility,int intelligence, int level, std::string specie, int minDamage
        , int maxDamage, int minDefense, int maxDefense,int raceLifeFactor,int classLifeFactor,int raceManaFactor,
         int classManaFactor,int recoveryFactor,int meditationRecoveryFactor,Observer* observer):
        Character(id,map,initialPosition,constitution,strength,agility,intelligence,level,
                  raceLifeFactor, classLifeFactor, raceManaFactor, classManaFactor,
                  recoveryFactor, meditationRecoveryFactor,observer),
        weapon("npcWeapon", minDamage,maxDamage, 0),
        armour("npcArmour", minDefense,maxDefense, ARMOUR, 0){
    this->specie = std::move(specie);
    this->mana = 0;
    this->updateTime = 0;
    spawn_character_t  spawn = {initialPosition.getX(),initialPosition.getY(),id};
    map->registerNpcSpawn(spawn);
}

float Npc::calculateNpcGoldDrop() {
    float random = Utils::random_real_number(0.01,0.2);
    return random * calculateMaxLife();
}

bool Npc::shouldDrop(float probability) {
    int n = 100;
    int result = Utils::random_int_number(0,n);
    return result < (probability * n);
}


void Npc::move(float loopTime) {
    updateTime += loopTime;
    if(updateTime >= NPC_UPDATE_TIME){
        Offset offset(0,0);

        auto* enemy = (PlayableCharacter*)map->findClosestCharacter(currPos, MAX_RANGE);
        bool enemyFound = (enemy != nullptr);
        if (enemyFound) {
            offset = enemy->getOffset(currPos);
            offset.approach();
        } else {
            offset.randomDir();
        }
        Position next(currPos);
        next.apply(offset);
        map->move(currPos,next);
        observer->notifyMovementNpcUpdate(id,currPos.getX(),currPos.getY());
        updateTime = 0;
        if(enemyFound) {
            this->attack(enemy);
        }
    }

}

int Npc::receiveDamage(int enemyLevel, int damage) {
    int xpEarned = 0;

    if (dodge()) {
        return xpEarned;
    }

    damage = defend(damage);
    lifePoints -= damage;
    xpEarned = calculateAttackXp(damage,enemyLevel);

    if (lifePoints <= 0) {
        die();
        int maxLifePoints = (int)calculateMaxLife();
        xpEarned += calculateKillXp(maxLifePoints,enemyLevel);
    }

    return xpEarned;
}

int Npc::defend(int damage) {
    int defense = armour.randomize();
    int result = damage - defense;
    if (result < 0) return 0;
    return result;
}

void Npc::attack(Character* character) {
    weapon.attack(character,strength,level, mana,currPos);
}

int Npc::receiveAttackFrom(PlayableCharacter *enemy) {
    return enemy->attackTo(this);
}

void Npc::die() {
    Drop drop(currPos);

    if(shouldDrop(GOLD_DROP_PROBABILITY)) {
        int gold = (int)calculateNpcGoldDrop();
        drop.addGold(gold);
    }

    if(shouldDrop(POTION_DROP_PROBABILITY)) {
        //CREATE POTION
        //drop.addEquippable(gold);
    }

    if(shouldDrop(OBJECT_DROP_PROBABILITY)) {
        //CREATE RANDOM OBJECT
        //drop.addEquippable(gold);
    }

    map->addDrop(drop);
    map->removeNpc(id);
}

Npc::~Npc() = default;



