#include "Npc.h"
#include "Mobility.h"

Npc::Npc(int lifePoints, Mobility* mobility, int x, int y, Map& map,int constitution,
         int strength,int agility,int intelligence):Character(x, y, map,constitution,strength,agility,intelligence),
         lifePoints(lifePoints),mobility(mobility) {
    map.addNpc(this);
}

void Npc::move() {
    mobility->move(currPos, map);
}

Npc::~Npc() {
    delete this->mobility;
}