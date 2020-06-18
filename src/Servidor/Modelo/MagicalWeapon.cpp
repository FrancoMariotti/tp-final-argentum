//
// Created by franco on 18/6/20.
//

#include "MagicalWeapon.h"

MagicalWeapon::MagicalWeapon(int minDamage, int maxDamage, int cost) {
    this->minDamage = minDamage;
    this->maxDamage = maxDamage;
    this->cost = cost;
}

void MagicalWeapon::attack(Character *enemy,int strength,int &mana,Position &holderPos,Calculator calc) {
    if(mana >= cost){
        int damage = calc.damage(strength,minDamage,maxDamage);
        enemy->receiveDamage(damage);
        mana -= cost;
    }
}

MagicalWeapon::~MagicalWeapon() {}
