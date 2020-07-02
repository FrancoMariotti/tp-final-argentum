#include <jsoncpp/json/json.h>
#include <iostream>
#include <Servidor/Common/Utils.h>
#include <Proxy/src/common_message_structs.h>
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

MapFactory::MapFactory(const std::string& configFile) {
    file = configFile;
    FileParser parser(configFile);
    mapObj = parser.read("map");
}

Map* MapFactory::create() {
    int width_map = mapObj["width"].asInt();
    int height_map = mapObj["height"].asInt();

    Map *map = new Map(file,width_map, height_map);
    Json::Value& obstacles = mapObj["obstacles"];
    Json::Value& cities = mapObj["cities"];

    for (auto & i : obstacles){
        int width = i["width"].asInt()/32;
        int height = i["height"].asInt()/32;
        int x = i["x"].asInt()/32;
        int y = i["y"].asInt()/32;
        Obstacle obstacle(x,y,height,width);
        map->addObstacle(obstacle);
    }

    for (auto & i : cities) {
        int width = i["width"].asInt();
        int height = i["height"].asInt();
        int x = i["x"].asInt();
        int y = i["y"].asInt();
        City city(x,y,height,width);
        map->addCity(city);
    }

    return map;
}

MapFactory::~MapFactory() =default;


PlayableCharacterFactory::PlayableCharacterFactory(const std::string& configFile) {
    FileParser parser(configFile);
    characterObj = parser.read("character");
}

void PlayableCharacterFactory::create(Map *map, const std::string &playerName, const std::string &charRace,
                                      const std::string &charClass, Observer* observer) {
    Log* log = Log::instancia();

    log->write("Creacion de Jugador:" + playerName);

    //Position initialPosition = map->asignPosition();
    Position initialPosition(1,2);

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
            meditationRecoveryFactor, invMaxElements,observer);
    map->addPlayableCharacter(playerName,character);
}

PlayableCharacterFactory::~PlayableCharacterFactory() = default;

NpcFactory::NpcFactory(const std::string& configFile) {
    this->counter = 1;
    FileParser parser(configFile);
    npcsObj = parser.read("npc");
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

    Position initialPosition = map->asignRandomPosition();
    std::string id = specie + std::to_string(counter);
    counter++;

    Npc *enemy = new Npc(id,map, initialPosition, constitution,
            strengh, agility, intelligence, level, specie, minDamage,
            maxDamage, minDefense, maxDefense,raceLifeFactor,classLifeFactor,raceManaFactor,classManaFactor,
            recoveryFactor,meditationRecoveryFactor,observer);

    spawn_character_t  spawn = {initialPosition.getX(),initialPosition.getY(),id};
    map->registerNpcSpawn(observer,spawn);
    map->addNpc(id,enemy);
}

NpcFactory::~NpcFactory() = default;

Equippable* NormalWeaponFactory::create(Json::Value itemObj) {
    return new NormalWeapon(itemObj.asString(), itemObj["min"].asInt(),
            itemObj["max"].asInt(), itemObj["goldCost"].asInt());
}

Equippable* RangeWeaponFactory::create(Json::Value itemObj) {
    return new RangeWeapon(itemObj.asString(), itemObj["min"].asInt(),
            itemObj["max"].asInt(), itemObj["goldCost"].asInt());
}

Equippable* ProtectionFactory::create(Json::Value itemObj) {
    return new Protection(itemObj.asString(), itemObj["min"].asInt(),
            itemObj["max"].asInt(), itemObj["id"].asInt(),
            itemObj["goldCost"].asInt());
}

Equippable* LifePotionFactory::create(Json::Value itemObj) {
    return new LifePotion(itemObj.asString(), itemObj["value"].asInt(),
            itemObj["goldCost"].asInt());
}

Equippable* ManaPotionFactory::create(Json::Value itemObj) {
    return new ManaPotion(itemObj.asString(), itemObj["value"].asInt(),
            itemObj["goldCost"].asInt());
}

Equippable* MagicalWeaponFactory::create(Json::Value itemObj) {
    SpellType* spellType = NULL;
    if (itemObj["spellType"].asString() == "heal") {
        spellType = new Heal();
    } else {
        spellType = new Damage();
    }
    return new MagicalWeapon(itemObj.asString(), spellType, itemObj["min"].asInt(),
            itemObj["max"].asInt(), itemObj["manaCost"].asInt(),
            itemObj["goldCost"].asInt());
}