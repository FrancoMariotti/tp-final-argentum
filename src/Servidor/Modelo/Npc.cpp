//
// Created by franco on 10/6/20.
//

#include "Npc.h"
#include "Movilidad.h"

#define MAX_RANGE 4

Npc::Npc(int lifePoints,Movilidad* movilidad,int x,int y,Mapa& mapa):GameObject(x,y,mapa),mobility(movilidad) {
    mapa.addNpc(this);
}

void Npc::move() {
    Offset offset = findClosestCharacterOffset();
    if (offset.isZero()) {
        offset.randomDir();
    } else {
        offset.approach();
    }

    mobility->move(actual, mapa, offset);
}

Offset Npc::findClosestCharacterOffset() {
    Offset offset(0,0);
    GameObject* enemy = mapa.findClosestCharacter(this->actual, MAX_RANGE);
    if (!enemy) return offset; //como no hay ningun personaje en el rango devuelvo un offset nulo.
    return enemy->getOffset(this->actual);
}

Npc::~Npc() {}