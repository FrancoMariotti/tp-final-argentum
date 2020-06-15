#ifndef ARGENTUM_CHARACTER_H
#define ARGENTUM_CHARACTER_H

#include "Map.h"
#include "Offset.h"
#include "Position.h"

class Map;

class Character {
    protected:
        Position currPos;
        Map& map;
    public:
        Character(int x,int y,Map& map);
        bool collideWith(Position& objPos);
        virtual int distanceTo(Position pos);
        Offset getOffset(Position initialPos);
        //METODO PARA PROBAR
        void printPosition();
        virtual ~Character();
};

#endif //ARGENTUM_CHARACTER_H
