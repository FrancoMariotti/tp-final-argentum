#include <iostream>
#include "PlayableCharacter.h"
#include "Mobility.h"
#include "Game.h"
#include "Log.h"

PlayableCharacter::PlayableCharacter(int lifePoints, int x, int y,int constitution,
        int strength,int agility,int intelligence, int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor)
                  :Character(lifePoints,x, y,constitution,strength,agility,intelligence,
                          raceLifeFactor, classLifeFactor, raceManaFactor,
                          classManaFactor,recoveryFactor,meditationRecoveryFactor) {
        this->activeWeapon = NULL;
        this->mana = 0;
        this->level = 1;
        this->gold = 0;
        this->xp =0;
}

void PlayableCharacter::move(Map* map,Offset& offset) {
    Position siguiente(this->currPos);
    siguiente.apply(offset);
    map->move(this->currPos,siguiente);
    //game->addUpdatePosition(currPos.getX(),currPos.getY());
}

void PlayableCharacter::attack(Character *character) {
    activeWeapon->attack(character,strength,mana,currPos);
}

void PlayableCharacter::equipWeapon(Weapon* weapon) {
    activeWeapon = weapon;
}

void PlayableCharacter::equipShield(int minDef, int maxDef) {
    armour.equipShield(minDef, maxDef);
}

int PlayableCharacter::defend(int damage) {
    return armour.use(damage);
}

PlayableCharacter::~PlayableCharacter() {
    /*if(activeWeapon){
        delete activeWeapon;
    }*/
}