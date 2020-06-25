#include "Armour.h"

Armour::Armour() {
    Equippable null(0, 0);
    for (int i = 0; i < 3 ; ++i) {
        elements.push_back(null);
    }
}

void Armour::equip(Equippable element, Equipment equipment) {
    elements[equipment] = element;
}

int Armour::use(int damage) const {
    int defense = 0;

    auto it = elements.begin();
    for(;it != elements.end(); it++) {
        defense += (*it).randomize();
    }

    int result = damage - defense;
    if (result < 0) return 0;
    return result;
}
