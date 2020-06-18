//
// Created by franco on 18/6/20.
//

#include "LongRange.h"


void LongRange::attack(Character *enemy, Position from ,int damage) {
    enemy->receiveDamage(damage);
}
