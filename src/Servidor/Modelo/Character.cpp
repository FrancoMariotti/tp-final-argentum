#include "Character.h"
#include <cmath>
#include <utility>
#include "Log.h"
#include "PlayableCharacter.h"
#include "Common/Utils.h"

Character::Character(std::string id,Map* map,Position &initialPosition,int constitution,
                  int strength,int agility,int intelligence,int level,  int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor,Observer* observer)
                  : map(map),currPos(initialPosition) {
    this->id = std::move(id);
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

int Character::calculateAttackXp(int damage,int enemyLvl) const {
    return damage * std::max(enemyLvl - level + 10, 0);
}

float Character::calculateMaxLife() const {
    return (float)(constitution * level * classLifeFactor * raceLifeFactor);
}

float Character::calculateMaxMana() const {
    return (float)(intelligence * classManaFactor * raceManaFactor * level);
}

int Character::calculateLvlLimit() const {
    return (int)(1000 * pow(level, 1.8));
}

float Character::calculateRecoverLifePoints(float seconds) const {
    return (float)recoveryFactor * seconds;
}

float Character::calculateRecoverMana(float seconds) const {
    return (float)recoveryFactor * seconds;
}

int Character::calculateRecoverManaMeditating(int seconds) const {
    return meditationRecoveryFactor * seconds;
}

int Character::calculateSafeGoldCapacity(int lvl) const {
    return (int)(100 * pow(lvl, 1.1));
}

int Character::calculateGoldCapacity() const {
    return (int)(calculateSafeGoldCapacity(level) * 1.5);
}

int Character::calculateKillXp(int enemyMaxLp, int enemyLvl) const {
    float modifier = Utils::random_real_number(0,0.1);
    return (int)(modifier * enemyMaxLp * std::max(enemyLvl - level + 10, 0));
}

bool Character::dodge() const {
    float modifier = Utils::random_real_number(0,1);
    return pow(modifier, agility) < 0.001;
}

void Character::restoreLife() {
    lifePoints = calculateMaxLife();
}

Position Character::getClosestPositionToDrop() {
    for (int distance = 1; distance <= 3 ; ++distance) {
        for (int i = -distance; i <= distance ; i+= distance) {
            for (int j = -distance; j <= distance ; j+= distance) {
                Offset offset(i, j);
                Position pos = currPos;
                pos.apply(offset);
                if (!map->isOccupied(pos) && !map->hasDropInPos(pos) && !map->outOfBounds(pos)) return pos;
            }
        }
    }
    return Position(0, 0);
}



Character::~Character() = default;

