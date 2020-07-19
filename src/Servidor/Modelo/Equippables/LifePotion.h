//
// Created by franco on 26/6/20.
//

#ifndef ARGENTUM_LIFEPOTION_H
#define ARGENTUM_LIFEPOTION_H

#include "Potion.h"
#include "Servidor/Modelo/Character/PlayableCharacter.h"

class LifePotion : public Potion {
public:
    LifePotion(std::string name, int id, int value, int goldCost);
    void use(PlayableCharacter* character);
};


#endif //ARGENTUM_LIFEPOTION_H
