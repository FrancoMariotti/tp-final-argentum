//
// Created by franco on 1/7/20.
//

#include "Drop.h"

Drop::Drop(Position& position):position(position) {
    this->gold = 0;
}

void Drop::addGold(int dropGold) {
    this->gold += dropGold;
}
