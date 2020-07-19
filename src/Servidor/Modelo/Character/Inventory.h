#ifndef ARGENTUM_INVENTORY_H
#define ARGENTUM_INVENTORY_H

#include <vector>
#include "Servidor/Modelo/Equippables/Equippable.h"
#include "Servidor/Modelo/Observer.h"

class Inventory {
    std::string& id;
    friend class PlayableCharacterFactory;
    unsigned int maxElements;
    std::vector<Equippable*> elements;
public:
    Inventory(std::string& id,unsigned int maxElements);
    void store(Equippable* element);
    Equippable* chooseElement(int index);
    Equippable* takeElement(int index, PlayableCharacter* character);
    void sendItems(Observer *observer);

    Equippable *takeElement(const std::string& elementName, PlayableCharacter *character);

    int getItemsAmount();

    int getItemIndex(std::string itemName);

    bool isFull();
};


#endif //ARGENTUM_INVENTORY_H
