#ifndef ARGENTUM_INVENTORY_H
#define ARGENTUM_INVENTORY_H

#include <vector>
#include "Server/Model/Equippables/Equippable.h"
#include "Server/Model/Observer.h"

class Inventory {
    std::string& id;
    //friend class PlayableCharacterFactory;
    friend class PersistanceManager;
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
