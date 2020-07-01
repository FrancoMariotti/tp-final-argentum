//
// Created by franco on 30/6/20.
//

#ifndef ARGENTUM_LIFESTATE_H
#define ARGENTUM_LIFESTATE_H

#include "PlayableCharacter.h"

class LifeState {
public:
    virtual void attackEnemy(PlayableCharacter* character,Character *enemy) = 0;
    virtual int modifyLifePointsFrom(PlayableCharacter *character, int enemyLevel, int damage) = 0;
    virtual void store(Equippable *element, Inventory &inventory, Observer *observer) = 0;
    virtual void heal(int maxLife, int &lifePoints, int value) = 0;
    virtual void earnMana(int maxMana, int &mana, int value) = 0;
    virtual void recoverLifePoints(int &lifePoints,int maxLife,int recoveredLifePoints) = 0;
    virtual void recoverMana(int &mana, int maxMana, int recoveredMana) = 0;
    virtual void equip(PlayableCharacter *character, Inventory &inventory, int indexElement) = 0;
    virtual void unequip(PlayableCharacter *character, Inventory &inventory, int indexElement) = 0;
    virtual bool dead() = 0;
    virtual ~LifeState() = default;
};


#endif //ARGENTUM_LIFESTATE_H
