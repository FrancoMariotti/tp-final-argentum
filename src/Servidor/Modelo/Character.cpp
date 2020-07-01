#include "Character.h"
#include <cmath>
#include <utility>
#include "Log.h"
#include "PlayableCharacter.h"

Character::Character(std::string id,Map* map,Position &initialPosition,int constitution,
                  int strength,int agility,int intelligence,int level,  int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor,Observer* observer)
                  : map(map),currPos(initialPosition) {
    this->id = id;
    this->observer = observer;
    this->level = level;
    this->raceLifeFactor = raceLifeFactor;
    this->classLifeFactor = classLifeFactor;
    this->raceManaFactor = raceManaFactor;
    this->classManaFactor = classManaFactor;
    this->recoveryFactor = recoveryFactor;
    this->meditationRecoveryFactor = meditationRecoveryFactor;
    this->constitution = constitution;
    this->strength = strength;
    this->agility = agility;
    this->intelligence = intelligence;
    this->lifePoints = calculateMaxLife();
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

/*metodos protected*/


int Character::calculateAttackXp(int damage,int enemyLvl) const {
    return damage * std::max(enemyLvl - level + 10, 0);
}

float Character::calculateMaxLife() const {
    return constitution * level * classLifeFactor * raceLifeFactor;
}

int Character::calculateMaxMana() const {
    return intelligence * classManaFactor * raceManaFactor * level;
}

int Character::calculateLvlLimit() const {
    return 1000 * pow(level, 1.8);
}

int Character::calculateRecoverLifePoints(int seconds) const {
    return recoveryFactor * seconds;
}

int Character::calculateRecoverMana(int seconds) const {
    return recoveryFactor * seconds;
}

int Character::calculateRecoverManaMeditating(int seconds) const {
    return meditationRecoveryFactor * seconds;
}

int Character::calculateSafeGoldCapacity(int lvl) const {
    return 100 * pow(lvl, 1.1);
}

int Character::calculateGoldCapacity() const {
    return calculateSafeGoldCapacity(level) * 1.5;
}

int Character::calculateKillXp(int enemyMaxLp, int enemyLvl) const {
    double modifier = double(std::rand()) / (double(RAND_MAX) + 1.0);
    return modifier * enemyMaxLp * std::max(enemyLvl - level + 10, 0);
}

bool Character::dodge() const {
    double modifier = double(std::rand()) / (double(RAND_MAX) * 1.0);
    return pow(modifier, agility) < 0.001;
}

void Character::restoreLife() {
    this->lifePoints = calculateMaxLife();
}


Character::~Character() = default;

