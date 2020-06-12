#include <jsoncpp/json/json.h>
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
    int ancho = obj["ancho"].asInt();
    int alto = obj["alto"].asInt();
    Map map(ancho,alto);
    return map;
}

MapFactory::~MapFactory() {}