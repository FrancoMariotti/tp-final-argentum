//
// Created by franco on 1/7/20.
//

#include "Priest.h"
#include "PlayableCharacter.h"

Priest::Priest(const Json::Value& items, const Position& pos):pos(pos) {
    factories["MagicalWeapon"] = new MagicalWeaponFactory();
    factories["LifePotion"] = new LifePotionFactory();
    factories["ManaPotion"] = new ManaPotionFactory();
    for (const auto &item : items) {
        stock[item["name"].asString()] = factories.at(item["type"].asString());
    }
}

Equippable* Priest::sell(const std::string& name, int *gold) {
    int cost = items[name]["goldCost"].asInt();
    if (cost > *gold) return nullptr;
    *gold -= cost;
    return stock.at(name)->create(items[name]);
}

void Priest::restoreManaAndLife(PlayableCharacter* character) {
    if(!character->isDead()) {
        character->restoreLife();
        character->restoreMana();
    }
}

void Priest::revive(PlayableCharacter* character) {
    if (character->isDead())character->revive();
}

Priest::~Priest(){
    auto it = factories.begin();
    for(;it!=factories.end();it++) {
        delete it->second;
    }
}

Priest::Priest(Priest &&priest) noexcept:pos(priest.pos)  {
    this->factories = priest.factories;
    priest.factories.clear();
}

