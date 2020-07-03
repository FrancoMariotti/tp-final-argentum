//
// Created by franco on 30/6/20.
//

#ifndef ARGENTUM_MERCHANT_H
#define ARGENTUM_MERCHANT_H


#include <map>
#include <string>
#include "Factory.h"

class Merchant {
    friend class City;
    Position pos;
    Json::Value obj;
    std::map<std::string, EquippableFactory*> stock;
    std::map<std::string, EquippableFactory*> factories;
public:
    Merchant(const std::string& configFile, Position pos);
    ~Merchant();
    Equippable* sell(const std::string& name, int *gold);
    int buy(const std::string& itemName);
};


#endif //ARGENTUM_MERCHANT_H
