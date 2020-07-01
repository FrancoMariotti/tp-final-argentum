//
// Created by franco on 1/7/20.
//

#ifndef ARGENTUM_DROP_H
#define ARGENTUM_DROP_H

#include "Position.h"

class Drop {
    int gold;
    Position position;
public:
    explicit Drop(Position& position);
    void addGold(int dropGold);
};


#endif //ARGENTUM_DROP_H
