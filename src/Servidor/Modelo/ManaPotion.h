//
// Created by franco on 26/6/20.
//

#ifndef ARGENTUM_MANAPOTION_H
#define ARGENTUM_MANAPOTION_H


#include "Potion.h"

class ManaPotion : public Potion {
public:
    ManaPotion(int value);
    void use(PlayableCharacter* character);
};


#endif //ARGENTUM_MANAPOTION_H
