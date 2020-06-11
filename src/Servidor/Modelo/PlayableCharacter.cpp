//
// Created by franco on 10/6/20.
//

#include "PlayableCharacter.h"

PlayableCharacter::PlayableCharacter(int vida,Movilidad* movilidad,float x,float y,Mapa& mapa):GameObject(x,y,mapa),mobility(movilidad) {
    mapa.agregar(this);
}

void PlayableCharacter::mover(Direccion *direccion) {
    this->mobility->mover(this->posicion,this->mapa,direccion);
}