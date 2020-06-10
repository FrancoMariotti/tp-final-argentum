#include "GameObject.h"
Posicion::Posicion(float x,float y):x(x),y(y) {}

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

void Movible::mover(Posicion posicion,Mapa& mapa,Direccion *direccion) {
    Posicion siguiente(posicion);
    siguiente.aplicar(direccion);
    mapa.mover(posicion,siguiente);
}

void NoMovible::mover(Posicion posicion,Mapa& mapa,Direccion *direccion) {}

GameObject::GameObject(float x,float y,Mapa& mapa):posicion(x,y),mapa(mapa) {}

Posicion GameObject::get_posicion() {
    return this->posicion;
}

bool GameObject::colisiono(Posicion& posicionObj) {
    return (this->posicion == posicionObj);
}

GameObject::~GameObject() {}

PersonajeNpc::PersonajeNpc(int vida, Movilidad *movilidad, float x, float y, Mapa &mapa):GameObject(x,y,mapa),movilidad(movilidad) {
    mapa.agregar(this);
}

Personaje::Personaje(int vida,Movilidad* movilidad,float x,float y,Mapa& mapa):GameObject(x,y,mapa),movilidad(movilidad) {
    mapa.agregar(this);
}

void Personaje::mover(Direccion *direccion) {
    this->movilidad->mover(this->posicion,this->mapa,direccion);
}


