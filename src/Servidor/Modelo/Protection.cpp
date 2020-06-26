//
// Created by franco on 25/6/20.
//

#include "Protection.h"
#include "PlayableCharacter.h"

Protection::Protection(int minVal, int maxVal, Equipment id) : Equippable(minVal, maxVal), id(id) {}

void Protection::equip(std::vector<Protection> &protections) {
    protections[id] = (*this);
}

void Protection::equipTo(PlayableCharacter *character) {
    character->equip(this);
}
