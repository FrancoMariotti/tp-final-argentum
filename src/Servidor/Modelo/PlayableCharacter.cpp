//
// Created by franco on 10/6/20.
//

#include "PlayableCharacter.h"
#include "Mobility.h"

PlayableCharacter::PlayableCharacter(int lifePoints, Mobility* mobility, int x, int y, Map& map): GameObject(x, y, map), mobility(mobility) {
    map.addPlayableCharacter(this);
}

void PlayableCharacter::move(Offset& offset) {
    this->mobility->move(this->currPos,this->map,offset);
}

PlayableCharacter::~PlayableCharacter() =default;