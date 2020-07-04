//
// Created by franco on 30/6/20.
//

#ifndef ARGENTUM_LIFESTATE_H
#define ARGENTUM_LIFESTATE_H

#include "Inventory.h"
#include "Character.h"

class LifeState {
public:
    virtual void attackEnemy(PlayableCharacter* character,Character *enemy) = 0;
    virtual int modifyLifePointsFrom(PlayableCharacter *character, int enemyLevel, int damage) = 0;
    virtual void store(Equippable *element, Inventory &inventory, Observer *observer) = 0;
    virtual void heal(float maxLife, float &lifePoints, float value) = 0;
    virtual void earnMana(float maxMana, float &mana, float value) = 0;
    virtual void recoverLifePoints(float &lifePoints,float maxLife,float recoveredLifePoints) = 0;
    virtual void recoverMana(float &mana, float maxMana, float recoveredMana) = 0;
    virtual void equip(PlayableCharacter *character, Inventory &inventory, int indexElement) = 0;
    virtual void unequip(PlayableCharacter *character, Inventory &inventory, int indexElement) = 0;
    virtual bool dead() = 0;
    virtual ~LifeState() = default;
    virtual LifeState* revive(PlayableCharacter *character) = 0 ;
    virtual Position teleportFromTo(Position from, Position to) = 0;

    virtual PlayableCharacter* closestToInRange(const Position &position,
            PlayableCharacter *closestEnemy, int *minDist, int range,PlayableCharacter *me) = 0;

    virtual void healedByPriest(PlayableCharacter* character) = 0;
};


#endif //ARGENTUM_LIFESTATE_H
