#include "Mobility.h"
#define MAX_RANGE 4

void Movable::move(Position& currPos, Map* map) {
    Offset offset(0,0);

    Character* enemy = map->findClosestCharacter(currPos, MAX_RANGE);
    if (!enemy) {
        offset.randomDir();
    } else {
        offset = enemy->getOffset(currPos);
        offset.approach();
    }

    Position siguiente(currPos);
    siguiente.apply(offset);
    map->move(currPos,siguiente);
}

Movable::~Movable() =default;

void NonMovable::move(Position& position, Map* map) {}

NonMovable::~NonMovable() = default;