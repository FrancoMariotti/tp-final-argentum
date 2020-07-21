#include "Equippable.h"
#include "Common/Utils.h"
#include "Server/Model/Character/PlayableCharacter.h"


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
void Equippable::takenBy(PlayableCharacter *player, Position& position) {
    player->takeDroppable(this, position);
}

int Equippable::getId() {
    return id;
}