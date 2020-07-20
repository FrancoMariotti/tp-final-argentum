//
// Created by franco on 26/6/20.
//

#include "ManaPotion.h"

ManaPotion::ManaPotion(std::string name, int id, int value, int goldCost)
    : Potion(name, id, value, goldCost) {}

void ManaPotion::use(PlayableCharacter *character) {
    int mana = randomize();
    character->earnMana(mana);
    character->notifyStats();
}