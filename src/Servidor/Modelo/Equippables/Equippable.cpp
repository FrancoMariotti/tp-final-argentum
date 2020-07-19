#include "Equippable.h"
#include "Common/Utils.h"
#include "Servidor/Modelo/Character/PlayableCharacter.h"


Equippable::Equippable(std::string name, uint32_t id, int minValue, int maxValue, int goldCost)
    : name(name), id(id), minValue(minValue), maxValue(maxValue), goldCost(goldCost)
    /*,equipped(false)*/{}

int Equippable::randomize() const {
    return Utils::random_int_number(minValue,maxValue);
}
/*
bool Equippable::isEquipped() {
    return equipped;
}
*/
void Equippable::takenBy(PlayableCharacter *player) {
    player->takeDroppable(this);
}

int Equippable::getId() {
    return id;
}