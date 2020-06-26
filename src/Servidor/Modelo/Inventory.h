#ifndef ARGENTUM_INVENTORY_H
#define ARGENTUM_INVENTORY_H


#include <vector>
#include "Equippable.h"

class Inventory {
    int maxElements;
    std::vector<Equippable*> elements;
public:
    Inventory(int maxElements);
    void store(Equippable* element);
    Equippable* takeElement(int index);
};


#endif //ARGENTUM_INVENTORY_H
