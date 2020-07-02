//
// Created by franco on 1/7/20.
//

#include "Priest.h"
#include "PlayableCharacter.h"

Priest::Priest(const std::string& configFile) {
    FileParser parser(configFile);
    obj = parser.read("priestItems");
    factories.at("MagicalWeapon") = new MagicalWeaponFactory();
    factories.at("LifePotion") = new LifePotionFactory();
    factories.at("ManaPotion") = new ManaPotionFactory();
    for (const auto &equipmentName : obj) {
        stock.at(equipmentName.asString()) = factories.at(equipmentName["type"].asString());
    }
}

Equippable* Priest::sell(const std::string& name, int *gold) {
    int cost = obj[name]["goldCost"].asInt();
    if (cost > *gold) return NULL;
    *gold -= cost;
    return stock.at(name)->create(obj[name]);
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

Priest::~Priest() {
     for (auto & factorie : factories) {
        delete factorie.second;
    }
}