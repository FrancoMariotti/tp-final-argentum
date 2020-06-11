#ifndef ARGENTUM_GAMEOBJECT_H
#define ARGENTUM_GAMEOBJECT_H

#include "Mapa.h"
#include "Offset.h"
#include "Position.h"

class Mapa;

class GameObject {
    protected:
        Position actual;
        Mapa& mapa;
    public:
        GameObject(int x,int y,Mapa& mapa);
        bool colisiono(Position& posicionObj);
        virtual int distanceTo(Position pos);
        Offset getOffset(Position pos);
        virtual ~GameObject();
};

#endif //ARGENTUM_GAMEOBJECT_H
