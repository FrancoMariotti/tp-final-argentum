//
// Created by franco on 10/6/20.
//

#include <cstdlib>
#include "Npc.h"
#include "PlayableCharacter.h"

Npc::Npc(int vida, Movilidad *movilidad, float x, float y, Mapa &mapa):GameObject(x,y,mapa),mobility(movilidad) {
    mapa.agregar(this);
}

void Npc::move() {
    int xOffset = 0;
    int yOffset = 0;
    std::vector<int> offset = this->findClosestCharacter();
    if (offset.empty()) {
        offset = this->getRandomDir();
        xOffset = offset[0];
        yOffset = offset[1];
    } else {
        if (abs(offset[0]) >= abs(offset[1])) {
            xOffset = offset[0] / (abs(offset[0]);
        } else {
            yOffset = offset[1] / (abs(offset[1]);
        }
    }
    //CAMBIAR EL MOVER DE MOVILIDAD
    mobility.move(posicion, mapa, xOffset, yOffset);
}

std::vector<int> Npc::getRandomDir() {
    int xOffset, yOffset;
    std::vector<int> posibleOffsets = {-1, 0, 1};
    xOffset = posibleOffsets[rand()%3];
    yOffset = posibleOffsets[rand()%3];
    std::vector<int> offset = {xOffset, yOffset};
    return offset;
}

std::vector<int> Npc::findClosestCharacter() {
    PlayableCharacter* enemy = mapa.findClosestCharacter(this->posicion, 3);
    if (!enemy) return std::vector<int>(); //como no hay ningun personaje en el rango devuelvo un vector vacio
    //EL METODO GETOFFSET ESTA DECLARADO EN GAMEOBJECT PERO NO ESTA IMPLEMENTADO TODAVIA ,DEFINIR SU LOGICA
    std::vector<int> offset = enemy->getOffset(this->posicion);
    return offset;
}

Npc::~Npc() {}