#include <algorithm>
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

Equippable* Inventory::takeElement(const std::string& elementName,PlayableCharacter* character) {
    Equippable* result = nullptr;
    auto itr = elements.begin();
    for (;itr != elements.end(); itr ++) {
        if ((*itr)->getName() ==  elementName) {
            result = *itr;
            if (result->isEquipped()) {
                result->unequipFrom(character);
            }
        }
    }

    elements.erase(std::remove_if(elements.begin(),
                                  elements.end(),
                                  [elementName](Equippable * equippable){return equippable->getName() == elementName;}),
                   elements.end());

    return result;
}
