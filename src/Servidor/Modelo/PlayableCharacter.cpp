#include <iostream>
#include "PlayableCharacter.h"
#include "Mobility.h"
#include "Game.h"

PlayableCharacter::PlayableCharacter(int lifePoints, int x, int y, Map& map,Game* game,int constitution,
        int strength,int agility,int intelligence):Character(x, y, map,constitution,strength,agility,intelligence),
        lifePoints(lifePoints),game(game) {
    map.addPlayableCharacter(this);
}

void PlayableCharacter::move(Offset& offset) {
    std::cout <<"posicion antes:"<<std::endl;
    this->printPosition();
    Position siguiente(this->currPos);
    siguiente.apply(offset);
    map.move(this->currPos,siguiente);
    std::cout <<"posicion despues:"<<std::endl;
    this->printPosition();
    game->addUpdatePosition(currPos.getX(),currPos.getY());
}

PlayableCharacter::~PlayableCharacter() = default;