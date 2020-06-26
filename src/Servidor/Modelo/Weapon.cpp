#include "Weapon.h"
#include "PlayableCharacter.h"

Weapon::Weapon(int minDamage, int maxDamage) : Equippable(minDamage, maxDamage) {
    //this->minDamage = minDamage;
    //this->maxDamage = maxDamage;
}

int Weapon::calculateDamage(int strength) {
    //int range = this->maxDamage - minDamage;
    //return strength * (std::rand() % range + minDamage);
    return strength * randomize();
}

void Weapon::equipTo(PlayableCharacter *character) {
    character->equip(this);
}
