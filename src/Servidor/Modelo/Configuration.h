//
// Created by franco on 15/7/20.
//

#ifndef ARGENTUM_CONFIGURATION_H
#define ARGENTUM_CONFIGURATION_H

#include <map>

class Configuration {
    //static Configuration* instance;
    std::map<std::string, float> constants;
    Configuration() = default;
    friend class Game;
    friend class PlayableCharacterFactory;
    friend class BankAccount;
    friend class Map;
    friend class Npc;
    friend class PlayableCharacter;
public:
    static Configuration& getInstance();
    ~Configuration() = default;
};


#endif //ARGENTUM_CONFIGURATION_H
