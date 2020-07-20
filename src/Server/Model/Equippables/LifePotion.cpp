//
// Created by franco on 26/6/20.
//

#include "LifePotion.h"

LifePotion::LifePotion(std::string name, int id, int value, int goldCost)
    : Potion(name, id, value, goldCost) {}

void LifePotion::use(PlayableCharacter *character) {
    int heal = randomize();
    character->heal(heal);
    character->notifyStats();
}