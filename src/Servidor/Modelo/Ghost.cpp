#include "Ghost.h"

void Ghost::attackEnemy(PlayableCharacter *character, Character *enemy) {}

int Ghost::modifyLifePointsFrom(PlayableCharacter *character, int enemyLevel, int damage) {
    return 0;
}

void Ghost::store(Equippable *element, Inventory &inventory, Observer *observer) {}

void Ghost::heal(int maxLife, int &lifePoints, int value) {}

void Ghost::earnMana(int maxMana, int &mana, int value) {}

void Ghost::recoverLifePoints(int &lifePoints, int maxLife, int recoveredLifePoints) {}

void Ghost::recoverMana(int &mana, int maxMana, int recoveredMana) {}

void Ghost::equip(PlayableCharacter *character, Inventory &inventory, int indexElement) {}

void Ghost::unequip(PlayableCharacter *character, Inventory &inventory, int indexElement) {}

bool Ghost::dead() {
    return true;
}


