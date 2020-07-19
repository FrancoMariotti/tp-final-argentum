#include <algorithm>
#include "Inventory.h"
#include "string"
#include "PlayableCharacter.h"

Inventory::Inventory(std::string& id,unsigned int maxElements):id(id),maxElements(maxElements) {}

void Inventory::sendItems(Observer *observer) {
    std::vector<std::string> items;
    for(auto &element:elements) {
        items.push_back(element->getName());
    }
    observer->notifyItemsUpdate(id,items);
}

void Inventory::store(Equippable* element) {
    if (elements.size() != maxElements) elements.push_back(element);
}

Equippable* Inventory::chooseElement(int index) {
    return elements[index];
}

Equippable* Inventory::takeElement(int index, PlayableCharacter* character) {
    Equippable* element = elements[index];
    //if (element->isEquipped()) element->unequipFrom(character);
    if (character->hasEquipped(element)) element->unequipFrom(character);
    elements.erase(elements.begin() + index);
    return element;
}

Equippable* Inventory::takeElement(const std::string& elementName,PlayableCharacter* character) {
    Equippable* result = nullptr;
    auto itr = elements.begin();
    for (;itr != elements.end(); itr ++) {
        if ((*itr)->getName() ==  elementName) {
            result = *itr;
            if (character->hasEquipped(result)) {
                result->unequipFrom(character);
            }
            elements.erase(itr--);
            break;
        }
    }

    return result;
}

int Inventory::getItemsAmount() {
    return elements.size();
}

int Inventory::getItemIndex(std::string itemName) {
    for (unsigned int i = 0; i < elements.size(); ++i) {
        if (elements[i]->getName() == itemName) return i;
    }
    return -1;
}

bool Inventory::isFull() {
    return elements.size() == maxElements;
}

