#include "Npc.h"

#include <utility>
#include "Mobility.h"

//CREO QUE NO HARIA FALTA QUE EL NPC TUVIESE LA CALCULADORA,PODRIAMOS PONERLA DIRECTAMENTE EN EL PLAYABLE CHARACTER
Npc::Npc(Map* map,Mobility* mobility,int lifePoints,Position &initialPosition,int constitution,
         int strength,int agility,int intelligence, int level, std::string specie, int minDamage
         , int maxDamage, int minDefense, int maxDefense,int raceLifeFactor,int classLifeFactor,int raceManaFactor,
         int classManaFactor,int recoveryFactor,int meditationRecoveryFactor):
         Character(map,lifePoints,initialPosition,constitution,strength,agility,intelligence,level,
                 raceLifeFactor, classLifeFactor, raceManaFactor, classManaFactor,
                 recoveryFactor, meditationRecoveryFactor),
         mobility(mobility),
         weapon(minDamage,maxDamage),
         armour(minDefense,maxDefense){
    this->specie = std::move(specie);
}

void Npc::move() {
    mobility->move(currPos, map);
}

int Npc::defend(int damage) {
    int defense = armour.randomize();
    int result = damage - defense;
    if (result < 0) return 0;
    return result;
}

void Npc::attack(Character* character) {
    weapon.attack(character,strength,level,nullptr,currPos);
}

Npc::~Npc() {
    delete this->mobility;
}


/*int Npc::calculateNpcGoldDrop(int npcMaxLp) {
    double modifier = double(rand()) / (double(RAND_MAX) + 0.2);
    return modifier * npcMaxLp;
}

bool Npc::shouldDrop(int probability) {
    int n = 100;
    int result = std::rand() % (n+1);
    return result < (probability * n);
}*/


