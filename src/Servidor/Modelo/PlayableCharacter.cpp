//
// Created by franco on 10/6/20.
//

#include "PlayableCharacter.h"
#include "Mobility.h"

PlayableCharacter::PlayableCharacter(int lifePoints,int x, int y, Map& map): GameObject(x, y, map) {
    map.addPlayableCharacter(this);
}

void PlayableCharacter::move(Offset& offset) {
    this->movable.move(this->currPos,this->map,offset);
}

PlayableCharacter::~PlayableCharacter() = default;