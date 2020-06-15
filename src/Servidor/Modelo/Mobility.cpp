#include "Mobility.h"

Mobility::~Mobility() = default;

void Movable::move(Position& position, Map& map, StrategyMoveNPC movement) {
    movement.move(position,map);
}

Movable::~Movable() =default;

void NonMovable::move(Position& position, Map& map, StrategyMoveNPC movement) {}

NonMovable::~NonMovable() = default;