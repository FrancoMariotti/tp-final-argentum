#include "Npc.h"
#include <utility>

#define MAX_RANGE 4


Npc::Npc(Map* map,Position &initialPosition,int constitution,
         int strength,int agility,int intelligence, int level, std::string specie, int minDamage
         , int maxDamage, int minDefense, int maxDefense,int raceLifeFactor,int classLifeFactor,int raceManaFactor,
         int classManaFactor,int recoveryFactor,int meditationRecoveryFactor):
         Character(map,initialPosition,constitution,strength,agility,intelligence,level,
                 raceLifeFactor, classLifeFactor, raceManaFactor, classManaFactor,
                 recoveryFactor, meditationRecoveryFactor),
         weapon("npcWeapon", minDamage,maxDamage),
         armour("npcArmour", minDefense,maxDefense, ARMOUR){
    this->specie = std::move(specie);
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


void Npc::move() {
    Offset offset(0,0);

    Character* enemy = map->findClosestCharacter(currPos, MAX_RANGE);
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

    if(enemyFound) this->attack(enemy);
}

int Npc::defend(int damage) {
    int defense = armour.randomize();
    int result = damage - defense;
    if (result < 0) return 0;
    return result;
}

void Npc::attack(Character* character) {
    //deberiamos agregarle el mana al npc y que sea cero
    int mana = 0;
    weapon.attack(character,strength,level, mana,currPos);
}

Npc::~Npc() {}



