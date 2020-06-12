#include "GameObject.h"

GameObject::GameObject(int x,int y,Map& map):currPos(x,y),map(map) {}

bool GameObject::collideWith(Position& objPos) {
    return (this->currPos == objPos);
}

int GameObject::distanceTo(Position pos) {
    return this->currPos.distanceTo(pos);
}

Offset GameObject::getOffset(Position initialPos) {
    Position final(currPos);
    return final - initialPos;
}

GameObject::~GameObject() {}

void GameObject::printPosition() {
    currPos.print();
}

