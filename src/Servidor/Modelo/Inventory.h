#ifndef ARGENTUM_INVENTORY_H
#define ARGENTUM_INVENTORY_H

#include <vector>
#include "Equippable.h"
#include "Observer.h"

class Inventory {
    unsigned int maxElements;
    std::vector<Equippable*> elements;
    Observer* observer;
public:
    explicit Inventory(unsigned int maxElements,Observer* observer);
    void store(Equippable* element);
    Equippable* chooseElement(int index);
    Equippable* takeElement(int index);
    void sendItems();
};


#endif //ARGENTUM_INVENTORY_H
