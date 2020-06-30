#include "Npc.h"
#include <utility>
#include <Proxy/src/common_message_structs.h>
#include "PlayableCharacter.h"

#define MAX_RANGE 4
#define NPC_UPDATE_TIME 800


Npc::Npc(std::string id,Map* map,Position &initialPosition,int constitution,
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

int Npc::calculateNpcGoldDrop(int npcMaxLp) {
    double modifier = double(rand()) / (double(RAND_MAX) + 0.2);
    return modifier * npcMaxLp;
}

bool Npc::shouldDrop(int probability) {
    int n = 100;
    int result = std::rand() % (n+1);
    return result < (probability * n);
}


void Npc::move(float looptime) {
    Offset offset(0,0);

    auto* enemy = (PlayableCharacter*)map->findClosestCharacter(currPos, MAX_RANGE);
    bool enemyFound = (enemy != nullptr);
    if (enemyFound) {
        offset = enemy->getOffset(currPos);
        offset.approach();
    } else {
        offset.randomDir();
    }

    updateTime += looptime;
    if(updateTime >= NPC_UPDATE_TIME){
        Position next(currPos);
        next.apply(offset);
        map->move(currPos,next);
        observer->notifyMovementNpcUpdate(id,currPos.getX(),currPos.getY());
        updateTime = 0;
    }

    if(enemyFound) {
        this->attack(enemy);
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
        int maxLifePoints = calculateMaxLife();
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

Npc::~Npc() = default;



