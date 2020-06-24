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
        Position currPos;
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
        //Calculator calculator;
        virtual int defend(int damage) = 0;
    public:
        Character(int lifePoints,int x,int y,int constitution,
                  int strength,int agility,int intelligence, int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor);
        bool collideWith(Position& objPos);
        int distanceTo(Position pos);
        Offset getOffset(Position initialPos);
        virtual void attack(Character* character) = 0;
        void receiveDamage(int damage);
        static int calculateMaxLife(int constitution, int lvl, int classLifeFactor,int raceLifeFactor);
        static int calculateMaxMana(int intelligence, int lvl,int classManaFactor,int raceManaFactor);
        //Devuelve la cantidad de vida recuperada en x segundos
        static int calculateRecoverLifePoints(int recoveryFactor,int seconds);
        //Devuelve la cantidad de mana recuperado en x segundos
        static int calculateRecoverMana(int recoveryFactor,int seconds);
        //Devuelve la cantidad de mana recuperado meditando en x segundos
        static int calculateRecoverManaMeditating(int meditationRecoveryFactor, int seconds);
        static int calculateSafeGoldCapacity(int lvl);
        //Devuelve la cantidad de oro maxima que puede tener el jugador
        static int calculateGoldCapacity(int lvl);
        static int calculateDamage(int strength, int weaponMinDamage, int weaponMaxDamage);
        static int calculateLvlLimit(int lvl);
        static int calculateAttackXp(int strength, int weaponMinDamage, int weaponMaxDamage, int myLvl, int enemyLvl);
        static int calculateKillXp (int enemyMaxLp, int mylvl, int enemyLvl);
        static bool dodge(int agility);
        //static int calculateDefense(int minArmour, int maxArmour, int minShield, int maxShield, int minHelmet, int maxHelmet);
        static int calculateNpcGoldDrop(int npcMaxLp);
        static bool shouldDrop(int probability);
        virtual ~Character();
};

#endif //ARGENTUM_CHARACTER_H
