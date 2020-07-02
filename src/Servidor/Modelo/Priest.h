//
// Created by franco on 1/7/20.
//

#ifndef ARGENTUM_PRIEST_H
#define ARGENTUM_PRIEST_H

//#include "PlayableCharacter.h"

#include "Factory.h"

class Priest {
    Json::Value obj;
    std::map<std::string, EquippableFactory*> stock;
    std::map<std::string, EquippableFactory*> factories;
public:
    Priest(const std::string& configFile);
    ~Priest();
    Equippable* sell(const std::string& name, int *gold);
    void restoreManaAndLife(PlayableCharacter* character);
    void revive(PlayableCharacter* character);
};


#endif //ARGENTUM_PRIEST_H
