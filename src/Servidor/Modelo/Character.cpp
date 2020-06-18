#include "Character.h"

Character::Character(int x,int y,Map& map,int constitution,
        int strength,int agility,int intelligence):currPos(x,y),map(map),
        calculator(0, 0, 0, 0,
                0, 0){
    this->constitution = constitution;
    this->strength = strength;
    this->agility = agility;
    this->intelligence = intelligence;
}

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

Character::~Character() = default;

