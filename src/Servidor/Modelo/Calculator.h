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
    int maxLife(int constitution, int lvl);
    int maxMana(int intelligence, int lvl);
    //Devuelve la cantidad de vida recuperada en x segundos
    int recoverLifePoints(int seconds);
    //Devuelve la cantidad de mana recuperado en x segundos
    int recoverMana(int seconds);
    //Devuelve la cantidad de mana recuperado meditando en x segundos
    int recoverManaMeditating(int seconds);
    int safeGoldCapacity(int lvl);
    //Devuelve la cantidad de oro maxima que puede tener el jugador
    int goldCapacity(int lvl);
    int lvlLimit(int lvl);
    int damage(int strength, int weaponMinDamage, int weaponMaxDamage);
    int attackXp(int strength, int weaponMinDamage, int weaponMaxDamage, int myLvl, int enemyLvl);
    int killXp (int enemyMaxLp, int mylvl, int enemyLvl);
    bool dodge(int agility);
    int defense(int minArmour, int maxArmour, int minShield, int maxShield, int minHelmet, int maxHelmet);
    int npcGoldDrop(int npcMaxLp);
    ~Calculator();
};


#endif //ARGENTUM_CALCULATOR_H
