#include <jsoncpp/json/json.h>
#include <iostream>
#include "Factory.h"
#include "PlayableCharacter.h"
#include "Npc.h"
#include "Log.h"
#include "string"

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
    FileParser parser(configFile);
    mapObj = parser.read("map");
}

Map* MapFactory::create() {
    int width_map = mapObj["width"].asInt();
    int height_map = mapObj["height"].asInt();

    Map *map = new Map(width_map, height_map);
    Json::Value& obstacles = mapObj["obstacles"];// array of characters

    for (auto & i : obstacles){
        int width = i["width"].asInt()/32;
        int height = i["height"].asInt()/32;
        int x = i["x"].asInt()/32;
        int y = i["y"].asInt()/32;
        auto* obstacle = new Obstacle(x,y,height,width);
        map->addObstacle(obstacle);
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

    auto* character =  new PlayableCharacter(map,initialPosition,constitution,strength,agility,intelligence,
            level,raceLifeFactor, classLifeFactor, raceManaFactor, classManaFactor,recoveryFactor,
            meditationRecoveryFactor, invMaxElements);
    character->addObserver(observer);
    character->sendStats();
    map->addPlayableCharacter(playerName,character);
}

PlayableCharacterFactory::~PlayableCharacterFactory() = default;

NpcFactory::NpcFactory(const std::string& configFile) {
    FileParser parser(configFile);
    npcsObj = parser.read("npc");
}

void NpcFactory::create(Map* map,const std::string& specie) {
    int maxLevel = npcsObj["maxLevel"].asInt();
    int minLevel = npcsObj["minLevel"].asInt();
    int level =  std::rand() % (maxLevel - minLevel) + minLevel;

    //Seteo los atributos del NPC
    int constitution = npcsObj["specie"][specie]["constitution"].asInt();
    int strengh = npcsObj["specie"][specie]["strengh"].asInt();
    int agility = npcsObj["specie"][specie]["agility"].asInt();
    int intelligence = npcsObj["specie"][specie]["intelligence"].asInt();
    int minDamage = npcsObj["specie"][specie]["minDamage"].asInt();
    int maxDamage = npcsObj["specie"][specie]["maxDamage"].asInt();
    int minDefense = npcsObj["specie"][specie]["minDefense"].asInt();
    int maxDefense = npcsObj["specie"][specie]["maxDefense"].asInt();
    int raceLifeFactor = npcsObj["lifeFactor"].asInt();
    int raceManaFactor = npcsObj["manaFactor"].asInt();
    int recoveryFactor = npcsObj["recoveryFactor"].asInt();
    int classLifeFactor = npcsObj["lifeFactor"].asInt();
    int classManaFactor = npcsObj["manaFactor"].asInt();
    int meditationRecoveryFactor = npcsObj["meditationRecoveryFactor"].asInt();

    //Position initialPosition = map->asignPosition();
    Position initialPosition(1,1);

    Npc *enemy = new Npc(map, initialPosition, constitution,
            strengh, agility, intelligence, level, specie, minDamage,
            maxDamage, minDefense, maxDefense,raceLifeFactor,classLifeFactor,raceManaFactor,classManaFactor,
            recoveryFactor,meditationRecoveryFactor);

    map->addNpc(enemy);
}

NpcFactory::~NpcFactory() = default;

