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
    explicit FileParser(const std::string &filename);
    Json::Value read(const std::string& parameter);

};

class MapFactory {
    Json::Value mapObj;
    public:
        explicit MapFactory(const std::string& configFile);
        Map* create();
        ~MapFactory();
};

class PlayableCharacterFactory {
    Json::Value characterObj;
    public:
        explicit PlayableCharacterFactory(const std::string& configFile);
        void create(Map* map,const std::string& playerName,const std::string& charRace,
                const std::string& charClass, Observer* observer);
        ~PlayableCharacterFactory();
};

class NpcFactory {
    Json::Value npcsObj;
    public:
        explicit NpcFactory(const std::string& configFile);
        void create(Map* map,const std::string& specie,Observer* observer);
        ~NpcFactory();
};

#endif //ARGENTUM_FACTORY_H
