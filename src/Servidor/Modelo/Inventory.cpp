#include "Inventory.h"
#include "string"

Inventory::Inventory(unsigned int maxElements):maxElements(maxElements) {}

void Inventory::sendItems(Observer *observer) {
    std::vector<std::string> items;
    for(auto &element:elements) {
        items.push_back(element->getName());
    }
    observer->notifyItemsUpdate(items);
}

void Inventory::store(Equippable* element) {
    if (elements.size() != maxElements) elements.push_back(element);
}

Equippable* Inventory::chooseElement(int index) {
    return elements[index];
}

Equippable* Inventory::takeElement(int index, PlayableCharacter* character) {
    Equippable* element = elements[index];
    if (element->isEquipped()) element->unequipFrom(character);
    elements.erase(elements.begin() + index);
    return element;
}

Equippable* Inventory::takeElement(std::string elementName,PlayableCharacter* character) {
    for(unsigned int i = 0; i < elements.size(); i++) {
        if(elements[i]->getName() == elementName) {
            if (elements[i]->isEquipped())elements[i]->unequipFrom(character);
            elements.erase(elements.begin() + i);
            return elements[i];
        }
    }
    return nullptr;
}
