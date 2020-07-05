//
// Created by franco on 1/7/20.
//

#include "Drop.h"

#include <utility>

Drop::Drop(Position& position, Droppable* droppable, std::string name) :
    position(position), item(droppable), name(std::move(name)){}

Position Drop::getPosition() {
    return position;
}

std::string Drop::getName() {
    return name;
}

/*
void Drop::addGold(int dropGold) {
    this->gold += dropGold;
}
*/