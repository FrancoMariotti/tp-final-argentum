#include <jsoncpp/json/json.h>
#include <iostream>
#include "Game.h"
#include "Factory.h"
#include "PlayableCharacter.h"

FileParser::FileParser(const std::string& filename):file(filename){}

Json::Value FileParser::read(const std::string& parameter) {
    Json::Reader reader;
    Json::Value obj;
    reader.parse(this->file, obj);
    return std::move(obj[parameter]);
}


MapFactory::MapFactory(const std::string& mapFile):parser(mapFile) {}

Map MapFactory::create() {
    Json::Value obj = parser.read("map");
    int width_map = obj["width"].asInt();
    int height_map = obj["height"].asInt();
    Map map(width_map,height_map);
    Json::Value& obstacles = obj["obstacles"];// array of characters

    for (auto & i : obstacles){
        int width = i["width"].asInt()/32;
        int height = i["height"].asInt()/32;
        int x = i["x"].asInt() / 32;
        int y = i["y"].asInt() / 32;
        auto* obstacle = new Obstacle(x,y,height,width);
        map.addObstacle(obstacle);
    }

    return map;
}

MapFactory::~MapFactory() = default;


PlayableCharacterFactory::PlayableCharacterFactory(std::string personajesFile,Map& map):parser(personajesFile),map(map) {}

PlayableCharacter PlayableCharacterFactory::create() {
    Json::Value obj = parser.read("character");

    int life = 100;
    int x = 1;
    int y = 1;
    int strength = obj["strength"].asInt();
    int agility = obj["agility"].asInt();
    int intelligence = obj["intelligence"].asInt();
    int constitution = obj["constitution"].asInt();

    return PlayableCharacter(life,x,y,map,constitution,strength,agility,intelligence);
}

PlayableCharacterFactory::~PlayableCharacterFactory() = default;