//
// Created by franco on 14/6/20.
//

#include <cmath>
#include <algorithm>
#include <vector>
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

int Calculator::safeGoldCapacity(int lvl) {
    return 100 * pow(lvl, 1.1);
}

int Calculator::goldCapacity(int lvl) {
    return safeGoldCapacity(lvl) * 1.5;
}

int Calculator::lvlLimit(int lvl) {
    return 1000 * pow(lvl, 1.8);
}

int Calculator::damage(int strengh, int weaponMinDamage, int weaponMaxDamage) {
    std::vector<int> possibleResults;
    for (int i = weaponMinDamage; i <= weaponMaxDamage; i++) {
        possibleResults.push_back(i);
    }
    return strengh * possibleResults[rand()%(possibleResults.size())];
}

int Calculator::attackXp(int strengh, int weaponMinDamage, int weaponMaxDamage, int myLvl, int enemyLvl) {
    int damage = this->damage(strengh, weaponMinDamage, weaponMaxDamage);
    return damage * std::max(enemyLvl - myLvl + 10, 0);
}

int Calculator::killXp (int enemyMaxLp, int mylvl, int enemyLvl) {
    std::vector<float> possibleResults = {0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1};
    float modifier = possibleResults[rand()%(possibleResults.size())];
    return modifier * enemyMaxLp * std::max(enemyLvl - mylvl + 10, 0);
}

bool Calculator::dodge(int agility) {
    std::vector<float> possibleResults = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};
    float modifier = possibleResults[rand()%(possibleResults.size())];
    return pow(modifier, agility) < 0.001;
}

int Calculator::defense(int minArmour, int maxArmour, int minShield, int maxShield, int minHelmet, int maxHelmet) {
    std::vector<int> possibleArmour;
    std::vector<int> possibleShield;
    std::vector<int> possibleHelmet;
    for (int i = minArmour; i <= maxArmour; i++) {
        possibleArmour.push_back(i);
    }
    for (int i = minShield; i <= maxShield; i++) {
        possibleShield.push_back(i);
    }
    for (int i = minHelmet; i <= maxHelmet; i++) {
        possibleHelmet.push_back(i);
    }
    int armour = possibleArmour[rand()%(possibleArmour.size())];;
    int shield =possibleShield[rand()%(possibleShield.size())];;
    int helmet = possibleHelmet[rand()%(possibleHelmet.size())];;
    return armour + shield + helmet;
}

int Calculator::npcGoldDrop(int npcMaxLp) {
    std::vector<float> possibleResults = {0, 0.1, 0.2};
    float modifier = possibleResults[rand()%(possibleResults.size())];
    return modifier * npcMaxLp;
}


Calculator::~Calculator() = default;
