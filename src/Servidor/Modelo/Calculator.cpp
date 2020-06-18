//
// Created by franco on 14/6/20.
//

#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
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

int Calculator::damage(int strength, int weaponMinDamage, int weaponMaxDamage) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(weaponMinDamage,weaponMaxDamage);
    return strength * distribution(generator);
}

int Calculator::attackXp(int strength, int weaponMinDamage, int weaponMaxDamage, int myLvl, int enemyLvl) {
    int damage = this->damage(strength, weaponMinDamage, weaponMaxDamage);
    return damage * std::max(enemyLvl - myLvl + 10, 0);
}

int Calculator::killXp (int enemyMaxLp, int mylvl, int enemyLvl) {
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0,0.1);
    float modifier = distribution(generator);
    return modifier * enemyMaxLp * std::max(enemyLvl - mylvl + 10, 0);
}

bool Calculator::dodge(int agility) {
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0,1);
    //std::vector<float> possibleResults = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};
    //float modifier = possibleResults[rand()%(possibleResults.size())];
    float modifier = distribution(generator);
    return pow(modifier, agility) < 0.001;
}

int Calculator::defense(int minArmour, int maxArmour, int minShield, int maxShield, int minHelmet, int maxHelmet) {

    std::default_random_engine generator;
    std::uniform_int_distribution<int> armour_distribution(minArmour,maxArmour);
    std::uniform_int_distribution<int> shield_distribution(minShield,maxShield);
    std::uniform_int_distribution<int> helmet_distribution(minHelmet,maxHelmet);

    /*std::vector<int> possibleArmour;
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
    int helmet = possibleHelmet[rand()%(possibleHelmet.size())];;*/
    int armour = armour_distribution(generator);
    int shield = shield_distribution(generator);
    int helmet = helmet_distribution(generator);

    return armour + shield + helmet;
}

int Calculator::npcGoldDrop(int npcMaxLp) {
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0,0.2);
    //std::vector<float> possibleResults = {0, 0.1, 0.2};
    //float modifier = possibleResults[rand()%(possibleResults.size())];
    float modifier = distribution(generator);
    return modifier * npcMaxLp;
}


Calculator::~Calculator() = default;
