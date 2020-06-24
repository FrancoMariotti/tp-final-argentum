#include "Npc.h"
#include "Mobility.h"

//CREO QUE NO HARIA FALTA QUE EL NPC TUVIESE LA CALCULADORA,PODRIAMOS PONERLA DIRECTAMENTE EN EL PLAYABLE CHARACTER
Npc::Npc(Map* map,int lifePoints, Mobility* mobility, int x, int y,int constitution,
         int strength,int agility,int intelligence, int level, std::string specie, int minDamage
         , int maxDamage, int minDefense, int maxDefense):
         Character(map,lifePoints,x, y,constitution,strength,agility,intelligence,
                 0, 0, 0, 0,
                 0, 0),mobility(mobility),
                 activeWeapon(minDamage, maxDamage,SHORT),
                 armour(minDefense, maxDefense){
    this->level = level;
    this->specie = specie;
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


int Npc::calculateNpcGoldDrop(int npcMaxLp) {
    double modifier = double(rand()) / (double(RAND_MAX) + 0.2);
    return modifier * npcMaxLp;
}

bool Npc::shouldDrop(int probability) {
    int n = 100;
    int result = std::rand() % (n+1);
    return result < (probability * n);
}


void Npc::attack(Character* character) {
    if (character->distanceTo(currPos) == 1) {
        activeWeapon.attack(character,strength,level,NULL,currPos);
    }
}

Npc::~Npc() {
    delete this->mobility;
}