//
// Created by franco on 18/6/20.
//

#include "ShortRange.h"

ShortRange::ShortRange() {}

void ShortRange::attack(Character *enemy, Position from, int damage) {
    if(enemy->distanceTo(from) == 1) {
        enemy->receiveDamage(damage);
    }
}

ShortRange::~ShortRange() {}
