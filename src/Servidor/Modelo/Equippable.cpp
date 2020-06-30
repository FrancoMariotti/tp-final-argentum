#include <cstdlib>
#include "Equippable.h"
#include "Servidor/Common/Utils.h"

Equippable::Equippable(std::string name, int minValue, int maxValue) : name(name), minValue(minValue),
    maxValue(maxValue), equipped(false){}

int Equippable::randomize() const {
    return Utils::random_int_number(minValue,maxValue);
}


