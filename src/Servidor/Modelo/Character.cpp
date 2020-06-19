#include "Character.h"
#include "Log.h"

Character::Character(int lifePoints,int x,int y,int constitution,
                  int strength,int agility,int intelligence,  int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor)
                  :currPos(x,y), calculator(raceLifeFactor, classLifeFactor, raceManaFactor,
                          classManaFactor,recoveryFactor,meditationRecoveryFactor){
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
    Log* log = Log::instancia();
    log->write("Danio generado por el enemigo:");
    log->writeInt(damage);
    log->write("vida character antes de recibir danio:");
    log->writeInt(this->lifePoints);
    this->lifePoints -= damage;
    log->write("vida character despues de recibir danio:");
    log->writeInt(this->lifePoints);
}

void Character::printPosition() {
    currPos.print();
}

Character::~Character() = default;

