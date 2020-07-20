//
// Created by franco on 30/6/20.
//

#ifndef ARGENTUM_MERCHANT_H
#define ARGENTUM_MERCHANT_H


#include <map>
#include <string>
#include "Server/Model/Map/Position.h"
#include "Server/Model/Equippables/Equippable.h"
#include "ItemSeller.h"

class Merchant: public ItemSeller {
    //friend class Npc;
    std::vector<Position>positions;
public:
    Merchant() = default;
    Merchant(std::vector<Position> positions, std::map<std::string,item_t> stock,
        ItemFactory* itemFactory);
    int buy(const std::string& itemName);
    bool ocupies(Position position);
    ~Merchant();

    void sendStockListTo(PlayableCharacter *pCharacter);
};


#endif //ARGENTUM_MERCHANT_H
