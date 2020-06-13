//
// Created by franco on 10/6/20.
//

#include "Npc.h"
#include "Mobility.h"

#define MAX_RANGE 4

Npc::Npc(int lifePoints, Mobility* mobility, int x, int y, Map& map): GameObject(x, y, map), mobility(mobility) {
    map.addNpc(this);
}

void Npc::move() {
    Offset offset = findClosestCharacterOffset();
    if (offset.isZero()) {
        offset.randomDir();
    } else {
        offset.approach();
    }

    mobility->move(currPos, map, offset);
}

Offset Npc::findClosestCharacterOffset() {
    Offset offset(0,0);
    GameObject* enemy = map.findClosestCharacter(this->currPos, MAX_RANGE);
    if (!enemy) return offset; //como no hay ningun personaje en el rango devuelvo un offset nulo.
    return enemy->getOffset(this->currPos);
}

Npc::~Npc() {
    delete this->mobility;
}