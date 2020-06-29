#ifndef ARGENTUM_CHARACTER_H
#define ARGENTUM_CHARACTER_H

#include "Map.h"
#include "Offset.h"
#include "Position.h"
#include "Observer.h"

class Map;

class Character {
    protected:
        std::string id;
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
        Observer* observer;

        int calculateMaxLife() const;
        int calculateMaxMana() const;
        int calculateRecoverLifePoints(int seconds) const;
        int calculateRecoverMana(int seconds) const;
        int calculateRecoverManaMeditating(int seconds) const;
        int calculateAttackXp(int damage,int enemyLvl) const;
        int calculateGoldCapacity() const;
        int calculateLvlLimit() const;
        int calculateKillXp (int enemyMaxLp, int enemyLvl) const;
        bool dodge() const;

        virtual int defend(int damage) = 0;
    public:
        Character(std::string id,Map* map,Position &initialPosition,int constitution,
                  int strength,int agility,int intelligence,int level, int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor,Observer* observer);
        bool collideWith(Position& objPos);
        int distanceTo(Position pos);
        Offset getOffset(Position initialPos);
        virtual void attack(Character* character) = 0;
        int receiveDamage(int enemyLevel,int damage);
        static int calculateSafeGoldCapacity(int lvl);
        virtual ~Character();
};

#endif //ARGENTUM_CHARACTER_H
