//
// Created by franco on 11/6/20.
//

#include <cmath>
#include <iostream>
#include "Position.h"
Position::Position(int x,int y):x(x),y(y) {}

void Position::apply(Offset& offset) {
    x = offset.move_x(x);
    y = offset.move_y(y);
}

bool Position::operator==(const Position& position) {
    return (this->x == position.x && this->y == position.y);
}

void Position::operator=(const Position& position) {
    this->x = position.x;
    this->y = position.y;
}

int Position::distanceTo(Position& position) {
    double  xSquare = pow(this->x - position.x,2);
    double  ySquare = pow(this->y - position.y,2);
    return (int)sqrt(xSquare + ySquare);
}

Offset Position::operator-(Position& position) {
    return Offset(this->x - position.x,this->y - position.y);
}

Position::~Position() {}

void Position::print() {
    std::cout << "x = " << x << " y = " << y << std::endl;
}