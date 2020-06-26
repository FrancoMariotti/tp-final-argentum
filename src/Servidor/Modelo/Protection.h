//
// Created by franco on 25/6/20.
//

#ifndef ARGENTUM_PROTECTION_H
#define ARGENTUM_PROTECTION_H

#include "Equippable.h"
#include "Armour.h"

enum Equipment {
    ARMOUR,
    SHIELD,
    HELMET,
    NONE
};

class Protection : public Equippable {
    int id;
public:
    Protection(int minVal, int maxVal, Equipment id);
    void equip(std::vector<Protection> &protections);
    void equipTo(PlayableCharacter *character) override;
};


#endif //ARGENTUM_PROTECTION_H
