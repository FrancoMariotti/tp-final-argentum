//
// Created by franco on 11/6/20.
//

#include "Mobility.h"
void Movable::move(Position& position, Map& map, Offset& offset) {
    Position siguiente(position);
    siguiente.apply(offset);
    map.mover(position,siguiente);
}

void NonMovable::move(Position& position, Map& map, Offset& offset) {}