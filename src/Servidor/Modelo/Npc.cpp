#include "Npc.h"
#include <utility>
#include <iostream>
#include "PlayableCharacter.h"
#include "Drop.h"
#include "Map.h"
#include "Common/Utils.h"
#include "GoldBag.h"
#include "Configuration.h"

Npc::Npc(const std::string& id,Map* map,Position &initialPosition,int constitution,
         int strength,int agility,int intelligence, int level,
         std::string specie, int minDamage, int maxDamage, int minDefense,
         int maxDefense, int raceLifeFactor, int classLifeFactor,
         int raceManaFactor, int classManaFactor, int recoveryFactor,
         int meditationRecoveryFactor, Observer* observer,
         ItemFactory* itemFactoryPtr, std::map<int, item_t>& itemsToDrop):
        Character(id, map, initialPosition, constitution, strength, agility,
                intelligence, level, raceLifeFactor, classLifeFactor,
                raceManaFactor, classManaFactor, recoveryFactor,
                meditationRecoveryFactor,observer),
        weapon("npcWeapon", 0, minDamage,maxDamage, 0),
        armour("npcArmour", 0, minDefense,maxDefense, ARMOUR, 0),
        itemsToDrop(itemsToDrop), config(Configuration::getInstance()) {
    this->specie = std::move(specie);
    this->mana = 0;
    this->updateTime = 0;
    itemFactory = itemFactoryPtr;
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
    if(updateTime >= config.constants["npcUpdateTime"]){
        Offset offset(0,0);

        auto* enemy = (PlayableCharacter*)map->findClosestCharacter(currPos,
                config.constants["maxRange"]);
        bool enemyFound = (enemy != nullptr);
        if (enemyFound) {
            offset = enemy->getOffset(currPos);
            offset.approach();
        } else {
            offset.randomDir();
        }
        Position next(currPos);
        next.apply(offset);
        //Permito que se mueva solo si la nueva posicion no esta dentro de una ciudad
        if (!map->posInCity(next)) map->move(currPos,next);
        observer->notifyMovementNpcUpdate(id,currPos.getX(),currPos.getY());
        updateTime = 0;
        if(enemyFound) {
            this->attack(enemy);
        }
    }
}

int Npc::receiveDamage(int attackerLvl, int damage) {
    int xpEarned = 0;

    if (dodge()) {
        return ATAQUE_ESQUIVADO;
    }

    damage = defend(damage);
    lifePoints -= damage;
    xpEarned = calculateAttackXp(damage,attackerLvl);

    if (lifePoints <= 0) {
        die();
        //int maxLifePoints = (int)calculateMaxLife();
        xpEarned += calculateKillXp(attackerLvl);
    }

    return xpEarned;
}

int Npc::defend(int damage) {
    int defense = armour.randomize();
    std::cout << "puntos de ataque defendidos" << defense << std::endl;
    int result = damage - defense;
    if (result < 0) return 0;
    return result;
}

void Npc::attack(Character* character) {
    weapon.attack(this,character,strength,level, mana,currPos);
}

int Npc::receiveAttackFrom(PlayableCharacter *enemy) {
    return enemy->attackTo(this);
}

void Npc::die() {
    if (shouldDrop(config.constants["goldDropProbability"])) {
        int gold = (int)calculateNpcGoldDrop();
        if (gold > 0) {
            auto* goldBag = new GoldBag(gold);
            Position pos = getClosestPositionToDrop();
            Drop drop(pos, goldBag, "goldBag");
            map->addDrop(drop);
        }
    }
    /*
    if (shouldDrop(POTION_DROP_PROBABILITY)) {
        int randomIndex = Utils::random_int_number(0, possiblePotionsToDrop.size() - 1);
        std::string potionName = possiblePotionsToDrop[randomIndex];

        Equippable* potion = itemFactory->create(item);
        Position pos = getClosestPositionToDrop();
        Drop drop(pos, potion, potionName);
        map->addDrop(drop);
    }
    */
    if (shouldDrop(config.constants["itemDropProbability"])) {
        int randomIndex = Utils::random_int_number(0, itemsToDrop.size() - 1);
        Equippable* item = itemFactory->create(itemsToDrop[randomIndex]);
        Position pos = getClosestPositionToDrop();
        Drop drop(pos, item, item->getName());
        map->addDrop(drop);
    }

    //Envio al cliente los drops a renderizar
    map->updateDropSpawns(observer);
    map->removeNpc(id, observer);
}
/*
void Npc::addMerchant(Merchant* newMerchant) {
    merchant = newMerchant;
}
*/

void Npc::addSpawnInfoTo(std::vector<location_t>& npcSpawns) {
    location_t  spawn = {currPos.getX(),currPos.getY(),id};
    npcSpawns.push_back(spawn);
}

Npc::~Npc() = default;



