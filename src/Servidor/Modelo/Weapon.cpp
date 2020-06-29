#include "Weapon.h"
#include "PlayableCharacter.h"

Weapon::Weapon(std::string name, int minDamage, int maxDamage) : Equippable(name, minDamage, maxDamage) {
    //this->minDamage = minDamage;
    //this->maxDamage = maxDamage;
}

int Weapon::calculateDamage(int strength) {
    //int range = this->maxDamage - minDamage;
    //return strength * (std::rand() % range + minDamage);
    return strength * randomize();
}

void Weapon::equipTo(PlayableCharacter *character, int index) {
    equipped = true;
    character->equip(this, index);
}

void Weapon::unequipFrom(PlayableCharacter *character) {
    equipped = false;
    character->unequip(this);
}
