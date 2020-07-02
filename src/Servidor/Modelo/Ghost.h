//
// Created by franco on 30/6/20.
//

#ifndef ARGENTUM_GHOST_H
#define ARGENTUM_GHOST_H


#include "LifeState.h"

class Ghost: public LifeState {
public:
    void attackEnemy(PlayableCharacter* character,Character *enemy) override;
    int modifyLifePointsFrom(PlayableCharacter *character, int enemyLevel, int damage) override;
    void store(Equippable *element, Inventory &inventory, Observer *observer) override;
    void heal(float maxLife, float &lifePoints, float value) override;
    void earnMana(float maxMana, float &mana, float value) override;
    void recoverLifePoints(float &lifePoints,float maxLife,float recoveredLifePoints) override;
    void recoverMana(float &mana, float maxMana, float recoveredMana) override;
    void equip(PlayableCharacter *character, Inventory &inventory, int indexElement) override;
    void unequip(PlayableCharacter *character, Inventory &inventory, int indexElement) override;
    bool dead() override;
};


#endif //ARGENTUM_GHOST_H