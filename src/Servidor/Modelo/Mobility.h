#ifndef ARGENTUM_MOBILITY_H
#define ARGENTUM_MOBILITY_H


#include "Character.h"
#include "Position.h"
#include "Map.h"

class Map;

class Mobility {
    public:
        virtual void move(Position& position, Map& map) = 0;
        virtual ~Mobility();
};

class Movable: public Mobility {
    public:
        void move(Position& position, Map& map) override;
        ~Movable() override;
};

class NonMovable: public Mobility {
    public:
        void move(Position& position, Map& map) override;
        ~NonMovable() override;
};


#endif //ARGENTUM_MOBILITY_H
