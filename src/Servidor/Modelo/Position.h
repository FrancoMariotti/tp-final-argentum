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
        void apply(Offset &offset);
        int distanceTo(Position& position);
        bool operator==(const Position& position);
        void operator=(const Position& position);
        Offset operator-(Position& position);
        ~Position();
        //METODO PARA PROBAR
        void print();
};


#endif //ARGENTUM_POSITION_H
