#include "PlayableCharacter.h"
#include <utility>
#include "Server/Model/Equippables/Potion.h"
#include "Server/Model/Map/Map.h"
#include "Server/Model/Character/Npc.h"
#include "Server/Model/Character/Alive.h"
#include "Server/Model/Character/Ghost.h"
#include "ItemSeller.h"
#include "Server/Model/Dropppables/GoldBag.h"
#include "Server/Model/Configuration.h"
#include "NotMeditating.h"
#include "Server/Model/Character/Meditating.h"

PlayableCharacter::PlayableCharacter(std::string id,Map* map, Position &initialPosition,int constitution,
    int strength,int agility,int intelligence,int level, int raceLifeFactor, int classLifeFactor,
    int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor,
    int invMaxElements,Observer* observer, int raceId):
    Character(std::move(id),map,initialPosition,constitution,strength,agility,intelligence,level,raceLifeFactor,
            classLifeFactor, raceManaFactor, classManaFactor,recoveryFactor,meditationRecoveryFactor,observer),
            defaultWeapon("none", 0, 1, 1, 0),
            config(Configuration::getInstance()),
            inventory(this->id,invMaxElements), inCity(true), raceId(raceId) {
    this->lifeState = new Alive();
    this->activeWeapon = &defaultWeapon;
    this->mana = calculateMaxMana();
    this->gold = 0;
    this->xp = 0;
    this->meditationState = new NotMeditating();
    notifyStats();
    notifyEquipment();
}

PlayableCharacter::PlayableCharacter(std::string id, float lifePoints, Map *map, Position &initialPosition,
        int constitution, int strength, int agility, int intelligence, int level,
        int raceLifeFactor, int classLifeFactor, int raceManaFactor, int classManaFactor,
        int recoveryFactor, int meditationRecoveryFactor, Observer *observer, int raceId,
        float mana, int gold, int xp, int lifeState, bool inCity) :
        Character(std::move(id),map,initialPosition,constitution,strength,agility,intelligence,level,
                raceLifeFactor, classLifeFactor, raceManaFactor, classManaFactor,recoveryFactor,
                meditationRecoveryFactor,observer), mana(mana), gold(gold), xp(xp),
                defaultWeapon("none", 0, 1, 1, 0),
                config(Configuration::getInstance()),
                inventory(this->id, config.constants["inventoryMaxItems"]),
                inCity(inCity),raceId(raceId) {
    if (lifeState == 0) this->lifeState = new Alive();
    else this->lifeState = new Ghost();
    this->activeWeapon = &defaultWeapon;
    this->meditationState = new NotMeditating();
    notifyStats();
    notifyEquipment();
}

void PlayableCharacter::notifyStats() {
    float health_percentage = lifePoints / calculateMaxLife();
    float maxMana = calculateMaxMana();
    float mana_percentage;
    if (maxMana != 0) {
        mana_percentage = mana / calculateMaxMana();
    } else {
        mana_percentage = 0;
    }
    float exp_percentage = (float)xp / (float)calculateLvlLimit();
    observer->notifyStatsUpdate(id,health_percentage,mana_percentage,exp_percentage,this->gold,this->level);
}

void PlayableCharacter::notifyEquipment() {
    std::string weaponName = activeWeapon->getName();
    std::string armourName = armour.getName(ARMOUR);
    std::string shieldName = armour.getName(SHIELD);
    std::string helmetName = armour.getName(HELMET);
    observer->notifyEquipmentUpdate(id,weaponName, armourName, shieldName, helmetName);
}

void PlayableCharacter::move(Offset& offset) {
    Position nextPos(this->currPos);
    nextPos.apply(offset);
    map->move(this->currPos,nextPos);
    inCity = map->posInCity(currPos);
    observer->notifymovementUpdate(id,this->currPos.getX(), this->currPos.getY());
}

void PlayableCharacter::teleportTo(Position position) {
    currPos = lifeState->teleportFromTo(currPos, position);
    observer->notifymovementUpdate(id,this->currPos.getX(), this->currPos.getY());
}

void PlayableCharacter::recoverLifePoints(float seconds) {
    float maxLife = calculateMaxLife();
    float recoveredLifePoints = calculateRecoverLifePoints(seconds);
    lifeState->recoverLifePoints(lifePoints,maxLife,recoveredLifePoints);
    updateTime += seconds;
    if(updateTime >= config.constants["playerStatsUpdateTime"]) {
        notifyStats();
        updateTime = 0;
    }
}

void PlayableCharacter::recoverMana(float seconds) {
    float maxMana = calculateMaxMana();
    float recoveredMana = calculateRecoverMana(seconds);
    lifeState->recoverMana(mana, maxMana, recoveredMana);
    if(updateTime >= config.constants["playerStatsUpdateTime"]) {
        notifyStats();
        updateTime = 0;
    }
}

void PlayableCharacter::attack(Character *character) {
    if (!inCity) {
        lifeState->attackEnemy(this,character);
    }
}

void PlayableCharacter::makeDamageTo(Character *character) {
    int earnedXp = character->receiveAttackFrom(this);
    if (earnedXp < 0) {
        if (earnedXp == ATAQUE_ESQUIVADO) {
            std::vector<std::string> messages;
            std::string message = "El enemigo esquivo tu ataque";
            messages.push_back(message);
            notifyConsoleOutputUpdate(messages);
        }
        earnedXp = 0;
    }

    int limit = calculateLvlLimit();
    int totalXp = earnedXp + xp;

    if(totalXp >= limit) {
        xp = totalXp - limit;
        this->level++;
    } else {
        xp += earnedXp;
    }
    notifyStats();
}

int PlayableCharacter::receiveAttackFrom(PlayableCharacter *enemy) {
    return enemy->attackTo(this);
}

int PlayableCharacter::attackTo(PlayableCharacter *enemy) {
    int earnedXp = 0;
    bool canAttack = enemy->checkFairPlay(level);
    if(canAttack) {
        earnedXp = activeWeapon->attack(this,enemy,strength,level,mana,currPos);
        if (earnedXp > 0) {
            std::vector<std::string> messages;
            std::string weaponName = activeWeapon->getName();
            if (weaponName == "none") weaponName = "punios";
            std::string message = "Danio producido al atacar con " + weaponName;
            message += " :"+ std::to_string(activeWeapon->getLastDamage());
            messages.push_back(message);
            notifyConsoleOutputUpdate(messages);
            //Notifico los stats aca por si ataca con un arma magica que modifica los stats
            //no lo puedo hacer en el activeweapon->attack porque recibe objetos de la clase Character
            // y no tienen el metodo notifyStats
            notifyStats();
        }
    }
    return earnedXp;
}

int PlayableCharacter::attackTo(Npc *enemy) {
    int earnedXp = activeWeapon->attack(this,enemy,strength,level,mana,currPos);
    if (earnedXp > 0) {
        std::vector<std::string> messages;
        std::string weaponName = activeWeapon->getName();
        if (weaponName == "none") weaponName = "punios";
            std::string message = "Danio producido al atacar con " + weaponName;
            message += " :"+ std::to_string(activeWeapon->getLastDamage());
            messages.push_back(message);
            notifyConsoleOutputUpdate(messages);
            notifyStats();
        }
    return earnedXp;
}

int PlayableCharacter::receiveDamage(int attackerLvl, int damage) {
    if(inCity) return 0;
    return lifeState->modifyLifePointsFrom(this,attackerLvl,damage);
}

int PlayableCharacter::modifyLifePoints(int attackerLvl, int damage) {
    int xpEarned = 0;
    std::vector<std::string> messages;

    if (dodge()) {
        std::string message = "Ataque esquivado";
        messages.push_back(message);
        notifyConsoleOutputUpdate(messages);
        return ATAQUE_ESQUIVADO;
    }

    damage = defend(damage);
    std::string message = "Danio recibido: " + std::to_string(damage);
    messages.push_back(message);
    notifyConsoleOutputUpdate(messages);

    float newLife = lifePoints - damage;
    xpEarned = calculateAttackXp(damage, attackerLvl);

    if (newLife <= 0) {
        die();
        //int maxLifePoints = (int)calculateMaxLife();
        xpEarned += calculateKillXp(attackerLvl);
    } else {
        lifePoints = newLife;
    }

    notifyStats();
    return xpEarned;
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
    if (activeWeapon != &defaultWeapon) activeWeapon->unequipFrom(this);
    activeWeapon = weapon;
    notifyEquipment();
}

void PlayableCharacter::equip(Protection* protection, int index) {
    armour.equipTo(protection, this);
    notifyEquipment();
}

void PlayableCharacter::equip(Potion* potion, int index) {
    potion->use(this);
    Equippable* element = inventory.takeElement(index, this);
    delete element;
    inventory.sendItems(observer);
}

void PlayableCharacter::equip(std::string itemName) {
    int index = inventory.getItemIndex(itemName);
    equip(index);
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

void PlayableCharacter::earnMana(float value) {
    float maxMana = calculateMaxMana();
    lifeState->earnMana(maxMana,mana, value);
}

bool PlayableCharacter::checkFairPlay(int enemyLevel) {
    int levelDifference = abs(enemyLevel - level);
    if(levelDifference > config.constants["levelDifference"]) return false;
    bool enemyisnewbie = (enemyLevel <= config.constants["newbieLevel"]);
    bool imnewbie = (level <= config.constants["newbieLevel"]);
    return (imnewbie && enemyisnewbie);
}

void PlayableCharacter::die() {
    //Dropeo el oro en exceso
    int safeGold = calculateSafeGoldCapacity(level);
    if (gold > safeGold) {
        int amountGoldDrop = gold - safeGold;
        gold -= amountGoldDrop;
        auto* goldBag = new GoldBag(amountGoldDrop);
        Position pos = getClosestPositionToDrop();
        Drop drop(pos, goldBag, "goldBag");
        map->addDrop(drop);
    }

    //Desequipo todos los items que tengo
    activeWeapon->unequipFrom(this);
    armour.unequipEveryProtectionFrom(this);
    notifyEquipment();

    //Dropeo mi inventario completo
    dropWholeInventory();

    delete lifeState;
    lifeState = new Ghost();
    lifePoints = 0;
    mana = 0;

    //Envio al cliente los drops a renderizar
    map->updateDropSpawns(observer);
    //LO COMENTO HASTA ASEGURARME DE QUE ESTEN LOS SPRITES DEL GHOST
    observer->notifyEquipmentUpdate(id,"none", "ghost", "none", "none");
}

void PlayableCharacter::dropWholeInventory() {
    int itemsInInventory = inventory.getItemsAmount();
    for (int i = 0; i < itemsInInventory ; ++i) {
        Equippable* equippable = inventory.takeElement(0, this);
        Position pos = getClosestPositionToDrop();
        Drop drop(pos, equippable, equippable->getName());
        map->addDrop(drop);
    }
    //hago que se actualice el inventario en el cliente
    inventory.sendItems(observer);
}

void PlayableCharacter::dropItem(int itemIndex) {
    Equippable* equippable = inventory.takeElement(itemIndex, this);
    Position pos = getClosestPositionToDrop();
    Drop drop(pos, equippable, equippable->getName());
    map->addDrop(drop);
    map->updateDropSpawns(observer);
    inventory.sendItems(observer);
}


void PlayableCharacter::sellTo(std::string itemName, Merchant *merchant) {
    if (!inCity) return;
    int earnedGold = merchant->buy(itemName);
    Equippable* item = inventory.takeElement(itemName, this);
    if (earnedGold != 0 && item) {
        addGold(earnedGold);
        delete item;
        inventory.sendItems(observer);
    }
}

void PlayableCharacter::buyFrom(const std::string& itemName, ItemSeller *seller) {
    if (!inCity) return;
    Equippable* item = seller->sell(itemName, &gold);
    if (item != nullptr) {
        inventory.store(item);
        inventory.sendItems(observer);
        notifyStats();
    }
}

void PlayableCharacter::revive() {
    LifeState* oldLifeState = lifeState;
    lifeState = lifeState->revive(this);
    if (lifeState) {
        delete oldLifeState;
    } else {
        lifeState = oldLifeState;
    }
}

void PlayableCharacter::deposit(const std::string& element, Banker* banker) {
    if(!inCity) return;
    Equippable *equippable = inventory.takeElement(element,this);
    banker->deposit(&bankAccount, equippable);
    inventory.sendItems(observer);
}

void PlayableCharacter::deposit(int amount, Banker* banker) {
    if(!inCity) return;
    banker->deposit(&bankAccount, amount,gold);
    notifyStats();
}

void PlayableCharacter::extract(const std::string& itemName, Banker *banker) {
    if (!inCity) return;
    Equippable* itemExtracted = banker->extract(&bankAccount, itemName);
    if (itemExtracted != nullptr) {
        inventory.store(itemExtracted);
        inventory.sendItems(observer);
    }
}

void PlayableCharacter::extract(int amount, Banker *banker) {
    if (!inCity) return;
    addGold(banker->extract(&bankAccount, amount));

}

void PlayableCharacter::restoreMana() {
    mana = calculateMaxMana();
}


PlayableCharacter* PlayableCharacter::closestToInRange(const Position &pos,
        PlayableCharacter *closestEnemy, int *minDistance, int range) {
    return lifeState->closestToInRange(pos, closestEnemy, minDistance, range, this);
}

void PlayableCharacter::healedByPriest() {
    if (!inCity) return;
    lifeState->healedByPriest(this);
}

void PlayableCharacter::addGold(int amount) {
    int maxGoldAmount = calculateGoldCapacity();
    if (gold + amount > maxGoldAmount) {
        gold = maxGoldAmount;
    } else {
        gold += amount;
    }
    notifyStats();
}

void PlayableCharacter::takeDroppable(GoldBag* goldBag) {
    addGold(goldBag->getAmount());
    delete goldBag;
    map->updateDropSpawns(observer);
}

void PlayableCharacter::takeDroppable(Equippable* equippable) {
    store(equippable);
    map->updateDropSpawns(observer);
}

void PlayableCharacter::takeDrop() {
    if (!inventory.isFull()) lifeState->takeDrop(map, currPos, this);
}

bool PlayableCharacter::isInCity() const {
    return inCity;
}


void PlayableCharacter::sendItemsInBankList() {
    bankAccount.sendItemsList(this);
}

void PlayableCharacter::notifyConsoleOutputUpdate(std::vector<std::string> messages) {
    observer->notifyConsoleOutputUpdate(id,messages);
}

void PlayableCharacter::addSpawnInfoTo(std::vector<spawn_playable_character_t> &pcSpawns) {
    std::vector<std::string> protectionNames;
    armour.getNames(protectionNames);
    std::string race = getRaceName();
    spawn_playable_character_t  spawn = {currPos.getX(), currPos.getY(), id, race,
         activeWeapon->getName(), protectionNames[0], protectionNames[1]
         , protectionNames[2]};
    pcSpawns.push_back(spawn);
}

std::string PlayableCharacter::getRaceName() {
    if (raceId == 1) return "human";
    if (raceId == 2) return "elf";
    if (raceId == 3) return "dwarf";
    return "gnome";
}

bool PlayableCharacter::hasEquipped(Equippable *item) {
    return item == activeWeapon || armour.has(item);
}

void PlayableCharacter::receivePrivateMessageFrom(std::string sender, std::string message) {
    std::string finalMessage = "Mensaje recibido de " + sender + " : " + message;
    std::vector<std::string> messages;
    messages.push_back(finalMessage);
    notifyConsoleOutputUpdate(messages);
}

void PlayableCharacter::recoverManaMeditating(float seconds) {
    meditationState->playerMeditatedFor(this, seconds);
}

void PlayableCharacter::meditatedFor(float seconds) {
    float manaRecovered = calculateRecoverManaMeditating(seconds);
    earnMana(manaRecovered);
}

void PlayableCharacter::meditate() {
    delete meditationState;
    meditationState = new Meditating();
    std::vector<std::string> messages;
    std::string message = "Meditando, no realices ninguna accion!";
    messages.push_back(message);
    notifyConsoleOutputUpdate(messages);
}

void PlayableCharacter::stopMeditating() {
    delete meditationState;
    meditationState = new NotMeditating();
}

PlayableCharacter::~PlayableCharacter() {
    delete lifeState;
    delete meditationState;
    if (activeWeapon != &defaultWeapon) delete activeWeapon;
}
