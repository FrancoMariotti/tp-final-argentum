#ifndef ARGENTUM_CHARACTER_H
#define ARGENTUM_CHARACTER_H

#include "Map.h"
#include "Offset.h"
#include "Position.h"
#include "Calculator.h"

class Map;

class Character {
    protected:
        int lifePoints;
        int level;
        Position currPos;
        Map& map;
        //ESTO TAMBIEN LO DEBE TENER EL NPC? o solo los personajes jugables tienen atributos?
        int constitution;
        int agility;
        int strength;
        int intelligence;
        //LA CALCULADORA NOSE SI LE CORRESPONDE TAMBIEN AL NPC,HAY QUE ANALIZARLO
        //SIN EMBARGO LA CALCULADORA USA ALGUNOS ATRIBUTOS DE LOS NPC COMO SU VIDA MAXIMA O SU NIVEL
        //ASI QUE TENEMOS QUE PENSAR DONDE NOS CONVIENE PONERLA
        Calculator calculator;

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
