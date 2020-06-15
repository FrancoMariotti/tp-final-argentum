#include "Npc.h"
#include "Mobility.h"

Npc::Npc(int lifePoints, Mobility* mobility, int x, int y, Map& map): Character(x, y, map), mobility(mobility) {
    map.addNpc(this);
}

void Npc::move() {
    mobility->move(currPos, map);
}

Npc::~Npc() {
    delete this->mobility;
}