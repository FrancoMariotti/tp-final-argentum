//
// Created by franco on 26/6/20.
//

#include "ManaPotion.h"
#include "Log.h"

ManaPotion::ManaPotion(std::string name, int value, int goldCost)
    : Potion(name, value, goldCost) {}

void ManaPotion::use(PlayableCharacter *character) {
    Log* log = Log::instancia();
    log->write("Usando pocion de mana de:");
    int mana = randomize();
    log->writeInt(mana);
    character->earnMana(mana);
}