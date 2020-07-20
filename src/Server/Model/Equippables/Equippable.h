//
// Created by franco on 23/6/20.
//

#ifndef ARGENTUM_EQUIPPABLE_H
#define ARGENTUM_EQUIPPABLE_H

#include <string>
#include "Server/Model/Dropppables/Droppable.h"

class Equippable : public Droppable {
    //Corresponde al identifcador de la imagen asociada al equipable
    std::string name;
    int id;
    int minValue;
    int maxValue;
    int goldCost;
public:
    Equippable(std::string name,uint32_t id, int minValue, int maxValue, int goldCost);
    int randomize() const;
    virtual void equipTo(PlayableCharacter *character, int index) = 0;
    virtual void unequipFrom(PlayableCharacter *character) = 0;
    std::string getName();
    int getId();
    void takenBy(PlayableCharacter* player) override;
    virtual ~Equippable() = default;
};


#endif //ARGENTUM_EQUIPPABLE_H
