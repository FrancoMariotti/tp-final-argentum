#ifndef ARGENTUM_PLAYABLECHARACTER_H
#define ARGENTUM_PLAYABLECHARACTER_H

#include "Character.h"
#include "Weapon.h"
#include "NormalWeapon.h"
#include "Inventory.h"
#include "Armour.h"
#include "Position.h"

class Game;
class Potion;

class PlayableCharacter: public Character {
    friend class PersonajeTest;
    Weapon* activeWeapon;
    NormalWeapon defaultWeapon;
    Inventory inventory;
    Armour armour;
    int mana;
    int gold;
    int xp;
    int defend(int damage) override;
public:
        PlayableCharacter(std::string id,Map* map, Position &initialPosition, int constitution,
                          int strength,int agility,int intelligence,int level, int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor,
                  int invMaxElements,Observer* observer);
        int receiveDamage(int enemyLevel, int damage) override;
        void attack(Character *character) override;
        void move(Offset& offset);
        void equip(int elementIndex);
        void equip(Equippable* element, int index);
        void equip(Weapon* weapon, int index);
        void equip(Protection* protection, int index);
        void equip(Potion* potion, int index);
        void unequip(int elementIndex);
        void unequip(Equippable* element);
        void store(Equippable* element);
        void recoverLifePoints(int seconds);
        void recoverMana(int seconds);
        void heal(int value);
        void earnMana(int value);
        void unequip(Protection *protection);
        void unequip(Weapon *weapon);
        void notifyStats();
        int attackTo(PlayableCharacter *enemy);
        int attackTo(Npc *enemy);
        bool checkFairPlay(int enemyLevel);
        int receiveAttackFrom(PlayableCharacter *enemy) override;
        void notifyEquipment();
        ~PlayableCharacter() override;
};


#endif //ARGENTUM_PLAYABLECHARACTER_H
