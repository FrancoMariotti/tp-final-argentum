//
// Created by franco on 19/6/20.
//

#include "Armour.h"
#include "Character.h"

Armour::Armour() : chestMinDef(0), chestMaxDef(0), shieldMinDef(0), shieldMaxDef(0),
    helmetMinDef(0), helmetMaxDef(0) {

}

Armour::Armour(int chestMinDef, int chestMaxDef, int shieldMinDef, int shieldMaxDef
    , int helmetMinDef, int helmetMaxDef) : chestMinDef(chestMinDef), chestMaxDef(chestMaxDef),
    shieldMinDef(shieldMinDef), shieldMaxDef(shieldMaxDef), helmetMinDef(helmetMinDef),
    helmetMaxDef(helmetMaxDef){

}

void Armour::equipChest(int minDef, int maxDef) {
    chestMinDef = minDef;
    chestMaxDef = maxDef;
}

void Armour::equipShield(int minDef, int maxDef) {
    shieldMinDef = minDef;
    shieldMaxDef = maxDef;
}

void Armour::equipHelmet(int minDef, int maxDef) {
    helmetMinDef = minDef;
    helmetMaxDef = maxDef;
}

int Armour::use(int damage) const {
    int defense = Character::calculateDefense(chestMinDef, chestMaxDef
            , shieldMinDef, shieldMaxDef, helmetMinDef, helmetMaxDef);
    int result = damage - defense;
    if (result < 0) return 0;
    return result;
}