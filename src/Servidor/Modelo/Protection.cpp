//
// Created by franco on 25/6/20.
//

#include "Protection.h"
#include "PlayableCharacter.h"

Protection::Protection(int minVal, int maxVal, Equipment id) : Equippable(minVal, maxVal), id(id) {}

void Protection::equip(std::vector<Protection> &protections) {
    protections[id] = (*this);
}

void Protection::unequip(std::vector<Protection> &protections) {
    protections[id] = Protection(0, 0, NONE);
}

void Protection::equipTo(PlayableCharacter *character, int index) {
    equipped = true;
    character->equip(this, index);
}

void Protection::unequipFrom(PlayableCharacter *character) {
    equipped = false;
    character->unequip(this);
}
