#include <cstdlib>
#include "Equippable.h"

Equippable::Equippable(std::string name, int minValue, int maxValue) : name(name), minValue(minValue),
    maxValue(maxValue), equipped(false){}

int Equippable::randomize() const {
    int range = maxValue - minValue;
    if (range == 0) return minValue;
    return std::rand() % range + minValue;
}


