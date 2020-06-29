//
// Created by franco on 26/6/20.
//

#ifndef ARGENTUM_LIFEPOTION_H
#define ARGENTUM_LIFEPOTION_H

#include "Potion.h"
#include "PlayableCharacter.h"

class LifePotion : public Potion {
public:
    LifePotion(std::string name, int value);
    void use(PlayableCharacter* character);
};


#endif //ARGENTUM_LIFEPOTION_H
