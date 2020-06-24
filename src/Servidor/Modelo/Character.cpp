#include "Character.h"
#include <cmath>
#include "Log.h"


Character::Character(int lifePoints,int x,int y,int constitution,
                  int strength,int agility,int intelligence,  int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor)
                  :currPos(x,y) {
    this->raceLifeFactor = raceLifeFactor;
    this->classLifeFactor = classLifeFactor;
    this->raceManaFactor = raceManaFactor;
    this->classManaFactor = classManaFactor;
    this->recoveryFactor = recoveryFactor;
    this->meditationRecoveryFactor = meditationRecoveryFactor;
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

int Character::receiveDamage(int enemyLevel,int damage) {
    Log* log = Log::instancia();
    log->write("Danio generado por el enemigo:");
    log->writeInt(damage);

    if (dodge()) return 0;

    damage = defend(damage);
    log->write("Danio restante despues de defenderme:");
    log->writeInt(damage);
    log->write("vida character antes de recibir danio:");
    log->writeInt(this->lifePoints);

    this->lifePoints -= damage;

    log->write("vida character despues de recibir danio:");
    log->writeInt(this->lifePoints);
    return calculateAttackXp(damage,enemyLevel);
}

/*metodos protected*/


int Character::calculateAttackXp(int damage,int enemyLvl) {
    return damage * std::max(enemyLvl - level + 10, 0);
}

int Character::calculateMaxLife() {
    return constitution * level * classLifeFactor * raceLifeFactor;
}

int Character::calculateMaxMana() {
    return intelligence * classManaFactor * raceManaFactor * level;
}

int Character::calculateLvlLimit() {
    return 1000 * pow(level, 1.8);
}

int Character::calculateRecoverLifePoints(int seconds) {
    return recoveryFactor * seconds;
}

int Character::calculateRecoverMana(int seconds) {
    return recoveryFactor * seconds;
}

int Character::calculateRecoverManaMeditating(int seconds) {
    return meditationRecoveryFactor * seconds;
}

int Character::calculateSafeGoldCapacity(int lvl) {
    return 100 * pow(lvl, 1.1);
}

int Character::calculateGoldCapacity() {
    return calculateSafeGoldCapacity(level) * 1.5;
}

int Character::calculateKillXp(int enemyMaxLp, int enemyLvl) {
    double modifier = double(rand()) / (double(RAND_MAX) + 1.0);
    return modifier * enemyMaxLp * std::max(enemyLvl - level + 10, 0);
}

bool Character::dodge() {
    double modifier = double(rand()) / (double(RAND_MAX) * 1.0);
    return pow(modifier, agility) < 0.001;
}


Character::~Character() = default;

