#include "Npc.h"
#include "Mobility.h"

//CREO QUE NO HARIA FALTA QUE EL NPC TUVIESE LA CALCULADORA,PODRIAMOS PONERLA DIRECTAMENTE EN EL PLAYABLE CHARACTER
Npc::Npc(int lifePoints, Mobility* mobility, int x, int y,int constitution,
         int strength,int agility,int intelligence, int level, std::string specie, int minDamage
         , int maxDamage, int minDefense, int maxDefense):
         Character(lifePoints,x, y,constitution,strength,agility,intelligence,
                 0, 0, 0, 0,
                 0, 0),mobility(mobility), specie(specie),
                 minDamage(minDamage), maxDamage(maxDamage),
                 armour(minDefense, maxDefense){
    this->level = level;
}

void Npc::move(Map* map) {
    mobility->move(currPos, map);
}

int Npc::defend(int damage) {
    int defense = armour.randomize();
    int result = damage - defense;
    if (result < 0) return 0;
    return result;
}

void Npc::attack(Character* character) {
    if (character->distanceTo(currPos) == 1) {
        int damage = Character::calculateDamage(strength, minDamage, maxDamage);
        character->receiveDamage(damage);
    }
}

Npc::~Npc() {
    delete this->mobility;
}