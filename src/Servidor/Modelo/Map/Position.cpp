#include <cmath>
#include <iostream>
#include "Position.h"
Position::Position(int x,int y):x(x),y(y) {}

void Position::apply(Offset& offset) {
    this->x = offset.move_x(x);
    this->y = offset.move_y(y);
}

bool Position::outOfBounds(int initialX,int finalX,int initialY,int finalY) {
    return (this->x < initialX || this->x >= finalX || this->y < initialY || this->y >= finalY);
}

bool Position::operator==(const Position& position) const {
    return (this->x == position.x && this->y == position.y);
}

Position& Position::operator=(const Position& position) {
    this->x = position.x;
    this->y = position.y;

    return *this;
}

int Position::distanceTo(Position& position) const {
    double  xSquare = pow(this->x - position.x,2);
    double  ySquare = pow(this->y - position.y,2);
    return (int)sqrt(xSquare + ySquare);
}

Offset Position::operator-(Position& position) const {
    return Offset(x - position.x,y - position.y);
}

int Position::getX() const {
    return this->x;
}

int Position::getY() const {
    return this->y;
}

Position::~Position() = default;