//
// Created by franco on 30/6/20.
//

#ifndef ARGENTUM_MERCHANT_H
#define ARGENTUM_MERCHANT_H


#include <map>
#include <string>
#include "Position.h"
#include "Equippable.h"
#include "ItemSeller.h"


class EquippableFactory;
typedef struct item item_t;

class Merchant: public ItemSeller {
    std::vector<Position>positions;
    std::map<std::string,item_t> stock;
    std::map<std::string, EquippableFactory*> factories;
public:
    Merchant() = default;
    Merchant(std::vector<Position> positions, std::map<std::string,item_t> stock,
            std::map<std::string, EquippableFactory*> factories);
    //Merchant(Merchant& merchant) noexcept ;
    Merchant& operator=(Merchant&&) noexcept ;
    Merchant(Merchant&& merchant) noexcept ;
    Equippable* sell(const std::string& name, int *gold) override;
    int buy(const std::string& itemName);
    bool ocupies(Position position);
    ~Merchant();
};


#endif //ARGENTUM_MERCHANT_H
