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
        virtual ~Mobility();
};

class Movable: public Mobility {
    public:
        void move(Position& position, Map& map, Offset& offset);
        ~Movable();
};

class NonMovable: public Mobility {
    public:
        void move(Position& position, Map& map, Offset& offset);
        ~NonMovable();
};


#endif //ARGENTUM_MOBILITY_H
