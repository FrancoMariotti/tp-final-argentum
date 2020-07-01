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
    void heal(int maxLife, int &lifePoints, int value) override;
    void earnMana(int maxMana, int &mana, int value) override;
    void recoverLifePoints(int &lifePoints,int maxLife,int recoveredLifePoints) override;
    void recoverMana(int &mana, int maxMana, int recoveredMana) override;
    void equip(PlayableCharacter *character, Inventory &inventory, int indexElement) override;
    void unequip(PlayableCharacter *character, Inventory &inventory, int indexElement) override;
    bool dead() override;
};


#endif //ARGENTUM_GHOST_H
