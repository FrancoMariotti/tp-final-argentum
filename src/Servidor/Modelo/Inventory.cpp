#include "Inventory.h"

Inventory::Inventory(int maxElements) : maxElements(maxElements) {}

void Inventory::store(Equippable* element) {
    if ((int)elements.size() != maxElements) elements.push_back(element);
}

Equippable* Inventory::takeElement(int index) {
    Equippable* element = elements[index];
    std::vector<Equippable*> aux;
    for (unsigned int i = 0; i < elements.size() ; ++i) {
        if (i != (unsigned)index) {
            aux.push_back(elements[i]);
        }
    }
    elements.swap(aux);
    return element;
}