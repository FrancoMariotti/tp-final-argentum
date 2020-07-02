#include "Equippable.h"
#include "Servidor/Common/Utils.h"

Equippable::Equippable(std::string name, int minValue, int maxValue, int goldCost)
    : name(name), minValue(minValue), maxValue(maxValue), goldCost(goldCost)
    ,equipped(false){}

int Equippable::randomize() const {
    return Utils::random_int_number(minValue,maxValue);
}

bool Equippable::isEquipped() {
    return equipped;
}


