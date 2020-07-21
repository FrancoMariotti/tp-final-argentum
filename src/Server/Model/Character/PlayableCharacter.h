#ifndef ARGENTUM_PLAYABLECHARACTER_H
#define ARGENTUM_PLAYABLECHARACTER_H

#include <Common/Messages/message_structs.h>
#include "Server/Model/Character/Character.h"
#include "Server/Model/Equippables/Weapon.h"
#include "Server/Model/Equippables/NormalWeapon.h"
#include "Server/Model/Character/Inventory.h"
#include "Server/Model/Character/Armour.h"
#include "Server/Model/Map/Position.h"
#include "Merchant.h"
#include "Banker.h"
#include "Server/Model/Character/MeditationState.h"

class LifeState;
class Game;
class Potion;
class GoldBag;

class PlayableCharacter: public Character {
    friend class PersonajeTest;
    friend class Priest;
    friend class PlayableCharacterFactory;
    friend class PersistanceManager;
    float mana;
    int gold;
    int xp;
    float updateTime;
    Weapon* activeWeapon;
    NormalWeapon defaultWeapon;
    Configuration& config;
    Inventory inventory;
    Armour armour;
    LifeState *lifeState;
    bool inCity;
    BankAccount bankAccount;
    int raceId;
    MeditationState* meditationState;
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
    //Calcula el danio total a partir del nivel y danio recibido y lo descuenta
    //de la vida del personaje.
    //Devuelve la experiencia obtenida por el ataque realizado.
    int receiveDamage(int attackerLvl, int damage) override;
    void attack(Character *character) override;
    void move(Offset& offset);
    //Equipa el elemento en el indice (param:elementIndex) del inventario.
    void equip(int elementIndex);
    void equip(Equippable* element, int index);
    void equip(Weapon* weapon, int index);
    void equip(Protection* protection, int index);
    void equip(Potion* potion, int index);
    //Des equipa el elemento en el indice (param:elementIndex) del inventario.
    void unequip(int elementIndex);
    void unequip(Equippable* element);
    void unequip(Protection *protection);
    void unequip(Weapon *weapon);
    //Guarda un equipable en el inventario si hay espacio en el mismo.
    void store(Equippable* element);
    //Recupera puntos de vida del personaje a partir de los segundo de
    // gameloop transcurridos.
    void recoverLifePoints(float seconds);
    void recoverMana(float seconds);
    void heal(int value);
    void earnMana(float value);
    //Genera una notificacion de los stats del personaje.
    void notifyStats();
    //Genera una notificacion del equipment del personaje.
    void notifyEquipment();
    void makeDamageTo(Character *character);
    int attackTo(PlayableCharacter *enemy);
    int attackTo(Npc *enemy);
    int receiveAttackFrom(PlayableCharacter *enemy) override;
    int defend(int damage);
    int modifyLifePoints(int attackerLvl, int damage);
    void sellTo(std::string itemName, Merchant* merchant);
    void buyFrom(const std::string& itemName, ItemSeller* seller);
    void deposit(const std::string& element, Banker *banker);
    void deposit(int amount, Banker* banker);
    void extract(const std::string& itemName, Banker *banker);
    void extract(int amount, Banker* banker);
    void die();
    void restoreMana();
    //Busca el Playable Character mas cercano a la posicion recibida en el rango recibido.
    PlayableCharacter* closestToInRange(const Position &pos, PlayableCharacter *closestEnemy,
                                        int *minDistance, int range);
    void healedByPriest();
    void takeDroppable(GoldBag *goldBag, Position& position);
    void takeDroppable(Equippable* equippable, Position& position);
    bool isInCity() const;
    void takeDrop();
    void dropItem(int itemIndex);
    void notifyConsoleOutputUpdate(std::vector<std::string> messages);
    void addSpawnInfoTo(std::vector<spawn_playable_character_t> &pcSpawns);
    void sendItemsInBankList();
    bool hasEquipped(Equippable *item);
    void receivePrivateMessageFrom(std::string sender, std::string message);
    void recoverManaMeditating(float seconds);
    void meditatedFor(float seconds);
    void meditate();
    void stopMeditating();
    ~PlayableCharacter() override;
};


#endif //ARGENTUM_PLAYABLECHARACTER_H
