//
// Created by franco on 25/6/20.
//

#ifndef ARGENTUM_PROTECTION_H
#define ARGENTUM_PROTECTION_H

#include <vector>
#include "Equippable.h"

enum Equipment {
    ARMOUR,
    SHIELD,
    HELMET,
    NONE
};

class Protection : public Equippable {
    int id;
public:
    Protection(std::string name, int minVal, int maxVal,
            int id, int goldCost);
    void equip(std::vector<Protection*> &protections, Protection* defaultProtection,
            PlayableCharacter* character);
    void equipTo(PlayableCharacter *character, int i) override;
    void unequip(std::vector<Protection*> &protections, Protection* defaultProtection) const;
    void unequipFrom(PlayableCharacter *character) override;
};


#endif //ARGENTUM_PROTECTION_H
