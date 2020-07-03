//
// Created by franco on 2/7/20.
//

#include <Servidor/Common/Utils.h>
#include "City.h"
#include "Map.h"

City::City(int x, int y, int height, int width,
           const Json::Value& priestItems,const Position& priestPos, const Json::Value& merchantItems,
           const Position& merchantPos, const Position& bankerPos)
        : Obstacle(x, y, height, width), priest(priestItems,priestPos)
        , merchant(merchantItems,merchantPos), banker(bankerPos){}

bool City::isOcupied(const Position& pos) {
    return priest.pos == pos || banker.pos == pos || merchant.pos == pos;
}

City::City(City &&city) noexcept:Obstacle(city),priest(std::move(city.priest)),merchant(std::move(city.merchant)),banker(city.banker)  {}
