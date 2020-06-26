//
// Created by franco on 25/6/20.
//

#include "Potion.h"

Potion::Potion(int value) : Equippable(value, value){}

void Potion::equipTo(PlayableCharacter *character) {
    character->equip(this);
}