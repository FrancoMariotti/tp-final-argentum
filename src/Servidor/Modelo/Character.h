#ifndef ARGENTUM_CHARACTER_H
#define ARGENTUM_CHARACTER_H

#include "Map.h"
#include "Offset.h"
#include "Position.h"

class Map;

class Character {
    protected:
        int lifePoints;
        int level;
        int constitution;
        int agility;
        int strength;
        int intelligence;
        int raceLifeFactor;
        int classLifeFactor;
        int raceManaFactor;
        int classManaFactor;
        int recoveryFactor;
        int meditationRecoveryFactor;
        Map* map;
        Position currPos;

        virtual int defend(int damage) = 0;
        int calculateMaxLife();
        int calculateMaxMana();
        //Devuelve la cantidad de vida recuperada en x segundos
        int calculateRecoverLifePoints(int seconds);
        //Devuelve la cantidad de mana recuperado en x segundos
        int calculateRecoverMana(int seconds);
        //Devuelve la cantidad de mana recuperado meditando en x segundos
        int calculateRecoverManaMeditating(int seconds);
        int calculateAttackXp(int damage,int enemyLvl);
        //Devuelve la cantidad de oro maxima que puede tener el jugador
        int calculateGoldCapacity();
        int calculateLvlLimit();
        int calculateKillXp (int enemyMaxLp, int enemyLvl);
        bool dodge();
    public:
        Character(Map* map,int lifePoints,int x,int y,int constitution,
                  int strength,int agility,int intelligence, int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor);
        bool collideWith(Position& objPos);
        int distanceTo(Position pos);
        Offset getOffset(Position initialPos);
        virtual void attack(Character* character) = 0;
        int receiveDamage(int enemyLevel,int damage);
        int calculateSafeGoldCapacity(int lvl);
        bool shouldDrop(int probability);
        virtual ~Character();
};

#endif //ARGENTUM_CHARACTER_H
