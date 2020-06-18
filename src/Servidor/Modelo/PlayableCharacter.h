#ifndef ARGENTUM_PLAYABLECHARACTER_H
#define ARGENTUM_PLAYABLECHARACTER_H

#include "Character.h"
#include "Mobility.h"
#include "Weapon.h"

class Mobility;
class Game;

class PlayableCharacter: public Character {
    friend class PersonajeTest;
    Weapon* activeWeapon;
    //Inventory inventory;
    //Armour
    //Helmet
    //Shield
    int mana;
    //int gold;
    //int xp;

public:
        PlayableCharacter(int lifePoints, int x, int y, Map& map,int constitution,
                          int strength,int agility,int intelligence, int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor);
        void attack(Character *character) override;
        void move(Offset& offset);
        ~PlayableCharacter() override;
};


#endif //ARGENTUM_PLAYABLECHARACTER_H
