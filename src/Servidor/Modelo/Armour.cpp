//
// Created by franco on 19/6/20.
//

#include "Armour.h"
#include "Character.h"

Armour::Armour() {
    Equippable null(0, 0);
    for (int i = 0; i < 3 ; ++i) {
        elements.push_back(null);
    }
}
/*
Armour::Armour(int chestMinDef, int chestMaxDef, int shieldMinDef, int shieldMaxDef
    , int helmetMinDef, int helmetMaxDef) : chestMinDef(chestMinDef), chestMaxDef(chestMaxDef),
    shieldMinDef(shieldMinDef), shieldMaxDef(shieldMaxDef), helmetMinDef(helmetMinDef),
    helmetMaxDef(helmetMaxDef){

}
 */

void Armour::equip(Equippable element, int id) {
    elements[id] = element;
}

int Armour::use(int damage) const {
    int defense = 0;
    for (int i = 0; i < 3; ++i) {
        defense += elements[i].randomize();
    }
    int result = damage - defense;
    if (result < 0) return 0;
    return result;
}
