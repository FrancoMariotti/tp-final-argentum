#include "Armour.h"

Armour::Armour() {
    Protection null("none", 0, 0, NONE, 0);
    for (int i = 0; i < 3 ; ++i) {
        protections.push_back(null);
    }
}

void Armour::equip(Protection protection) {
    protection.equip(protections);
}

int Armour::use(int damage) const {
    int defense = 0;

    auto it = protections.begin();
    for(;it != protections.end(); it++) {
        defense += (*it).randomize();
    }

    int result = damage - defense;
    if (result < 0) return 0;
    return result;
}

void Armour::unequip(Protection protection) {
    protection.unequip(protections);
}

std::string Armour::getName(int equipmentId) {
    return protections[equipmentId].getName();
}
