#include "Weapon.h"
#include "PlayableCharacter.h"

Weapon::Weapon(std::string name, int id, int minDamage, int maxDamage, int goldCost)
    : Equippable(name, id, minDamage, maxDamage, goldCost), lastDamage(0) {
    //this->minDamage = minDamage;
    //this->maxDamage = maxDamage;
}

int Weapon::calculateDamage(int strength) {
    //int range = this->maxDamage - minDamage;
    //return strength * (std::rand() % range + minDamage);
    int damage = strength * randomize();
    lastDamage = damage;
    return damage;
}

void Weapon::equipTo(PlayableCharacter *character, int index) {
    //equipped = true;
    character->equip(this, index);
}

void Weapon::unequipFrom(PlayableCharacter *character) {
    //equipped = false;
    character->unequip(this);
}

int Weapon::getLastDamage() {
    return lastDamage;
}
