#include <iostream>
#include "Player.h"

Player::Player(Map& map) : character(100, 1, 1, map) {}
/*bool Player::exists(std::string name) {
    if (this->name == name) return true;
    return false;
}*/

void Player::move(Offset offset) {
    std::cout<<"posicion incial:"<<std::endl;
    character.printPosition();
    character.move(offset);
    std::cout<<"posicion despues:"<<std::endl;
    character.printPosition();
}

Player::~Player() = default;
