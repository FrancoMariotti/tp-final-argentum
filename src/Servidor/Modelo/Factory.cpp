#include <jsoncpp/json/json.h>
#include "Factory.h"
#include "utility"

FileParser::FileParser(std::string filename):file(filename){}

Json::Value FileParser::leer(std::string parametro) {
    Json::Reader reader;
    Json::Value obj;
    reader.parse(this->file, obj);
    return std::move(obj[parametro]);
}


MapaFactory::MapaFactory(std::string mapaFile):parser(mapaFile) {}

Mapa MapaFactory::create() {
    Json::Value obj = parser.leer("mapa");
    int ancho = obj["ancho"].asInt();
    int alto = obj["alto"].asInt();
    Mapa mapa(ancho,alto);
    return mapa;
}

MapaFactory::~MapaFactory() {}