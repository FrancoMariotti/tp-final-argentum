//
// Created by franco on 15/6/20.
//

#include "Player.h"

Player::Player(Map& map) : character(100, 1, 1, map) {}
/*
bool Player::exists(std::string name) {
    if (this->name == name) return true;
    return false;
}
*/
void Player::move(Offset offset) {
    character.move(offset);
}
