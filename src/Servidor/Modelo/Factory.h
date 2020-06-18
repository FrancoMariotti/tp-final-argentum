#ifndef ARGENTUM_FACTORY_H
#define ARGENTUM_FACTORY_H

#include <fstream>
#include <jsoncpp/json/value.h>
#include "Map.h"
#include "string"

class Game;

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

class PlayableCharacterFactory {
    FileParser parser;
    Map& map;
public:
    explicit PlayableCharacterFactory(std::string personajesFile,Map& map);
    PlayableCharacter create();
    ~PlayableCharacterFactory();
};


#endif //ARGENTUM_FACTORY_H
