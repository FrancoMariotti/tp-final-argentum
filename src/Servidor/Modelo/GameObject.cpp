//
// Created by franco on 8/6/20.
//

#include "GameObject.h"
Posicion::Posicion(int x,int y):x(x),y(y) {}

void Posicion::aplicar(Direccion *direccion) {
    x = direccion->mover_x(x);
    y = direccion->mover_y(y);
}

bool Posicion::operator==(const Posicion& posicion) {
    return (this->x == posicion.x && this->y == posicion.y);
}

void Posicion::operator=(Posicion& posicion) {
    this->x = posicion.x;
    this->y = posicion.y;
    posicion.x = -1;
    posicion.y = -1;
}

Posicion::~Posicion() {}

GameObject::GameObject(int x,int y,Mapa& mapa):posicion(x,y),mapa(mapa) {
    mapa.agregar(&posicion);
}

void GameObject::mover(Direccion *direccion) {
    Posicion siguiente(posicion);
    siguiente.aplicar(direccion);
    mapa.mover(posicion,siguiente);
}

Posicion GameObject::get_posicion() {
    return this->posicion;
}

GameObject::~GameObject() {}