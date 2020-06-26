#ifndef ARGENTUM_PLAYABLECHARACTER_H
#define ARGENTUM_PLAYABLECHARACTER_H

#include "Character.h"
#include "Weapon.h"
#include "Armour.h"
#include "Inventory.h"
#include "Protection.h"
#include "Equippable.h"
#include "Potion.h"

class Game;
class Potion;

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
        PlayableCharacter(Map* map, Position &initialPosition, int constitution,
                          int strength,int agility,int intelligence,int level, int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor,
                  int invMaxElements);

        void attack(Character *character) override;
        void move(Offset& offset);
        void equip(int elementIndex);
        void equip(Equippable* element);
        void equip(Weapon* weapon);
        void equip(Protection* protection);
        void equip(Potion* potion);
        void store(Equippable* element);
        void recoverLifePoints(int seconds);
        void recoverMana(int seconds);
        void heal(int value);
        ~PlayableCharacter() override;

    void earnMana(int value);
};


#endif //ARGENTUM_PLAYABLECHARACTER_H
