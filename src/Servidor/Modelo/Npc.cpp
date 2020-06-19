#include "Npc.h"
#include "Mobility.h"

//CREO QUE NO HARIA FALTA QUE EL NPC TUVIESE LA CALCULADORA,PODRIAMOS PONERLA DIRECTAMENTE EN EL PLAYABLE CHARACTER
Npc::Npc(int lifePoints, Mobility* mobility, int x, int y,int constitution,
         int strength,int agility,int intelligence, int level, std::string specie):
         Character(lifePoints,x, y,constitution,strength,agility,intelligence,
                 0, 0, 0, 0,
                 0, 0),mobility(mobility), specie(specie) {
    this->level = level;
}

void Npc::move(Map* map) {
    mobility->move(currPos, map);
}

void Npc::attack(Character* character) {
    //TODAVIA NO LO IMPLEMENTE
}

Npc::~Npc() {
    delete this->mobility;
}