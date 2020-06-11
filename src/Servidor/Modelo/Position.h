//
// Created by franco on 11/6/20.
//

#ifndef ARGENTUM_POSITION_H
#define ARGENTUM_POSITION_H


#include "Offset.h"

class Position {
    int x,y;
    public:
        Position(int x,int y);
        void aplicar(Offset &offset);
        int distanceTo(Position& posicion);
        bool operator==(const Position& posicion);
        void operator=(Position& posicion);
        Offset operator-(Position& posicion);
        ~Position();
};


#endif //ARGENTUM_POSITION_H
