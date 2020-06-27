#ifndef ARGENTUM_INVENTORY_H
#define ARGENTUM_INVENTORY_H

#include <vector>
#include "Equippable.h"

class Inventory {
    unsigned int maxElements;
    std::vector<Equippable*> elements;
    public:
        explicit Inventory(unsigned int maxElements);
        void store(Equippable* element);
        Equippable* chooseElement(int index);
        Equippable* takeElement(int index);
};


#endif //ARGENTUM_INVENTORY_H
