#include "PlayableCharacter.h"
#include "Mobility.h"

PlayableCharacter::PlayableCharacter(int lifePoints,int x, int y, Map& map): Character(x, y, map) {
    map.addPlayableCharacter(this);
}

void PlayableCharacter::move(Offset& offset) {
    Position siguiente(this->currPos);
    siguiente.apply(offset);
    map.move(this->currPos,siguiente);
}

PlayableCharacter::~PlayableCharacter() = default;