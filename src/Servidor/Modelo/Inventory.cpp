#include "Inventory.h"

Inventory::Inventory(int maxElements) : maxElements(maxElements) {}

bool Inventory::addEquippable(Equippable* element) {
    if ((int)elements.size() == maxElements) return false;
    elements.push_back(element);
    return true;
}

Equippable* Inventory::takeElement(int index) {
    Equippable* element = elements[index];
    std::vector<Equippable*> aux;
    for (auto i = 0; i < maxElements ; ++i) {
        if (i != index) {
            aux.push_back(elements[i]);
        }
    }
    elements.swap(aux);
    return element;
}