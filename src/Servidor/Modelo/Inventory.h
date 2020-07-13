#ifndef ARGENTUM_INVENTORY_H
#define ARGENTUM_INVENTORY_H

#include <vector>
#include "Equippable.h"
#include "Observer.h"

class Inventory {
    unsigned int maxElements;
    std::vector<Equippable*> elements;
public:
    explicit Inventory(unsigned int maxElements);
    void store(Equippable* element);
    Equippable* chooseElement(int index);
    Equippable* takeElement(int index, PlayableCharacter* character);
    void sendItems(Observer *observer);

    Equippable *takeElement(const std::string& elementName, PlayableCharacter *character);

    int getItemsAmount();

    int getItemIndex(std::string itemName);
};


#endif //ARGENTUM_INVENTORY_H
