//
// Created by franco on 11/7/20.
//

#include "ItemSeller.h"
#include "Servidor/Modelo/Factory.h"

ItemSeller::ItemSeller(std::map<std::string, item_t> stock, ItemFactory *itemFactory)
    : stock(stock), itemFactory(itemFactory) {}

Equippable *ItemSeller::sell(const std::string &name, int *gold) {
    if (stock.find(name) == stock.end()) return nullptr;
    item_t item = stock.at(name);
    if (item.goldCost > *gold) return nullptr;
    *gold -= item.goldCost;
    if (*gold < 0) *gold = 0;
    return itemFactory->create(item);
}


