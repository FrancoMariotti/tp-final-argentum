#include "PlayableCharacter.h"
#include "Log.h"

PlayableCharacter::PlayableCharacter(Map* map, Position &initialPosition,int constitution,
        int strength,int agility,int intelligence,int level, int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor,
                  int invMaxElements)
                  :Character(map,initialPosition,constitution,strength,agility,intelligence,level,
                          raceLifeFactor, classLifeFactor, raceManaFactor,
                          classManaFactor,recoveryFactor,meditationRecoveryFactor), inventory(invMaxElements) {
        this->activeWeapon = nullptr;
        this->mana = 0;
        this->gold = 0;
        this->xp = 0;
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
    int earnedXp= activeWeapon->attack(character,strength,level,mana,currPos);
    int limit = calculateLvlLimit();
    int totalXp = earnedXp + xp;

    Log* log = Log::instancia();
    log->write("El limit level es:");
    log->writeInt(limit);

    log->write("El xp ganado es:");
    log->writeInt(earnedXp);

    log->write("El level actual es:");
    log->writeInt(level);

    log->write("El xp actual es:");
    log->writeInt(xp);

    if(totalXp >= limit) {
        xp = totalXp - limit;
        this->level ++;
    } else {
        xp += earnedXp;
    }

    log->write("El level actual es:");
    log->writeInt(level);

    log->write("El xp actual es:");
    log->writeInt(xp);
}

void PlayableCharacter::store(Equippable* element) {
    inventory.store(element);
}

void PlayableCharacter::recoverMana(int seconds) {
    this->mana += calculateRecoverMana(seconds);
}

void PlayableCharacter::equip(int elementIndex) {
    Equippable* element = inventory.takeElement(elementIndex);
    equip(element);
}

void PlayableCharacter::equip(Equippable* element) {
    element->equipTo(this);
}

void PlayableCharacter::equip(Weapon* weapon) {
    activeWeapon = weapon;
}

void PlayableCharacter::equip(Protection* protection) {
    armour.equip(*protection);
}

void PlayableCharacter::equip(Potion* potion) {
    potion->use(this);
}

int PlayableCharacter::defend(int damage) {
    return armour.use(damage);
}

void PlayableCharacter::heal(int value) {
    Log* log = Log::instancia();
    log->write("Vida antes de curar:");
    log->writeInt(lifePoints);

    int maxLife = calculateMaxLife();
    if (lifePoints + value >= maxLife) {
        lifePoints = maxLife;
    } else {
        lifePoints += value;
    }
    log->write("Vida despues de curar:");
    log->writeInt(lifePoints);
}

void PlayableCharacter::earnMana(int value) {
    Log* log = Log::instancia();
    log->write("Mana antes de agregar:");
    log->writeInt(mana);

    int maxMana = calculateMaxMana();
    if (mana + value >= maxMana) {
        mana = maxMana;
    } else {
        mana += value;
    }
    log->write("Mana despues de agregar:");
    log->writeInt(mana);
}

PlayableCharacter::~PlayableCharacter() {
    /*if(activeWeapon){
        delete activeWeapon;
    }*/
}
