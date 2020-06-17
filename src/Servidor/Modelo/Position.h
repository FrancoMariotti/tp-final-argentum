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
        int distanceTo(Position& position) const;
        bool operator==(const Position& position) const;
        void operator=(const Position& position);
        Offset operator-(Position& position);
        int getX() const;
        int getY() const;
        ~Position();
        //METODO PARA PROBAR
        void print() const;
};


#endif //ARGENTUM_POSITION_H
