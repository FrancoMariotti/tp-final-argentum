//
// Created by franco on 25/6/20.
//

#ifndef ARGENTUM_POTION_H
#define ARGENTUM_POTION_H

#include "Equippable.h"
#include "PlayableCharacter.h"

class Potion : public Equippable {
public:
    Potion(std::string name, int value);
    virtual void use(PlayableCharacter* character) = 0;
    void equipTo(PlayableCharacter *character, int i) override;
    void unequipFrom(PlayableCharacter *character) override;
};


#endif //ARGENTUM_POTION_H
