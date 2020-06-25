#include "Npc.h"
#include <utility>

#define MAX_RANGE 4


Npc::Npc(Map* map,int lifePoints,Position &initialPosition,int constitution,
         int strength,int agility,int intelligence, int level, std::string specie, int minDamage
         , int maxDamage, int minDefense, int maxDefense,int raceLifeFactor,int classLifeFactor,int raceManaFactor,
         int classManaFactor,int recoveryFactor,int meditationRecoveryFactor):
         Character(map,lifePoints,initialPosition,constitution,strength,agility,intelligence,level,
                 raceLifeFactor, classLifeFactor, raceManaFactor, classManaFactor,
                 recoveryFactor, meditationRecoveryFactor),
         weapon(minDamage,maxDamage),
         armour(minDefense,maxDefense){
    this->specie = std::move(specie);
}

void Npc::move() {
    Offset offset(0,0);

    Character* enemy = map->findClosestCharacter(currPos, MAX_RANGE);
    if (!enemy) {
        offset.randomDir();
    } else {
        offset = enemy->getOffset(currPos);
        offset.approach();
    }

    Position next(currPos);
    next.apply(offset);
    map->move(currPos,next);
}

int Npc::defend(int damage) {
    int defense = armour.randomize();
    int result = damage - defense;
    if (result < 0) return 0;
    return result;
}

void Npc::attack(Character* character) {
    weapon.attack(character,strength,level, nullptr,currPos);
}

Npc::~Npc() {}


/*int Npc::calculateNpcGoldDrop(int npcMaxLp) {
    double modifier = double(rand()) / (double(RAND_MAX) + 0.2);
    return modifier * npcMaxLp;
}

bool Npc::shouldDrop(int probability) {
    int n = 100;
    int result = std::rand() % (n+1);
    return result < (probability * n);
}*/


