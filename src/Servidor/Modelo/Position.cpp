//
// Created by franco on 11/6/20.
//

#include <cmath>
#include "Position.h"
Position::Position(int x,int y):x(x),y(y) {}

void Position::aplicar(Offset& offset) {
    x = offset.move_x(x);
    y = offset.move_y(y);
}

bool Position::operator==(const Position& posicion) {
    return (this->x == posicion.x && this->y == posicion.y);
}

void Position::operator=(Position& posicion) {
    this->x = posicion.x;
    this->y = posicion.y;
    posicion.x = -1;
    posicion.y = -1;
}

int Position::distanceTo(Position& posicion) {
    double  xSquare = pow(this->x - posicion.x,2);
    double  ySquare = pow(this->y - posicion.y,2);
    return (int)sqrt(xSquare + ySquare);
}

Offset Position::operator-(Position& posicion) {
    return Offset(this->x - posicion.x,this->y - posicion.y);
}

Position::~Position() {}