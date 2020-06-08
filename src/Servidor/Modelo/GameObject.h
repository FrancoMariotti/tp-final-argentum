//
// Created by franco on 8/6/20.
//

#ifndef ARGENTUM_GAMEOBJECT_H
#define ARGENTUM_GAMEOBJECT_H

#include "Mapa.h"
#include "Direccion.h"

class Mapa;

class Posicion {
    int x,y;
    public:
        Posicion(int x,int y);
        void aplicar(Direccion *direccion);
        bool operator==(const Posicion& posicion);
        void operator=(Posicion& posicion);
        ~Posicion();
};

class GameObject {
    Posicion posicion;
    Mapa& mapa;
    public:
        GameObject(int x,int y,Mapa& mapa);
        void mover(Direccion *direccion);
        Posicion get_posicion();
        ~GameObject();
};


#endif //ARGENTUM_GAMEOBJECT_H
