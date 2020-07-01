#include "Armour.h"

Armour::Armour() : defaultProtection("none", 0, 0, NONE, 0) {
    for (int i = 0; i < 3 ; ++i) {
        protections.push_back(&defaultProtection);
    }
}

void Armour::equip(Protection* protection) {
    protection->equip(protections);
}

int Armour::use(int damage) const {
    int defense = 0;

    auto it = protections.begin();
    for(;it != protections.end(); it++) {
        defense += (*it)->randomize();
    }

    int result = damage - defense;
    if (result < 0) return 0;
    return result;
}

void Armour::unequip(Protection* protection) {
    protection->unequip(protections, &defaultProtection);
}

std::string Armour::getName(int equipmentId) {
    return protections[equipmentId]->getName();
}

Armour::~Armour() {
    for (auto it = protections.begin(); it != protections.end(); it++) {
        if ((*it) != &defaultProtection) delete (*it);
    }
}