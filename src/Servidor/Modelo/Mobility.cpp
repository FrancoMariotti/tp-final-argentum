//
// Created by franco on 11/6/20.
//

#include "Mobility.h"

Mobility::~Mobility() = default;

void Movable::move(Position& position, Map& map, Offset& offset) {
    Position siguiente(position);
    siguiente.apply(offset);
    map.move(position,siguiente);
}
Movable::~Movable() =default;

void NonMovable::move(Position& position, Map& map, Offset& offset) {}

NonMovable::~NonMovable() = default;