#ifndef ARGENTUM_PLAYABLECHARACTER_H
#define ARGENTUM_PLAYABLECHARACTER_H

#include "Character.h"
#include "Weapon.h"
#include "Armour.h"
#include "Inventory.h"

class Game;

class PlayableCharacter: public Character {
    friend class PersonajeTest;
    Weapon* activeWeapon;
    Inventory inventory;
    Armour armour;
    int mana;
    int gold;
    int xp;
    int defend(int damage) override;
    public:
        PlayableCharacter(Map* map,int lifePoints, Position &initialPosition, int constitution,
                          int strength,int agility,int intelligence,int level, int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor,
                  int invMaxElements);

        void attack(Character *character) override;
        void move(Offset& offset);
        void equipWeapon(Weapon* weapon);
        void equipProtection(Equippable element, Equipment equipment);
        void recoverLifePoints(int seconds);
        void recoverMana(int seconds);
        ~PlayableCharacter() override;
};


#endif //ARGENTUM_PLAYABLECHARACTER_H
