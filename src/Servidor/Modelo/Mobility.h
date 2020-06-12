//
// Created by franco on 11/6/20.
//

#ifndef ARGENTUM_MOBILITY_H
#define ARGENTUM_MOBILITY_H


#include "GameObject.h"
#include "Position.h"
#include "Map.h"

class Map;

class Mobility {
    public:
        virtual void move(Position& position, Map& map, Offset& offset) = 0;
};

class Movable: public Mobility {
    public:
        void move(Position& position, Map& map, Offset& offset);
};

class NonMovable: public Mobility {
    public:
        void move(Position& position, Map& map, Offset& offset);
};


#endif //ARGENTUM_MOBILITY_H
