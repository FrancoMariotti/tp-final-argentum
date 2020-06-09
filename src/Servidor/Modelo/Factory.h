#ifndef ARGENTUM_FACTORY_H
#define ARGENTUM_FACTORY_H


#include <fstream>
#include <jsoncpp/json/value.h>
#include "Mapa.h"
#include "string"

class FileParser {
    std::ifstream file;
    public:
        FileParser(std::string filename);
        Json::Value leer(std::string parametro);

};

class MapaFactory {
    FileParser parser;
    public:
        MapaFactory(std::string mapaFile);
        Mapa create();
        ~MapaFactory();
};


#endif //ARGENTUM_FACTORY_H
