#ifndef ARGENTUM_FACTORY_H
#define ARGENTUM_FACTORY_H

#include <fstream>
#include <jsoncpp/json/value.h>
#include "string"
#include "Observer.h"
#include "Servidor/Modelo/Equippables/NormalWeapon.h"
#include "Servidor/Modelo/Character/Merchant.h"

class Game;
class Map;
class ItemFactory;
class Configuration;

#define CHARACTER_INFO_INTS_AMOUNT 45

typedef struct character_info {
   int lifePoints;
   int level;
   int constitution;
   int agility;
   int strength;
   int intelligence;
   int raceLifeFactor;
   int classLifeFactor;
   int raceManaFactor;
   int classManaFactor;
   int recoveryFactor;
   int meditationRecoveryFactor;
   int x;
   int y;
   int mana;
   int gold;
   int xp;
   std::vector<int> inventoryItems;
   int activeWeapon;
   std::vector<int> protections;
   int lifeState;
   int inCity;
   int goldInBank;
   std::vector<int> itemsInBank;
   int race;
} character_info_t;

typedef struct item {
    std::string name;
    std::string type;
    std::string spelltype;
    int id;
    int protectionId;
    int max;
    int min;
    int value;
    int goldCost;
    int manaCost;
} item_t;

typedef struct login_info {
    //int stringLen;
    std::string password;
    int index;
} login_info_t;

class FileParser {
    std::ifstream file;
public:
    explicit FileParser(const std::string &filename);
    Json::Value read(const std::string& parameter);

};

class MapFactory {
    std::string file;
    Json::Value mapObj;
    public:
        explicit MapFactory(const std::string& configFile);
        Map *create(ItemFactory *pFactory);
        ~MapFactory();
};

class MerchantFactory {
public:
    MerchantFactory() = default;
    void create(Map *map, std::string file, ItemFactory *pFactory);
    ~MerchantFactory() = default;
};

class PriestFactory {
public:
    PriestFactory() = default;
    void create(Map *map, std::string file, ItemFactory *pFactory);
    ~PriestFactory() = default;
};

class BankerFactory {
public:
    BankerFactory() = default;
    void create(Map* map, std::string file);
    ~BankerFactory() = default;
};

class PlayableCharacterFactory {
    Json::Value characterObj;
    ItemFactory* itemFactory;
    std::map<int, item_t> items;
    std::string playersInfoFile;
    std::string playersInfoMapFile;
    std::map<std::string, login_info_t> playersInfoMap;
    int playersAmount;
    Configuration& config;
    void addPlayerInfoToFile(character_info_t playerInfo, int index);
    character_info_t getPlayerInfoFromFile(int index);
    void createPlayerFromInfo(character_info_t info, std::string playerName, Map* map, Observer* observer);
    public:
        explicit PlayableCharacterFactory(const std::string &configFile, ItemFactory *pFactory,
                std::string  playersInfoMapFile, std::string  playersInfoFile);
        void create(Map* map,const std::string& playerName,const std::string& charRace,
                const std::string& charClass, Observer* observer);

        void persistPlayerData(PlayableCharacter *pCharacter);
        bool login(const std::string &playerName, std::string &password, Map* map, Observer* observer);
        ~PlayableCharacterFactory() = default;

    bool signup(const std::string &username, const std::string &password);
};

class NpcFactory {
    int counter;
    Json::Value npcsObj;
    ItemFactory* itemFactory;
    std::map<int, item_t> itemsToDrop;
    public:
        explicit NpcFactory(const std::string &configFile, ItemFactory *pFactory);
        void create(Map* map,const std::string& specie,Observer* observer);
        ~NpcFactory();
};

class EquippableFactory {
public:
    virtual Equippable* create(item_t item)= 0;
    virtual ~EquippableFactory() = default;
};

class NormalWeaponFactory : public EquippableFactory {
public:
    Equippable* create(item_t item) override;
};

class RangeWeaponFactory : public EquippableFactory{
public:
    Equippable* create(item_t item) override;
};

class ProtectionFactory : public EquippableFactory {
public:
    Equippable* create(item_t item) override;
};

class LifePotionFactory : public EquippableFactory {
public:
    Equippable* create(item_t item) override;
};

class ManaPotionFactory : public EquippableFactory {
public:
    Equippable* create(item_t item) override;
};

class MagicalWeaponFactory : public EquippableFactory {
public:
    Equippable* create(item_t item) override;
};

class ItemFactory {
    std::map<std::string, EquippableFactory*> factories;
public:
    ItemFactory();
    Equippable* create(item_t item);
    ~ItemFactory();
};
#endif //ARGENTUM_FACTORY_H
