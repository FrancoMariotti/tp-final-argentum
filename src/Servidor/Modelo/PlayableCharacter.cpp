#include "PlayableCharacter.h"
#include <utility>
#include "Potion.h"
#include "Map.h"
#include "Npc.h"
#include "Alive.h"
#include "Ghost.h"

#define NEWBIE_LEVEL 12
#define LEVEL_DIFFERENCE 10

PlayableCharacter::PlayableCharacter(std::string id,Map* map, Position &initialPosition,int constitution,
        int strength,int agility,int intelligence,int level, int raceLifeFactor, int classLifeFactor,
        int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor,
        int invMaxElements,Observer* observer):
        Character(std::move(id),map,initialPosition,constitution,strength,agility,intelligence,level,raceLifeFactor,
                classLifeFactor, raceManaFactor, classManaFactor,recoveryFactor,meditationRecoveryFactor,observer),
                defaultWeapon("none",1, 1, 0), inventory(invMaxElements) {
    this->lifeState = new Alive();
    this->activeWeapon = &defaultWeapon;
    this->mana = calculateMaxMana();
    this->gold = 0;
    this->xp = 0;
    notifyStats();
    notifyEquipment();
}

void PlayableCharacter::notifyStats() {
    float health_percentage = lifePoints / calculateMaxLife();
    float mana_percentage = mana / calculateMaxMana();
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

void PlayableCharacter::recoverLifePoints(float seconds) {
    float maxLife = calculateMaxLife();
    float recoveredLifePoints = calculateRecoverLifePoints(seconds);
    lifeState->recoverLifePoints(lifePoints,maxLife,recoveredLifePoints);
    notifyStats();
}

void PlayableCharacter::recoverMana(float seconds) {
    float maxMana = calculateMaxMana();
    float recoveredMana = calculateRecoverMana(seconds);
    lifeState->recoverMana(mana, maxMana, recoveredMana);
    notifyStats();
}

void PlayableCharacter::attack(Character *character) {
    lifeState->attackEnemy(this,character);
}

void PlayableCharacter::makeDamageTo(Character *character) {
    int earnedXp = character->receiveAttackFrom(this);

    int limit = calculateLvlLimit();
    int totalXp = earnedXp + xp;

    if(totalXp >= limit) {
        xp = totalXp - limit;
        this->level++;
    } else {
        xp += earnedXp;
    }
}

int PlayableCharacter::receiveDamage(int enemyLevel, int damage) {
    return lifeState->modifyLifePointsFrom(this,enemyLevel,damage);
}

int PlayableCharacter::modifyLifePoints(int enemyLevel, int damage) {
    int xpEarned = 0;

    if (dodge()) {
        return xpEarned;
    }

    damage = defend(damage);

    float newLife = lifePoints - damage;
    xpEarned = calculateAttackXp(damage,enemyLevel);

    if (newLife <= 0) {
        lifePoints = 0;
        die();
        int maxLifePoints = (int)calculateMaxLife();
        xpEarned += calculateKillXp(maxLifePoints,enemyLevel);
    } else {
        lifePoints = newLife;
    }

    notifyStats();
    return xpEarned;
}

int PlayableCharacter::attackTo(PlayableCharacter *enemy) {
    int earnedXp = 0;
    bool canAttack = enemy->checkFairPlay(level);
    if(canAttack) earnedXp = activeWeapon->attack(enemy,strength,level,mana,currPos);
    return earnedXp;
}

int PlayableCharacter::attackTo(Npc *enemy) {
    return activeWeapon->attack(enemy,strength,level,mana,currPos);
}

void PlayableCharacter::store(Equippable* element) {
    lifeState->store(element,inventory,observer);
}

void PlayableCharacter::equip(int elementIndex) {
    lifeState->equip(this,inventory,elementIndex);
}

void PlayableCharacter::equip(Equippable* element, int index) {
    element->equipTo(this, index);
}

void PlayableCharacter::equip(Weapon* weapon, int index) {
    activeWeapon = weapon;
    notifyEquipment();
}

void PlayableCharacter::equip(Protection* protection, int index) {
    armour.equip(protection);
    notifyEquipment();
}

void PlayableCharacter::equip(Potion* potion, int index) {
    potion->use(this);
    Equippable* element = inventory.takeElement(index);
    delete element;
}

void PlayableCharacter::unequip(int elementIndex) {
    lifeState->unequip(this,inventory,elementIndex);
}

void PlayableCharacter::unequip(Equippable* element) {
    element->unequipFrom(this);
}

void PlayableCharacter::unequip(Weapon* weapon) {
    activeWeapon = &defaultWeapon;
    notifyEquipment();
}

void PlayableCharacter::unequip(Protection* protection) {
    armour.unequip(protection);
    notifyEquipment();
}

int PlayableCharacter::defend(int damage) {
    return armour.use(damage);
}

void PlayableCharacter::heal(int value) {
    float maxLife = calculateMaxLife();
    lifeState->heal(maxLife,lifePoints,(float)value);
}

void PlayableCharacter::earnMana(int value) {
    float maxMana = calculateMaxMana();
    lifeState->earnMana(maxMana,mana,(float)value);

}

bool PlayableCharacter::checkFairPlay(int enemyLevel) {
    int levelDifference = abs(enemyLevel - level);
    if(levelDifference > LEVEL_DIFFERENCE) return false;
    bool enemyisnewbie = (enemyLevel <= NEWBIE_LEVEL);
    bool imnewbie = (level <= NEWBIE_LEVEL);
    return (imnewbie && enemyisnewbie);
}

int PlayableCharacter::receiveAttackFrom(PlayableCharacter *enemy) {
    return enemy->attackTo(this);
}

bool PlayableCharacter::isDead() {
    return lifeState->dead();
}

void PlayableCharacter::die() {
    /*Drop drop(currPos.nearAvailablePosition(map));
    int safeGold = calculateSafeGoldCapacity(level);
    if (gold > safeGold) {
        int amountGoldDrop = gold - safeGold;
        drop.addGold(amountGoldDrop);
    }*/

    //logica drop items inventario

    delete lifeState;
    lifeState = new Ghost();
}

void PlayableCharacter::sellTo(int itemIndex, Merchant *merchant) {
    Equippable* item = inventory.takeElement(itemIndex);
    gold += merchant->buy(item->getName());
    delete item;
}

void PlayableCharacter::buyFrom(const std::string& itemName, Merchant *merchant) {
    Equippable* item = merchant->sell(itemName, &gold);
    if (item != nullptr) inventory.store(item);
}

PlayableCharacter::~PlayableCharacter() {
    delete lifeState;
    if (activeWeapon != &defaultWeapon) delete activeWeapon;
}
