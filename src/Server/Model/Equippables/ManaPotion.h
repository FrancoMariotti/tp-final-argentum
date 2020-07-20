//
// Created by franco on 26/6/20.
//

#ifndef ARGENTUM_MANAPOTION_H
#define ARGENTUM_MANAPOTION_H


#include "Potion.h"

class ManaPotion : public Potion {
public:
    ManaPotion(std::string name, int id, int value, int goldCost);
    void use(PlayableCharacter* character);
};


#endif //ARGENTUM_MANAPOTION_H
