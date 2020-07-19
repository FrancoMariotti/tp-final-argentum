//
// Created by franco on 25/6/20.
//

#include "Protection.h"
#include "Servidor/Modelo/Character/PlayableCharacter.h"

Protection::Protection(std::string name, int id, int minVal, int maxVal, int protectionId, int goldCost)
    : Equippable(name, id, minVal, maxVal, goldCost), protectionId(protectionId) {}

void Protection::equip(std::vector<Protection*> &protections, Protection* defaultProtection,
        PlayableCharacter* character) {
    if (protections[protectionId] != defaultProtection) protections[protectionId]->unequipFrom(character);
    protections[protectionId] = this;
}

void Protection::unequip(std::vector<Protection*> &protections, Protection* defaultProtection) const {
    protections[protectionId] = defaultProtection;
}

void Protection::equipTo(PlayableCharacter *character, int index) {
    //equipped = true;
    character->equip(this, index);
}

void Protection::unequipFrom(PlayableCharacter *character) {
    //equipped = false;
    character->unequip(this);
}

std::string Equippable::getName(){
    return name;
}