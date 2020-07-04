//
// Created by franco on 1/7/20.
//

#include "Priest.h"
#include "PlayableCharacter.h"

Priest::Priest(std::string configFile,const Json::Value& items, const Position& pos):pos(pos),configFile(configFile) {
    factories["MagicalWeapon"] = new MagicalWeaponFactory();
    factories["LifePotion"] = new LifePotionFactory();
    factories["ManaPotion"] = new ManaPotionFactory();
    for (const auto &item : items) {
        std::string itemName = item["name"].asString();
        stock[itemName] = factories.at(item["type"].asString());
        costs[itemName] = item["goldCost"].asInt();
    }
}

Equippable* Priest::sell(const std::string& name, int *gold) {
    int cost = costs.at(name);
    if (cost > *gold) return nullptr;
    *gold -= cost;
    return stock.at(name)->create(configFile,name,cost);
}

void Priest::restoreManaAndLife(PlayableCharacter* character) {
    character->healedByPriest();
}

void Priest::revive(PlayableCharacter* character) {
    character->revive();
}

void Priest::reviveIn(PlayableCharacter *character, Position position) {
    character->revive();
    character->teleportTo(position);
}

Priest::~Priest(){
    auto it = factories.begin();
    for(;it!=factories.end();it++) {
        delete it->second;
    }
}

Priest::Priest(Priest &&priest) noexcept:pos(priest.pos), configFile(priest.configFile) {
    this->factories = priest.factories;
    priest.factories.clear();
}

