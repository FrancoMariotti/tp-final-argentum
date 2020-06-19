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
        Map* map;
       //ESTOS 5 ATRIBUTOS DE ACA ABAJO CREO QUE SOLO DEBERIAN ESTAR EN EL PLAYABLE CHARACTER
       //CREO QUE NO SON NECESARIOS PARA EN NPC
        int constitution;
        int agility;
        int strength;
        int intelligence;
        Calculator calculator;

    public:
        Character(int lifePoints,int x,int y,Map* map,int constitution,
                  int strength,int agility,int intelligence, int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor);
        bool collideWith(Position& objPos);
        int distanceTo(Position pos);
        Offset getOffset(Position initialPos);
        virtual void attack(Character* character) = 0;
        void receiveDamage(int damage);
        //METODO PARA PROBAR
        void printPosition();
        virtual ~Character();
};

#endif //ARGENTUM_CHARACTER_H
