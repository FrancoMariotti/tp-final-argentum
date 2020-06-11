//
// Created by franco on 10/6/20.
//

#include "PlayableCharacter.h"
#include "Movilidad.h"

PlayableCharacter::PlayableCharacter(int lifePoints,Movilidad* movilidad,int x,int y,Mapa& mapa):GameObject(x,y,mapa),mobility(movilidad) {
    mapa.addPlayableCharacter(this);
}

void PlayableCharacter::move(Offset& offset) {
    this->mobility->move(this->actual,this->mapa,offset);
}

PlayableCharacter::~PlayableCharacter() =default;