#ifndef ARGENTUM_PLAYABLECHARACTER_H
#define ARGENTUM_PLAYABLECHARACTER_H

#include "Character.h"
#include "Mobility.h"
#include "Weapon.h"
#include "Armour.h"

class Mobility;
class Game;

class PlayableCharacter: public Character {
    friend class PersonajeTest;
    Weapon* activeWeapon;
    //Inventory inventory;
    Armour armour;
    int mana;
    int gold;
    int xp;
    virtual int defend(int damage) override;
public:
        PlayableCharacter(int lifePoints, int x, int y, int constitution,
                          int strength,int agility,int intelligence, int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor);
        void attack(Character *character) override;
        void move(Map* map,Offset& offset);
        void equipWeapon(Weapon* weapon);
        void equipShield(int minDef, int maxDef);
        ~PlayableCharacter() override;
};


#endif //ARGENTUM_PLAYABLECHARACTER_H
