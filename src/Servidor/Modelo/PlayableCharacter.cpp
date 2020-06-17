#include "PlayableCharacter.h"
#include "Mobility.h"
#include "Game.h"

PlayableCharacter::PlayableCharacter(int lifePoints,int x, int y, Map& map,Game* game): Character(x, y, map),lifePoints(lifePoints),game(game) {
    map.addPlayableCharacter(this);
}

void PlayableCharacter::move(Offset& offset) {
    Position siguiente(this->currPos);
    siguiente.apply(offset);
    map.move(this->currPos,siguiente);
    game->addUpdatePosition(currPos.getX(),currPos.getY());
}

PlayableCharacter::~PlayableCharacter() = default;