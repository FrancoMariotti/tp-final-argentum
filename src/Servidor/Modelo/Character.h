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
        int constitution;
        int agility;
        int strength;
        int intelligence;
    public:
        Character(int x,int y,Map& map,int constitution,
                  int strength,int agility,int intelligence);
        bool collideWith(Position& objPos);
        virtual int distanceTo(Position pos);
        Offset getOffset(Position initialPos);
        //METODO PARA PROBAR
        void printPosition();
        virtual ~Character();
};

#endif //ARGENTUM_CHARACTER_H
