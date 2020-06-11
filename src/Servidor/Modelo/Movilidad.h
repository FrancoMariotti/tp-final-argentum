//
// Created by franco on 11/6/20.
//

#ifndef ARGENTUM_MOVILIDAD_H
#define ARGENTUM_MOVILIDAD_H


#include "GameObject.h"
#include "Position.h"
#include "Mapa.h"

class Mapa;

class Movilidad {
    public:
        virtual void move(Position& posicion,Mapa& mapa,Offset& offset) = 0;
};

class Movible: public Movilidad {
    public:
        void move(Position& posicion,Mapa& mapa,Offset& offset);
};

class NoMovible: public Movilidad {
    public:
        void move(Position& posicion,Mapa& mapa,Offset& offset);
};


#endif //ARGENTUM_MOVILIDAD_H
