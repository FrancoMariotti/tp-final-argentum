#include "Character.h"
#include <cmath>
#include "Log.h"


Character::Character(int lifePoints,int x,int y,int constitution,
                  int strength,int agility,int intelligence,  int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor)
                  :currPos(x,y)/*, calculator(raceLifeFactor, classLifeFactor, raceManaFactor,
                          classManaFactor,recoveryFactor,meditationRecoveryFactor)*/{
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

void Character::receiveDamage(int damage) {
    Log* log = Log::instancia();
    log->write("Danio generado por el enemigo:");
    log->writeInt(damage);
    if (!Character::dodge(agility)) {
        int result = defend(damage);
        log->write("Danio restante despues de defenderme:");
        log->writeInt(result);
        log->write("vida character antes de recibir danio:");
        log->writeInt(this->lifePoints);
        this->lifePoints -= result;
    } else {
        log->write("Ataque esquivado");
    }
    log->write("vida character despues de recibir danio:");
    log->writeInt(this->lifePoints);
}

/*metodos de clase*/

int Character::calculateDamage(int strength, int weaponMinDamage, int weaponMaxDamage) {
    int range = weaponMaxDamage - weaponMinDamage;
    return strength * (std::rand() % range + weaponMinDamage);
}

int Character::calculateMaxLife(int constitution, int lvl, int classLifeFactor,int raceLifeFactor) {
    return constitution * lvl * classLifeFactor * raceLifeFactor;
}

int Character::calculateMaxMana(int intelligence, int lvl,int classManaFactor,int raceManaFactor) {
    return intelligence * classManaFactor * raceManaFactor * lvl;
}

int Character::calculateRecoverLifePoints(int recoveryFactor,int seconds) {
    return recoveryFactor * seconds;
}

int Character::calculateRecoverMana(int recoveryFactor,int seconds) {
    return recoveryFactor * seconds;
}

int Character::calculateRecoverManaMeditating(int meditationRecoveryFactor,int seconds) {
    return meditationRecoveryFactor * seconds;
}

int Character::calculateSafeGoldCapacity(int lvl) {
    return 100 * pow(lvl, 1.1);
}

int Character::calculateGoldCapacity(int lvl) {
    return calculateSafeGoldCapacity(lvl) * 1.5;
}

int Character::calculateLvlLimit(int lvl) {
    return 1000 * pow(lvl, 1.8);
}

int Character::calculateAttackXp(int strength, int weaponMinDamage, int weaponMaxDamage, int myLvl, int enemyLvl) {
    int damage = calculateDamage(strength, weaponMinDamage, weaponMaxDamage);
    return damage * std::max(enemyLvl - myLvl + 10, 0);
}

int Character::calculateKillXp(int enemyMaxLp, int mylvl, int enemyLvl) {
    double modifier = double(rand()) / (double(RAND_MAX) + 1.0);
    return modifier * enemyMaxLp * std::max(enemyLvl - mylvl + 10, 0);
}

bool Character::dodge(int agility) {
    double modifier = double(rand()) / (double(RAND_MAX) * 1.0);
    return pow(modifier, agility) < 0.001;
}

/*int Character::calculateDefense(int minArmour, int maxArmour, int minShield, int maxShield, int minHelmet, int maxHelmet) {
    int armour = 0;
    int shield = 0;
    int helmet = 0;

    int range_armour = maxArmour - minArmour;
    int range_shield = maxShield - minShield;
    int range_helmet = maxHelmet - minHelmet;

    if(range_armour) armour = std::rand() % range_armour + minArmour;
    if(range_shield) shield = std::rand() % range_shield + minShield;
    if(range_helmet) helmet = std::rand() % range_shield + minShield;

    return armour + shield + helmet;
}
*/
int Character::calculateNpcGoldDrop(int npcMaxLp) {
    //std::default_random_engine generator;
    //std::uniform_real_distribution<float> distribution(0,0.2);
    double modifier = double(rand()) / (double(RAND_MAX) + 0.2);
    //float modifier = distribution(generator);
    return modifier * npcMaxLp;
}

bool Character::shouldDrop(int probability) {
    int n = 100;
    int result = std::rand() % (n+1);
    return result < (probability * n);
}


Character::~Character() = default;

