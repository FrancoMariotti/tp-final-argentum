#include "Inventory.h"
#include "string"

Inventory::Inventory(unsigned int maxElements):maxElements(maxElements) {}

void Inventory::sendItems(Observer *observer) {
    std::vector<std::string> items;
    for(auto &element:elements) {
        items.push_back(element->getName());
    }
    observer->updateCharacterItems(items);
}

void Inventory::store(Equippable* element) {
    if (elements.size() != maxElements) elements.push_back(element);
}

Equippable* Inventory::chooseElement(int index) {
    return elements[index];
}

Equippable* Inventory::takeElement(int index) {
    Equippable* element = elements[index];
    elements.erase(elements.begin() + index);
    return element;
}
