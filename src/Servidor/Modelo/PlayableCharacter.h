#ifndef ARGENTUM_PLAYABLECHARACTER_H
#define ARGENTUM_PLAYABLECHARACTER_H

#include <Common/message_structs.h>
#include "Character.h"
#include "Weapon.h"
#include "NormalWeapon.h"
#include "Inventory.h"
#include "Armour.h"
#include "Position.h"
#include "Merchant.h"
#include "Banker.h"

class LifeState;
class Game;
class Potion;
class GoldBag;


class PlayableCharacter: public Character {
    friend class PersonajeTest;
    friend class Priest;
    friend class PlayableCharacterFactory;
    float mana;
    int gold;
    int xp;
    Weapon* activeWeapon;
    NormalWeapon defaultWeapon;
    Inventory inventory;
    Armour armour;
    LifeState *lifeState;
    bool inCity;
    BankAccount bankAccount;
    int raceId;
private:
    bool checkFairPlay(int enemyLevel);
    void revive();
    void teleportTo(Position position);
    void addGold(int amount);
    void dropWholeInventory();
    PlayableCharacter(std::string id, float lifePoints, Map* map, Position &initialPosition, int constitution,
            int strength,int agility,int intelligence,int level, int raceLifeFactor, int classLifeFactor,
            int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor,
            Observer* observer, int raceId, float mana, int gold,
            int xp, int lifeState, bool inCity);
    void equip(std::string itemName);
    std::string getRaceName();
public:
    PlayableCharacter(std::string id,Map* map, Position &initialPosition, int constitution,
                          int strength,int agility,int intelligence,int level, int raceLifeFactor, int classLifeFactor,
                  int raceManaFactor, int classManaFactor, int recoveryFactor, int meditationRecoveryFactor,
                  int invMaxElements,Observer* observer, int raceId);
    int receiveDamage(int enemyLevel, int damage) override;
    void attack(Character *character) override;
    void move(Offset& offset);
    void equip(int elementIndex);
    void equip(Equippable* element, int index);
    void equip(Weapon* weapon, int index);
    void equip(Protection* protection, int index);
    void equip(Potion* potion, int index);
    void unequip(int elementIndex);
    void unequip(Equippable* element);
    void unequip(Protection *protection);
    void unequip(Weapon *weapon);
    void store(Equippable* element);
    void recoverLifePoints(float seconds);
    void recoverMana(float seconds);
    void heal(int value);
    void earnMana(int value);
    void notifyStats();
    void notifyEquipment();
    void notifySpawn();
    void makeDamageTo(Character *character);
    int attackTo(PlayableCharacter *enemy);
    int attackTo(Npc *enemy);
    int receiveAttackFrom(PlayableCharacter *enemy) override;
    int defend(int damage);
    int modifyLifePoints(int enemyLevel, int damage);
    void sellTo(std::string itemName, Merchant* merchant);
    void buyFrom(const std::string& itemName, ItemSeller* seller);
    void deposit(const std::string& element, Banker *banker);
    void deposit(int amount, Banker* banker);
    void extract(const std::string& itemName, Banker *banker);
    void extract(int amount, Banker* banker);
    void die();
    void restoreMana();
    PlayableCharacter* closestToInRange(const Position &pos, PlayableCharacter *closestEnemy,
                                        int *minDistance, int range);

    void healedByPriest();
    void takeDroppable(GoldBag *goldBag);
    void takeDroppable(Equippable* equippable);
    bool isInCity() const;
    void takeDrop();
    void dropItem(int itemIndex);
    ~PlayableCharacter() override;

    void sendItemsInBankList();

    void notifyConsoleOutputUpdate(std::vector<std::string> messages);

    void addSpawnInfoTo(std::vector<spawn_playable_character_t> &pcSpawns);

};


#endif //ARGENTUM_PLAYABLECHARACTER_H
