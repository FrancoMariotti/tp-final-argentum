//
// Created by franco on 30/6/20.
//

#include "Merchant.h"

Merchant::Merchant(const std::string& configFile, Position pos) : pos(pos) {
    FileParser parser(configFile);
    obj = parser.read("merchantItems");
    factories.at("NormalWeapon") = new NormalWeaponFactory();
    factories.at("RangeWeapon") = new RangeWeaponFactory();
    factories.at("Protection") = new ProtectionFactory();
    factories.at("LifePotion") = new LifePotionFactory();
    factories.at("ManaPotion") = new ManaPotionFactory();
    for (const auto &equipmentName : obj) {
        stock.at(equipmentName.asString()) = factories.at(equipmentName["type"].asString());
    }
}

Equippable* Merchant::sell(const std::string& name, int *gold) {
    int cost = obj[name]["goldCost"].asInt();
    if (cost > *gold) return NULL;
    *gold -= cost;
    return stock.at(name)->create(obj[name]);
}

int Merchant::buy(std::string itemName) {
    return obj[itemName]["goldCost"].asInt();
}

Merchant::~Merchant() {
    for (auto & factorie : factories) {
        delete factorie.second;
    }
}