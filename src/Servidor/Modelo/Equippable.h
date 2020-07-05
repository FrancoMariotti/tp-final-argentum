//
// Created by franco on 23/6/20.
//

#ifndef ARGENTUM_EQUIPPABLE_H
#define ARGENTUM_EQUIPPABLE_H

#include <string>
#include "Droppable.h"

//class PlayableCharacter;

class Equippable : public Droppable {
    //Corresponde al identifcador de la imagen asociada al equipable
    std::string name;
    int minValue;
    int maxValue;
    int goldCost;
protected:
    bool equipped;
public:
    Equippable(std::string name, int minValue, int maxValue, int goldCost);
    int randomize() const;
    virtual void equipTo(PlayableCharacter *character, int index) = 0;
    virtual void unequipFrom(PlayableCharacter *character) = 0;
    std::string getName();
    void takenBy(PlayableCharacter* player) override;
    virtual ~Equippable() = default;

    bool isEquipped();
};


#endif //ARGENTUM_EQUIPPABLE_H
