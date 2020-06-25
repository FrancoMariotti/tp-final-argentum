#include "PlayableCharacter.h"

PlayableCharacter::PlayableCharacter(Map* map,int lifePoints, Position &initialPosition,int constitution,
        int strength,int agility,int intelligence,int level, int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor)
                  :Character(map,lifePoints,initialPosition,constitution,strength,agility,intelligence,level,
                          raceLifeFactor, classLifeFactor, raceManaFactor,
                          classManaFactor,recoveryFactor,meditationRecoveryFactor) {

        this->activeWeapon = nullptr;
        this->mana = 0;
        this->gold = 0;
        this->xp =0;
}

void PlayableCharacter::move(Offset& offset) {
    Position nextPos(this->currPos);
    nextPos.apply(offset);
    map->move(this->currPos,nextPos);
    if (currPos == nextPos) {
        observer->movementUpdate(offset.getX(), offset.getY());
    }
}

void PlayableCharacter::recoverLifePoints(int seconds) {
    this->lifePoints += calculateRecoverLifePoints(seconds);
}

void PlayableCharacter::attack(Character *character) {
    activeWeapon->attack(character,strength,level,&mana,currPos);
}

void PlayableCharacter::recoverMana(int seconds) {
    this->mana += calculateRecoverMana(seconds);
}

void PlayableCharacter::equipWeapon(Weapon* weapon) {
    activeWeapon = weapon;
}

void PlayableCharacter::equipProtection(Equippable element, Equipment equipment) {
    armour.equip(element, equipment);
}

int PlayableCharacter::defend(int damage) {
    return armour.use(damage);
}

PlayableCharacter::~PlayableCharacter() {
    /*if(activeWeapon){
        delete activeWeapon;
    }*/
}