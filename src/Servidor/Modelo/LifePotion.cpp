//
// Created by franco on 26/6/20.
//

#include "LifePotion.h"
#include "Log.h"

LifePotion::LifePotion(std::string name, int id, int value, int goldCost)
    : Potion(name, id, value, goldCost) {}

void LifePotion::use(PlayableCharacter *character) {
    Log* log = Log::instancia();
    log->write("Usando pocion de curacion de:");
    int heal = randomize();
    log->writeInt(heal);
    character->heal(heal);
    character->notifyStats();
}