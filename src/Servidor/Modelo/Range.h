//
// Created by franco on 18/6/20.
//

#ifndef ARGENTUM_RANGE_H
#define ARGENTUM_RANGE_H


#include "Character.h"

class Range {
public:
    virtual void attack(Character enemy, Position from) = 0;
};


#endif //ARGENTUM_RANGE_H
