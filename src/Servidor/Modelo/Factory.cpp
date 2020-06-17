#include <jsoncpp/json/json.h>
#include <iostream>
#include <utility>
#include "Factory.h"
#include "utility"

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