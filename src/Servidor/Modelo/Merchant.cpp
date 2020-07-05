#include <iostream>
#include <utility>
#include "Merchant.h"
#include "Factory.h"

Merchant::Merchant(std::vector<Position> positions, std::map<std::string, item_t> stock ,
                   std::map<std::string, EquippableFactory*> factories):
                   positions(std::move(positions)),stock(std::move(stock)),factories(std::move(factories)) {}

Equippable* Merchant::sell(const std::string& name, int *gold) {
    if (stock.find(name) == stock.end()) return nullptr;
    item_t item = stock.at(name);
    if (item.goldCost > *gold) return nullptr;
    *gold -= item.goldCost;
    return factories.at(name)->create(item);
}

int Merchant::buy(const std::string& itemName) {
    return stock.at(itemName).goldCost;
}

//Merchant::Merchant(Merchant &merchant) noexcept {}

Merchant::Merchant(Merchant &&merchant) noexcept :positions(merchant.positions),
                            stock(merchant.stock),factories(merchant.factories) {
    merchant.factories.clear();
}

bool Merchant::ocupies(Position position) {
    for (Position & pos : positions) {
        if (pos == position) return true;
    }
    return false;
}

Merchant::~Merchant() {
    auto it = factories.begin();
    for(;it!=factories.end();it++) {
        delete it->second;
    }
}

Merchant& Merchant::operator=(const Merchant&) {
    return *this;
}
