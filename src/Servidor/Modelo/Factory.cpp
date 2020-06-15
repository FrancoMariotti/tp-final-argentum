#include <jsoncpp/json/json.h>
#include <iostream>
#include "Factory.h"
#include "utility"

FileParser::FileParser(std::string filename):file(filename){}

Json::Value FileParser::read(std::string parameter) {
    Json::Reader reader;
    Json::Value obj;
    reader.parse(this->file, obj);
    return std::move(obj[parameter]);
}


MapFactory::MapFactory(std::string mapFile):parser(mapFile) {}

Map MapFactory::create() {
    Json::Value obj = parser.read("map");
    int width_map = obj["width"].asInt();
    int height_map = obj["height"].asInt();
    Map map(width_map,height_map);
    Json::Value& obstacles = obj["obstacles"];// array of characters

    for (unsigned int i = 0; i < obstacles.size(); i++){
        int width = obstacles[i]["width"].asInt()/32;
        int height = obstacles[i]["height"].asInt()/32;
        int x = obstacles[i]["x"].asInt() / 32;
        int y = obstacles[i]["y"].asInt() / 32;
        Obstacle* obstacle = new Obstacle(x,y,height,width);
        map.addObstacle(obstacle);
    }

    return map;
}

MapFactory::~MapFactory() {}