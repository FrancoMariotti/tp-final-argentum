#include <jsoncpp/json/json.h>
#include <iostream>
#include <utility>
#include <Servidor/Common/Utils.h>
#include <Proxy/src/common_message_structs.h>
#include <Proxy/src/common_osexception.h>
#include "Factory.h"
#include "PlayableCharacter.h"
#include "Npc.h"
#include "Log.h"
#include "string"
#include "Obstacle.h"
#include "RangeWeapon.h"
#include "LifePotion.h"
#include "ManaPotion.h"
#include "MagicalWeapon.h"
#include "Heal.h"
#include "Damage.h"
#include "Merchant.h"


FileParser::FileParser(const std::string &filename):file(filename) {}

Json::Value FileParser::read(const std::string &parameter) {
    Json::Reader reader;
    Json::Value config;
    bool parsingSuccessful = reader.parse(file, config);
    if ( !parsingSuccessful ) {
        // Aca habria que lanzar una excepcion
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
    }
    return config[parameter];
}

void MerchantFactory::create(Map *map, std::string file, ItemFactory *pFactory) {
    FileParser parser(file);
    Json::Value merchantObj = parser.read("merchant");
    Json::Value& merchantPositions = merchantObj["positions"];
    std::vector<Position> positions;

    std::vector<spawn_object_t> spawnsMerchant;
    for (auto& pos: merchantPositions) {
        Position merchantPos(pos["x"].asInt(), pos["y"].asInt());
        spawn_object_t merchantSpawn = {merchantPos.getX(),merchantPos.getY(),"merchant"};
        positions.push_back(merchantPos);
        spawnsMerchant.push_back(merchantSpawn);
    }
    map->registerCityCharactersSpawns(spawnsMerchant);
    Json::Value& merchantItems = merchantObj["items"];

    std::map<std::string, item_t> stock;

    for(auto& item: merchantItems) {
        item_t newItem {
                item["name"].asString(),
                item["type"].asString(),
                item["spelltype"].asString(),
                item["protectionId"].asInt(),
                item["max"].asInt(),
                item["min"].asInt(),
                item["value"].asInt(),
                item["goldCost"].asInt(),
                item["manaCost"].asInt()
        };
        stock[newItem.name] = newItem;
    }

    Merchant merchant(positions,stock,pFactory);

    //map->add(std::move(merchant));
    map->add(merchant);
}

void PriestFactory::create(Map *map, std::string file, ItemFactory *pFactory) {
    FileParser parser(file);
    Json::Value priestObj = parser.read("priest");

    Json::Value& priestPositions = priestObj["positions"];
    std::vector<Position> positions;

    std::vector<spawn_object_t> spawnsPriest;
    for (auto& pos: priestPositions) {
        Position priestPos(pos["x"].asInt(), pos["y"].asInt());
        spawn_object_t  priestSpawn = {priestPos.getX(),priestPos.getY(),"priest"};
        positions.push_back(priestPos);
        spawnsPriest.push_back(priestSpawn);
    }
    map->registerCityCharactersSpawns(spawnsPriest);
    Json::Value& priestItems = priestObj["items"];

    std::map<std::string,item_t> stock;

    /*std::map<std::string, EquippableFactory*> factories;
    factories["MagicalWeapon"] = new MagicalWeaponFactory();
    factories["LifePotion"] = new LifePotionFactory();
    factories["ManaPotion"] = new ManaPotionFactory();*/

    for(auto& item: priestItems) {
        item_t newItem {
                item["name"].asString(),
                item["type"].asString(),
                item["spelltype"].asString(),
                item["protectionId"].asInt(),
                item["max"].asInt(),
                item["min"].asInt(),
                item["value"].asInt(),
                item["goldCost"].asInt(),
                item["manaCost"].asInt()
        };
        stock[newItem.name] = newItem;
    }

    Priest priest(positions,stock,pFactory);

    //map->add(std::move(priest));
    map->add(priest);
}

void BankerFactory::create(Map* map, std::string file) {
    FileParser parser(file);
    Json::Value bankerObj = parser.read("banker");

    Json::Value& bankerPositions = bankerObj["positions"];
    std::vector<Position> positions;

    std::vector<spawn_object_t> spawnsBanker;
    for (auto& pos: bankerPositions) {
        Position bankerPos(pos["x"].asInt(), pos["y"].asInt());
        spawn_object_t  bankerSpawn = {bankerPos.getX(),bankerPos.getY(),"banker"};
        spawnsBanker.push_back(bankerSpawn);
        positions.push_back(bankerPos);
    }
    map->registerCityCharactersSpawns(spawnsBanker);
    Banker banker(positions);

    map->add(std::move(banker));
}



MapFactory::MapFactory(const std::string& configFile) {
    file = configFile;
}

Map * MapFactory::create(ItemFactory *pFactory) {

    FileParser parser(file);
    mapObj = parser.read("map");

    int width_map = mapObj["width"].asInt();
    int height_map = mapObj["height"].asInt();

    Json::Value& obstacles = mapObj["obstacles"];
    Json::Value& cities = mapObj["cities"];

    MerchantFactory merchantFactory;
    BankerFactory bankerFactory;
    PriestFactory priestFactory;


    Map *map = new Map(width_map, height_map);

    merchantFactory.create(map, file, pFactory);
    bankerFactory.create(map,file);
    priestFactory.create(map, file, pFactory);


    for (auto & i : obstacles){
        int width = i["width"].asInt()/32;
        int height = i["height"].asInt()/32;
        int x = i["x"].asInt()/32;
        int y = i["y"].asInt()/32;
        Obstacle obstacle(x,y,height,width);
        map->add(obstacle);
    }

    for (auto & i : cities) {
        int width = i["width"].asInt();
        int height = i["height"].asInt();
        int x = i["x"].asInt();
        int y = i["y"].asInt();

        City city(x,y,height,width);
        map->add(std::move(city));
    }

    return map;
}

MapFactory::~MapFactory() =default;


PlayableCharacterFactory::PlayableCharacterFactory(const std::string &configFile,
        ItemFactory *pFactory, const std::string& playersInfoMapFile,
        const std::string& playersInfoFile) : itemFactory(pFactory),
        playersInfoFile(playersInfoFile, std::fstream::in | std::fstream::out | std::fstream::binary),
        playersInfoMapFile(playersInfoMapFile, std::fstream::in | std::fstream::out | std::fstream::binary)
        , playersAmount(0) {
    FileParser parser(configFile);
    characterObj = parser.read("character");
    //Ahora creo el stock de items
    FileParser itemParser(configFile);
    Json::Value itemsObj = itemParser.read("allItems");

    for(auto& item: itemsObj) {
        item_t newItem {
                item["name"].asString(),
                item["type"].asString(),
                item["spelltype"].asString(),
                item["protectionId"].asInt(),
                item["max"].asInt(),
                item["min"].asInt(),
                item["value"].asInt(),
                item["goldCost"].asInt(),
                item["manaCost"].asInt()
        };
        items[newItem.name] = newItem;
    }

    //Chequeo que los archivos se hayan podido abrir
    if (!this->playersInfoFile || !this->playersInfoMapFile) {
        throw OSError("Error al abrir los archivos binarios de informacion de los jugadores");
    }

    int nameLength, index;
    while (this->playersInfoMapFile.read((char*)&nameLength, sizeof(int))) {
        std::string name;
        this->playersInfoMapFile.read(const_cast<char *>(name.c_str()), nameLength);
        this->playersInfoMapFile.read((char*)&index, sizeof(int));
        playersInfoMap[name] = index;
    }

}

void PlayableCharacterFactory::create(Map *map, const std::string &playerName, const std::string &charRace,
                                      const std::string &charClass, Observer* observer) {

    //TENDRIA QUE AGREGAR LA PARTE DE LA PERSISTENCIA, ES UN JUEGADOR NUEVO O NO?

    Position initialPosition = map->asignRandomPosInAnyCity();

    int invMaxElements = characterObj["inventoryMaxElements"].asInt();
    int level = characterObj["level"].asInt();
    int strength = characterObj["strength"].asInt();
    int agility = characterObj["agility"].asInt();
    int intelligence = characterObj["intelligence"].asInt();
    int constitution = characterObj["constitution"].asInt();
    int raceLifeFactor = characterObj["race"][charRace]["lifeFactor"].asInt();
    int raceManaFactor = characterObj["race"][charRace]["manaFactor"].asInt();
    int recoveryFactor = characterObj["race"][charRace]["recoveryFactor"].asInt();
    int classLifeFactor = characterObj["class"][charClass]["lifeFactor"].asInt();
    int classManaFactor = characterObj["class"][charClass]["manaFactor"].asInt();
    int meditationRecoveryFactor = characterObj["class"][charClass]["meditationRecoveryFactor"].asInt();

    auto* character =  new PlayableCharacter(playerName,map,initialPosition,constitution,strength,agility,intelligence,
            level,raceLifeFactor, classLifeFactor, raceManaFactor, classManaFactor,recoveryFactor,
            meditationRecoveryFactor, invMaxElements,observer, charRace);
    map->add(playerName,character);
}

PlayableCharacterFactory::~PlayableCharacterFactory() = default;

NpcFactory::NpcFactory(const std::string &configFile, ItemFactory *pFactory) {
    this->counter = 1;
    FileParser parser(configFile);
    npcsObj = parser.read("npc");
    //Armo el mapa de objetos que puede dropear el npc
    FileParser itemParser(configFile);
    Json::Value itemsObj = itemParser.read("allItems");
    int itemsToDropIndex = 0;
    for(auto& item : itemsObj) {
        item_t newItem {
                item["name"].asString(),
                item["type"].asString(),
                item["spelltype"].asString(),
                item["protectionId"].asInt(),
                item["max"].asInt(),
                item["min"].asInt(),
                item["value"].asInt(),
                item["goldCost"].asInt(),
                item["manaCost"].asInt()
        };
        itemsToDrop[itemsToDropIndex] = newItem;
        itemsToDropIndex++;
    }
}

void NpcFactory::create(Map* map,const std::string& specie,Observer* observer) {
    int maxLevel = npcsObj["maxLevel"].asInt();
    int minLevel = npcsObj["minLevel"].asInt();

    int level =  Utils::random_int_number(minLevel,maxLevel);

    //Seteo los atributos del NPC
    int constitution = npcsObj["specie"][specie]["constitution"].asInt();
    int strengh = npcsObj["specie"][specie]["strength"].asInt();
    int agility = npcsObj["specie"][specie]["agility"].asInt();
    int intelligence = npcsObj["specie"][specie]["intelligence"].asInt();
    int minDamage = npcsObj["specie"][specie]["minDamage"].asInt();
    int maxDamage = npcsObj["specie"][specie]["maxDamage"].asInt();
    int minDefense = npcsObj["specie"][specie]["minDefense"].asInt();
    int maxDefense = npcsObj["specie"][specie]["maxDefense"].asInt();
    int raceLifeFactor = npcsObj["specie"][specie]["lifeFactor"].asInt();
    int raceManaFactor = npcsObj["specie"][specie]["manaFactor"].asInt();
    int recoveryFactor = npcsObj["specie"][specie]["recoveryFactor"].asInt();
    int classLifeFactor = npcsObj["specie"][specie]["lifeFactor"].asInt();
    int classManaFactor = npcsObj["specie"][specie]["manaFactor"].asInt();
    int meditationRecoveryFactor = npcsObj["specie"][specie]["meditationRecoveryFactor"].asInt();

    //Le asigno al npc una posicion que no este dentro de una ciudad
    Position initialPosition = map->asignRandomPosition();
    while (map->posInCity(initialPosition)) initialPosition = map->asignRandomPosition();

    //Voy llenando los vectores de los items que puede dropear
    /*std::vector<std::string> potionsToDrop, itemsToDrop;
    for (auto &potion : npcsObj["potionsToDrop"]) {
        potionsToDrop.push_back(potion["name"].asString());
    }
    for (auto &item : npcsObj["itemsToDrop"]) {
        itemsToDrop.push_back(item["name"].asString());
    }*/

    std::string id = specie + std::to_string(counter);
    counter++;

    Npc *enemy = new Npc(id, map, initialPosition, constitution, strengh,
            agility, intelligence, level, specie, minDamage, maxDamage,
            minDefense, maxDefense, raceLifeFactor, classLifeFactor,
            raceManaFactor, classManaFactor, recoveryFactor,
            meditationRecoveryFactor, observer, itemFactory,
            itemsToDrop);

    map->add(id,enemy);
}

NpcFactory::~NpcFactory() = default;

Equippable* NormalWeaponFactory::create(item_t item) {
    return new NormalWeapon(item.name, item.min,item.max, item.goldCost);
}

Equippable* RangeWeaponFactory::create(item_t item) {
    return new RangeWeapon(item.name, item.min,item.max, item.goldCost);
}

Equippable* ProtectionFactory::create(item_t item) {
    return new Protection(item.name, item.min,item.max, item.protectionId,item.goldCost);
}

Equippable* LifePotionFactory::create(item_t item) {
    return new LifePotion(item.name,item.value,item.goldCost);
}

Equippable* ManaPotionFactory::create(item_t item) {
    return new ManaPotion(item.name, item.value,item.goldCost);
}

Equippable* MagicalWeaponFactory::create(item_t item) {
    SpellType* spell;
    if (item.spelltype == "Heal") {
        spell = new Heal();
    } else {
        spell = new Damage();
    }
    return new MagicalWeapon(item.name,spell,item.min,item.max,item.manaCost,item.goldCost);
}


ItemFactory::ItemFactory() {
    factories["NormalWeapon"] = new NormalWeaponFactory();
    factories["RangeWeapon"] = new RangeWeaponFactory();
    factories["Protection"] = new ProtectionFactory();
    factories["LifePotion"] = new LifePotionFactory();
    factories["ManaPotion"] = new ManaPotionFactory();
    factories["MagicalWeapon"] = new MagicalWeaponFactory();
}

Equippable* ItemFactory::create(item_t item) {
    return factories.at(item.type)->create(item);
}

ItemFactory::~ItemFactory() {
    auto it = factories.begin();
    for(;it!=factories.end();it++) {
        delete it->second;
    }
}
