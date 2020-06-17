#ifndef ARGENTUM_FACTORY_H
#define ARGENTUM_FACTORY_H

#include <fstream>
#include <jsoncpp/json/value.h>
#include "Map.h"
#include "string"

class FileParser {
    std::ifstream file;
    public:
        explicit FileParser(const std::string& filename);
        Json::Value read(const std::string& parameter);

};

class MapFactory {
    FileParser parser;
    public:
        explicit MapFactory(const std::string& mapFile);
        Map create();
        ~MapFactory();
};

/*class PersonajeFactory {
    FileParser parser;
public:
    PersonajeFactory(std::string personajesFile);
    std::vector<Personaje> create();
    ~PersonajeFactory();
};*/


#endif //ARGENTUM_FACTORY_H
