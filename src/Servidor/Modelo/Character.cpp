#include "Character.h"

Character::Character(int x,int y,Map& map):currPos(x,y),map(map) {}

bool Character::collideWith(Position& objPos) {
    return (this->currPos == objPos);
}

int Character::distanceTo(Position pos) {
    return this->currPos.distanceTo(pos);
}

Offset Character::getOffset(Position initialPos) {
    Position final(currPos);
    return final - initialPos;
}

void Character::printPosition() {
    currPos.print();
}

Character::~Character() {}

