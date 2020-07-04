//
// Created by franco on 30/6/20.
//

#include "Alive.h"
#include "PlayableCharacter.h"

void Alive::attackEnemy(PlayableCharacter *character, Character *enemy) {
    character->makeDamageTo(enemy);
}
int Alive::modifyLifePointsFrom(PlayableCharacter *character,int enemyLevel,int damage) {
    return character->modifyLifePoints(enemyLevel,damage);
}

void Alive::store(Equippable* element,Inventory& inventory,Observer* observer) {
    inventory.store(element);
    inventory.sendItems(observer);
}

void Alive::heal(float maxLife,float &lifePoints,float value) {
    if (lifePoints + value >= maxLife) {
        lifePoints = maxLife;
    } else {
        lifePoints += value;
    }
}

void Alive::earnMana(float maxMana,float &mana,float value) {
    if (mana + value >= maxMana) {
        mana = maxMana;
    } else {
        mana += value;
    }
}

void Alive::recoverLifePoints(float &lifePoints,float maxLife,float recoveredLifePoints) {
    if(lifePoints == maxLife) return;
    float newLife = lifePoints + recoveredLifePoints;

    if(newLife >= maxLife) lifePoints = maxLife;
    else lifePoints = newLife;
}

void Alive::recoverMana(float &mana,float maxMana,float recoveredMana) {
    if(mana == maxMana) return;
    float newMana = mana + recoveredMana;

    if(newMana >= maxMana) mana = maxMana;
    else mana = newMana;
}

void Alive::equip(PlayableCharacter* character,Inventory& inventory,int indexElement) {
    Equippable* element = inventory.chooseElement(indexElement);
    character->equip(element,indexElement);
}

void Alive::unequip(PlayableCharacter *character, Inventory &inventory, int indexElement) {
    Equippable* element = inventory.chooseElement(indexElement);
    character->unequip(element);
}

bool Alive::dead() {
    return false;
}

LifeState *Alive::revive(PlayableCharacter *character) {
    return nullptr;
}
