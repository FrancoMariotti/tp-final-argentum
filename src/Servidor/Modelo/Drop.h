//
// Created by franco on 1/7/20.
//

#ifndef ARGENTUM_DROP_H
#define ARGENTUM_DROP_H

#include "Position.h"
#include "Equippable.h"

class Drop {
    //int gold;
    Position position;
    Droppable* item;
    std::string name;
public:
    Drop(Position& position, Droppable* droppable, std::string name);
    //bool collidesWith(Position pos);
    Position getPosition();
    std::string getName();
};


#endif //ARGENTUM_DROP_H
