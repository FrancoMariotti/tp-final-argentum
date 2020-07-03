#include "Merchant.h"

Merchant::Merchant(const Json::Value& items, Position pos) : pos(pos) {
    factories["NormalWeapon"] = new NormalWeaponFactory();
    factories["RangeWeapon"] = new RangeWeaponFactory();
    factories["Protection"] = new ProtectionFactory();
    factories["LifePotion"] = new LifePotionFactory();
    factories["ManaPotion"] = new ManaPotionFactory();

    for (const auto &item : items) {
        stock[item["name"].asString()] = factories.at(item["type"].asString());
    }
}

Equippable* Merchant::sell(const std::string& name, int *gold) {
    int cost = obj[name]["goldCost"].asInt();
    if (cost > *gold) return nullptr;
    *gold -= cost;
    return stock.at(name)->create(obj[name]);
}

int Merchant::buy(const std::string& itemName) {
    return obj[itemName]["goldCost"].asInt();
}

Merchant::~Merchant() {
    auto it = factories.begin();
    for(;it!=factories.end();it++) {
        delete it->second;
    }
}

Merchant::Merchant(Merchant &&merchant) noexcept :pos(merchant.pos) {
    this->factories = merchant.factories;
    merchant.factories.clear();
}
