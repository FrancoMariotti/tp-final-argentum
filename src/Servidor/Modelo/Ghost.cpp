#include "Ghost.h"
#include "PlayableCharacter.h"
#include "Alive.h"

void Ghost::attackEnemy(PlayableCharacter *character, Character *enemy) {}

int Ghost::modifyLifePointsFrom(PlayableCharacter *character, int enemyLevel, int damage) {
    return 0;
}

void Ghost::store(Equippable *element, Inventory &inventory, Observer *observer) {}

void Ghost::heal(float maxLife, float &lifePoints, float value) {}

void Ghost::earnMana(float maxMana, float &mana, float value) {}

void Ghost::recoverLifePoints(float &lifePoints, float maxLife, float recoveredLifePoints) {}

void Ghost::recoverMana(float &mana, float maxMana, float recoveredMana) {}

void Ghost::equip(PlayableCharacter *character, Inventory &inventory, int indexElement) {}

void Ghost::unequip(PlayableCharacter *character, Inventory &inventory, int indexElement) {}

bool Ghost::dead() {
    return true;
}

LifeState* Ghost::revive(PlayableCharacter *character) {
    character->restoreLife();
    character->restoreMana();
    character->notifyEquipment();
    character->notifyStats();
    return new Alive();
}

Position Ghost::teleportFromTo(Position from, Position to) {
    return to;
}

PlayableCharacter * Ghost::closestToInRange(const Position &position,
        PlayableCharacter *closestEnemy, int *minDist, int range,
        PlayableCharacter *me) {
    return closestEnemy;
}

void Ghost::healedByPriest(PlayableCharacter *character) {}

void Ghost::takeDrop(Map *map, Position position, PlayableCharacter *pCharacter) {}


