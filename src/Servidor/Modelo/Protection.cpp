//
// Created by franco on 25/6/20.
//

#include "Protection.h"
#include "PlayableCharacter.h"

Protection::Protection(std::string name, int minVal, int maxVal, int id, int goldCost)
    : Equippable(name, minVal, maxVal, goldCost), id(id) {}

void Protection::equip(std::vector<Protection*> &protections) {
    protections[id] = this;
}

void Protection::unequip(std::vector<Protection*> &protections, Protection* defaultProtection) {
    protections[id] = defaultProtection;
}

void Protection::equipTo(PlayableCharacter *character, int index) {
    equipped = true;
    character->equip(this, index);
}

void Protection::unequipFrom(PlayableCharacter *character) {
    equipped = false;
    character->unequip(this);
}

std::string Equippable::getName(){
    return name;
}