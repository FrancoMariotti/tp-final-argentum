//
// Created by franco on 14/6/20.
//

#include <cmath>
#include <algorithm>
#include "Calculator.h"

Calculator::Calculator(int raceLifeFactor, int classLifeFactor, int raceManaFactor,
            int classManaFactor, int recoveryFactor, int meditationRecoveryFactor) :
            raceLifeFactor(raceLifeFactor), classLifeFactor(classLifeFactor),
            raceManaFactor(raceManaFactor), classManaFactor(classManaFactor),
            recoveryFactor(recoveryFactor),
            meditationRecoveryFactor(meditationRecoveryFactor) {

}

int Calculator::maxLife(int constitution, int lvl) {
    return constitution * lvl * classLifeFactor * raceLifeFactor;
}

int Calculator::maxMana(int intelligence, int lvl) {
    return intelligence * classManaFactor * raceManaFactor * lvl;
}

int Calculator::recoverLifePoints(int seconds) {
    return recoveryFactor * seconds;
}

int Calculator::recoverMana(int seconds) {
    return recoveryFactor * seconds;
}

int Calculator::recoverManaMeditating(int seconds) {
    return meditationRecoveryFactor * seconds;
}

int Calculator::goldCapacity(int lvl) {
    return 100 * pow(lvl, 1.1);
}

int Calculator::lvlLimit(int lvl) {
    return 1000 * pow(lvl, 1.8);
}

int attackXp(int damage, int myLvl, int enemyLvl) {
    return damage * std::max(enemyLvl - myLvl + 10, 0);
}


Calculator::~Calculator() = default;
