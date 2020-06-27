//
// Created by franco on 23/6/20.
//

#include <cstdlib>
#include "Equippable.h"

Equippable::Equippable(int minValue, int maxValue) : minValue(minValue),
    maxValue(maxValue), equipped(false){}

int Equippable::randomize() const {
    int range = maxValue - minValue;
    if (range == 0) return minValue;
    return std::rand() % range + minValue;
}


