//
// Created by franco on 1/7/20.
//

#ifndef ARGENTUM_PRIEST_H
#define ARGENTUM_PRIEST_H

//#include "PlayableCharacter.h"

#include "Factory.h"

class Priest {
    friend class City;
    Position pos;
    Json::Value items;
    std::string configFile;
    std::map<std::string, int> costs;
    std::map<std::string, EquippableFactory*> stock;
    std::map<std::string, EquippableFactory*> factories;
public:
    Priest(std::string configFile,const Json::Value& items, const Position& pos);
    Priest(Priest&& priest) noexcept ;
    ~Priest();
    Equippable* sell(const std::string& name, int *gold);
    void restoreManaAndLife(PlayableCharacter* character);
    void revive(PlayableCharacter* character);

    void reviveIn(PlayableCharacter *character, Position position);
};


#endif //ARGENTUM_PRIEST_H
