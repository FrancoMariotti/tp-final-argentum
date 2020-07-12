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

typedef struct character_info {
   std::string id;
   float lifePoints;
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
   float mana;
   int gold;
   int xp;
   std::string activeWeapon;
   std::vector<std::string> inventoryItems;
   std::vector<std::string> protections;
   std::string lifeState;
   bool inCity;
   int goldInBank;
   std::vector<std::string> itemsInBank;
   std::string race;
} character_info_t;

typedef struct item {
    std::string name;
    std::string type;
    std::string spelltype;
    int protectionId;
    int max;
    int min;
    int value;
    int goldCost;
    int manaCost;
} item_t;

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
    std::map<std::string, item_t> items;
    std::fstream playersInfoFile;
    std::fstream playersInfoMapFile;
    std::map<std::string, int> playersInfoMap;
    int playersAmount;
    public:
        explicit PlayableCharacterFactory(const std::string &configFile, ItemFactory *pFactory,
                const std::string& playersInfoMapFile, const std::string& playersInfoFile);
        void create(Map* map,const std::string& playerName,const std::string& charRace,
                const std::string& charClass, Observer* observer);
        ~PlayableCharacterFactory();
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
