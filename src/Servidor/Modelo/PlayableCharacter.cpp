#include "PlayableCharacter.h"
#include "Log.h"
#include "Potion.h"
#include "Map.h"
#include "Npc.h"

PlayableCharacter::PlayableCharacter(std::string id,Map* map, Position &initialPosition,int constitution,
        int strength,int agility,int intelligence,int level, int raceLifeFactor, int classLifeFactor,
        int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor,
        int invMaxElements,Observer* observer):
        Character(id,map,initialPosition,constitution,strength,agility,intelligence,level,raceLifeFactor,
                classLifeFactor, raceManaFactor, classManaFactor,recoveryFactor,meditationRecoveryFactor,observer),
                defaultWeapon("fists",1, 1, 0), inventory(invMaxElements) {
    this->activeWeapon = &defaultWeapon;
    this->mana = calculateMaxMana();
    this->gold = 0;
    this->xp = 0;
    notifyStats();
    notifyEquipment();
}

void PlayableCharacter::notifyStats() {
    float health_percentage = (float)lifePoints / (float)calculateMaxLife();
    float mana_percentage = (float)mana / (float)calculateMaxMana();
    float exp_percentage = (float)xp / (float)calculateLvlLimit();
    observer->notifyStatsUpdate(health_percentage,mana_percentage,exp_percentage,this->gold,this->level);
}

void PlayableCharacter::notifyEquipment() {
    std::string weaponName = activeWeapon->getName();
    std::string armourName = armour.getName(ARMOUR);
    std::string shieldName = armour.getName(SHIELD);
    std::string helmetName = armour.getName(HELMET);
    observer->notifyEquipmentUpdate(weaponName, armourName, shieldName, helmetName);
}

void PlayableCharacter::move(Offset& offset) {
    Position nextPos(this->currPos);
    nextPos.apply(offset);
    map->move(this->currPos,nextPos);
    observer->notifymovementUpdate(this->currPos.getX(), this->currPos.getY());
}

void PlayableCharacter::recoverLifePoints(int seconds) {
    this->lifePoints += calculateRecoverLifePoints(seconds);
}

void PlayableCharacter::attack(Character *character) {
    int earnedXp = character->receiveAttackFrom(this);

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
        this->level++;
    } else {
        xp += earnedXp;
    }

    log->write("El level actual es:");
    log->writeInt(level);

    log->write("El xp actual es:");
    log->writeInt(xp);
}

int PlayableCharacter::receiveDamage(int enemyLevel, int damage) {
    if(lifePoints <= 0) return 0;
    int xpEarned = 0;

    if (dodge()) {
        return xpEarned;
    }

    damage = defend(damage);
    int newLife = lifePoints - damage;
    xpEarned = calculateAttackXp(damage,enemyLevel);

    if (newLife <= 0) {
        lifePoints = 0;
        int maxLifePoints = calculateMaxLife();
        xpEarned += calculateKillXp(maxLifePoints,enemyLevel);
    } else {
        lifePoints = newLife;
    }

    notifyStats();
    return xpEarned;
}

int PlayableCharacter::attackTo(PlayableCharacter *enemy) {
    bool canAttack = enemy->checkFairPlay(level);
    if(canAttack) return activeWeapon->attack(enemy,strength,level,mana,currPos);
    enemy->notifyStats();
    return 0;
}

int PlayableCharacter::attackTo(Npc *enemy) {
    return activeWeapon->attack(enemy,strength,level,mana,currPos);
}

void PlayableCharacter::store(Equippable* element) {
    inventory.store(element);
    inventory.sendItems(observer);
}

void PlayableCharacter::recoverMana(int seconds) {
    this->mana += calculateRecoverMana(seconds);
}

void PlayableCharacter::equip(int elementIndex) {
    Equippable* element = inventory.chooseElement(elementIndex);
    equip(element, elementIndex);
}

void PlayableCharacter::equip(Equippable* element, int index) {
    element->equipTo(this, index);
}

void PlayableCharacter::equip(Weapon* weapon, int index) {
    activeWeapon = weapon;
    notifyEquipment();
}

void PlayableCharacter::equip(Protection* protection, int index) {
    armour.equip(*protection);
    notifyEquipment();
}

void PlayableCharacter::equip(Potion* potion, int index) {
    potion->use(this);
    inventory.takeElement(index);
}

void PlayableCharacter::unequip(int elementIndex) {
    Equippable* element = inventory.chooseElement(elementIndex);
    unequip(element);
}

void PlayableCharacter::unequip(Equippable* element) {
    element->unequipFrom(this);
}

void PlayableCharacter::unequip(Weapon* weapon) {
    activeWeapon = &defaultWeapon;
    notifyEquipment();
}

void PlayableCharacter::unequip(Protection* protection) {
    armour.unequip(*protection);
    notifyEquipment();
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

bool PlayableCharacter::checkFairPlay(int enemyLevel) {
    int levelDifference = abs(enemyLevel - level);
    if(levelDifference > 10) return false;
    bool enemyisnewbie = (enemyLevel <= 12);
    bool imnewbie = (level <= 12);
    return (imnewbie && enemyisnewbie);
}

int PlayableCharacter::receiveAttackFrom(PlayableCharacter *enemy) {
    return enemy->attackTo(this);
}


PlayableCharacter::~PlayableCharacter() = default;
