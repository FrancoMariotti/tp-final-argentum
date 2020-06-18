#include "Character.h"

Character::Character(int lifePoints,int x,int y,Map& map,int constitution,
                  int strength,int agility,int intelligence,  int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor)
                  :currPos(x,y),map(map), calculator(raceLifeFactor, classLifeFactor, raceManaFactor,
                          classManaFactor,recoveryFactor,meditationRecoveryFactor){
    level = 1;
    this->lifePoints = lifePoints;
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

void Character::receiveDamage(int damage) {
    this->lifePoints -= damage;
}

void Character::printPosition() {
    currPos.print();
}

Character::~Character() = default;

