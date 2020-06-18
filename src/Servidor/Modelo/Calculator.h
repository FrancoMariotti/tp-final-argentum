//
// Created by franco on 14/6/20.
//

#ifndef ARGENTUM_CALCULATOR_H
#define ARGENTUM_CALCULATOR_H

//En esta clase se encuentran las ecuaciones utilizadas para los calculos referidos
//al personaje jugable


//TODAVIA FALTAN AGREGAR ECUACIONES
class Calculator {
    private:
        int raceLifeFactor;
        int classLifeFactor;
        int raceManaFactor;
        int classManaFactor;
        int recoveryFactor;
        int meditationRecoveryFactor;
    public:
        Calculator(int raceLifeFactor, int classLifeFactor, int raceManaFactor,
                int classManaFactor, int recoveryFactor, int meditationRecoveryFactor);
        int calculateMaxLife(int constitution, int lvl);
        int calculateMaxMana(int intelligence, int lvl);
        //Devuelve la cantidad de vida recuperada en x segundos
        int calculateRecoverLifePoints(int seconds);
        //Devuelve la cantidad de mana recuperado en x segundos
        int calculateRecoverMana(int seconds);
        //Devuelve la cantidad de mana recuperado meditando en x segundos
        int calculateRecoverManaMeditating(int seconds);
        int calculateSafeGoldCapacity(int lvl);
        //Devuelve la cantidad de oro maxima que puede tener el jugador
        int calculateGoldCapacity(int lvl);
        int calculateLvlLimit(int lvl);
        int calculateDamage(int strength, int weaponMinDamage, int weaponMaxDamage);
        int calculateAttackXp(int strength, int weaponMinDamage, int weaponMaxDamage, int myLvl, int enemyLvl);
        int calculateKillXp (int enemyMaxLp, int mylvl, int enemyLvl);
        bool caculateDodge(int agility);
        int calculateDefense(int minArmour, int maxArmour, int minShield, int maxShield, int minHelmet, int maxHelmet);
        int calculateNpcGoldDrop(int npcMaxLp);
        ~Calculator();
};


#endif //ARGENTUM_CALCULATOR_H
