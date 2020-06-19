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
    explicit PlayableCharacterFactory(const std::string& personajesFile,Map& map);
    void create(const std::string& playerName,const std::string& charRace, const std::string& charClass);
    ~PlayableCharacterFactory();
};

class NpcFactory {
    FileParser parser;
    Map& map;
public:
    explicit NpcFactory(const std::string& npcsFile,Map& map);
    void create(const std::string& specie);
    ~NpcFactory();
};

#endif //ARGENTUM_FACTORY_H
