#include "Merchant.h"
#include <tuple>
#define COST 0
#define MAX 1
#define MIN 2

Merchant::Merchant(std::string& configFile,const Json::Value& items, Position pos) : configFile(configFile),pos(pos) {
    factories["NormalWeapon"] = new NormalWeaponFactory();
    factories["RangeWeapon"] = new RangeWeaponFactory();
    factories["Protection"] = new ProtectionFactory();
    factories["LifePotion"] = new LifePotionFactory();
    factories["ManaPotion"] = new ManaPotionFactory();

    for (const auto &item : items) {
        std::string itemName = item["name"].asString();
        costs[itemName] = item["goldCost"].asInt();
        stock[itemName] = factories.at(item["type"].asString());
    }
}

Equippable* Merchant::sell(const std::string& name, int *gold) {
    if (costs.find(name) == costs.end() || stock.find(name) == stock.end()) return nullptr;
    int cost = costs.at(name);
    if (cost > *gold) return nullptr;
    *gold -= cost;
    return stock.at(name)->create(configFile,name,cost);
}

int Merchant::buy(const std::string& itemName) {
    return costs.at(itemName);
}

Merchant::Merchant(Merchant &&merchant) noexcept :configFile(merchant.configFile),pos(merchant.pos) {
    this->costs = merchant.costs;
    this->stock = merchant.stock;
    this->factories = merchant.factories;
    merchant.stock.clear();
    merchant.costs.clear();
    merchant.factories.clear();
}

Merchant::~Merchant() {
    auto it = factories.begin();
    for(;it!=factories.end();it++) {
        delete it->second;
    }
}
