//
// Created by franco on 5/7/20.
//

#ifndef ARGENTUM_ITEMSELLER_H
#define ARGENTUM_ITEMSELLER_H

#include <map>
#include "string"
#include "Servidor/Modelo/Equippables/Equippable.h"

class ItemFactory;
typedef struct item item_t;

class ItemSeller{
protected:
    std::map<std::string,item_t> stock;
    ItemFactory* itemFactory;
public:
    ItemSeller() = default;
    ItemSeller(std::map<std::string,item_t> stock, ItemFactory* itemFactory);
    Equippable* sell(const std::string& name, int *gold);
};

#endif //ARGENTUM_ITEMSELLER_H
