#include <jsoncpp/json/json.h>
#include <iostream>
#include <utility>
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
}

Map* MapFactory::create() {

    FileParser parser(file);
    mapObj = parser.read("map");

    int width_map = mapObj["width"].asInt();
    int height_map = mapObj["height"].asInt();

    Map *map = new Map(file,width_map, height_map);
    Json::Value& obstacles = mapObj["obstacles"];
    Json::Value& cities = mapObj["cities"];

    Json::Value priestItems = mapObj["priestItems"];
    Json::Value merchantItems = mapObj["merchantItems"];

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

        //Voy creando los city characters y agregandolos al vector de spawns para luego mandarle al
        //cliente y que los renderice correctamente
        std::vector<spawn_character_t> cityCharacters;
        Position priestPos(i["Priest"]["x"].asInt(), i["Priest"]["y"].asInt());
        spawn_character_t  priestSpawn = {priestPos.getX(),priestPos.getY(),"priest"};
        cityCharacters.push_back(priestSpawn);
        Position merchantPos(i["Merchant"]["x"].asInt(), i["Merchant"]["y"].asInt());
        spawn_character_t  merchantSpawn = {merchantPos.getX(),merchantPos.getY(),"merchant"};
        cityCharacters.push_back(merchantSpawn);
        Position bankerPos(i["Banker"]["x"].asInt(), i["Banker"]["y"].asInt());
        spawn_character_t  bankerSpawn = {bankerPos.getX(),bankerPos.getY(),"banker"};
        cityCharacters.push_back(bankerSpawn);

        map->registerCityCharactersSpawns(cityCharacters);

        City city(x,y,height,width,file,priestItems,priestPos, merchantItems,merchantPos, bankerPos);
        map->add(std::move(city));
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
    map->add(playerName,character);
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

    //Le asigno al npc una posicion que no este dentro de una ciudad
    Position initialPosition = map->asignRandomPosition();
    while (map->posInCity(initialPosition)) initialPosition = map->asignRandomPosition();

    std::string id = specie + std::to_string(counter);
    counter++;

    Npc *enemy = new Npc(id,map, initialPosition, constitution,
            strengh, agility, intelligence, level, specie, minDamage,
            maxDamage, minDefense, maxDefense,raceLifeFactor,classLifeFactor,raceManaFactor,classManaFactor,
            recoveryFactor,meditationRecoveryFactor,observer);

    spawn_character_t  spawn = {initialPosition.getX(),initialPosition.getY(),id};
    map->registerNpcSpawn(observer,spawn);
    map->add(id,enemy);
}

NpcFactory::~NpcFactory() = default;

Equippable* NormalWeaponFactory::create(std::string configFile,std::string itemName,int cost) {
    FileParser parser(configFile);
    Json::Value weaponsData = parser.read("weapons");
    int max = weaponsData[itemName]["max"].asInt();
    int min = weaponsData[itemName]["min"].asInt();
    return new NormalWeapon(itemName, min,max, cost);
}

Equippable* RangeWeaponFactory::create(std::string configFile,std::string itemName,int cost) {
    FileParser parser(configFile);
    Json::Value weaponsData = parser.read("weapons");
    int max = weaponsData[itemName]["max"].asInt();
    int min = weaponsData[itemName]["min"].asInt();
    return new RangeWeapon(itemName, min,
            max, cost);
}

Equippable* ProtectionFactory::create(std::string configFile,std::string itemName,int cost) {
    FileParser parser(configFile);
    Json::Value weaponsData = parser.read("weapons");
    int max = weaponsData[itemName]["max"].asInt();
    int min = weaponsData[itemName]["min"].asInt();
    int id = weaponsData[itemName]["id"].asInt();
    return new Protection(itemName, min,max, id,cost);
}

Equippable* LifePotionFactory::create(std::string configFile,std::string itemName,int cost) {
    FileParser parser(configFile);
    Json::Value weaponsData = parser.read("weapons");
    int value = weaponsData[itemName]["value"].asInt();
    return new LifePotion(itemName,value,cost);
}

Equippable* ManaPotionFactory::create(std::string configFile,std::string itemName,int cost) {
    FileParser parser(configFile);
    Json::Value weaponsData = parser.read("weapons");
    int value = weaponsData[itemName]["value"].asInt();
    return new ManaPotion(itemName, value,cost);
}

Equippable* MagicalWeaponFactory::create(std::string configFile,std::string itemName,int cost) {
    FileParser parser(configFile);
    Json::Value weaponsData = parser.read("weapons");
    int max = weaponsData[itemName]["max"].asInt();
    int min = weaponsData[itemName]["min"].asInt();
    int manaCost = weaponsData[itemName]["manaCost"].asInt();
    std::string spellType = weaponsData[itemName]["spellType"].asString();
    SpellType* spell = nullptr;
    if (spellType == "heal") {
        spell = new Heal();
    } else {
        spell = new Damage();
    }
    return new MagicalWeapon(itemName,spell,min,max,manaCost,cost);
}


