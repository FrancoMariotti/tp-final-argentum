//
// Created by franco on 1/7/20.
//

#ifndef ARGENTUM_DROP_H
#define ARGENTUM_DROP_H

#include "Position.h"
#include "Equippable.h"

class Drop {
    Position position;
    Droppable* item;
    std::string name;
public:
    Drop();
    Drop(Position& position, Droppable* droppable, std::string name);
    Position getPosition();
    std::string getName();

    void takenBy(PlayableCharacter *player);
};


#endif //ARGENTUM_DROP_H
