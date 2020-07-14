#ifndef ARGENTUM_FACTORY_H
#define ARGENTUM_FACTORY_H

#include <fstream>
#include <jsoncpp/json/value.h>
#include "string"
#include "Observer.h"
#include "NormalWeapon.h"
#include "Merchant.h"

class Game;
class Map;
class ItemFactory;

#define CHARACTER_INFO_INTS_AMOUNT 45

typedef struct character_info {
   //std::string id;
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

typedef struct character_map_info {
    //int stringLen;
    std::string name;
    uint32_t index;
} character_map_info_t;

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
    std::map<std::string, int> playersInfoMap;
    uint32_t playersAmount;
    public:
        explicit PlayableCharacterFactory(const std::string &configFile, ItemFactory *pFactory,
                std::string  playersInfoMapFile, std::string  playersInfoFile);
        void create(Map* map,const std::string& playerName,const std::string& charRace,
                const std::string& charClass, Observer* observer);
        ~PlayableCharacterFactory();

    void addPlayerInfoToFile(character_info_t playerInfo, int index);

    character_info_t getPlayerInfoFromFile(int index);

    void createPlayerFromInfo(character_info_t info, std::string playerName, Map* map, Observer* observer);
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
