#ifndef ARGENTUM_GAMEOBJECT_H
#define ARGENTUM_GAMEOBJECT_H

#include "Map.h"
#include "Offset.h"
#include "Position.h"

class Map;

class GameObject {
    protected:
        Position currPos;
        Map& map;
    public:
        GameObject(int x,int y,Map& map);
        bool collideWith(Position& objPos);
        virtual int distanceTo(Position pos);
        Offset getOffset(Position initialPos);
        virtual ~GameObject();
        //METODO PARA PROBAR
        void printPosition();
};

#endif //ARGENTUM_GAMEOBJECT_H
