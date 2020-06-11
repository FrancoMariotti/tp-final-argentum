#include "GameObject.h"

GameObject::GameObject(int x,int y,Mapa& mapa):actual(x,y),mapa(mapa) {}

bool GameObject::colisiono(Position& posicionObj) {
    return (this->actual == posicionObj);
}

int GameObject::distanceTo(Position pos) {
    return this->actual.distanceTo(pos);
}

Offset GameObject::getOffset(Position inicial) {
    Position final(actual);
    return final - inicial;
}

GameObject::~GameObject() {}

void GameObject::printPosition() {
    actual.print();
}

