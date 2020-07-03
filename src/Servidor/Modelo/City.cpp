//
// Created by franco on 2/7/20.
//

#include <Servidor/Common/Utils.h>
#include "City.h"
#include "Map.h"

City::City(int x, int y, int height, int width, std::string configFile,
        Position priestPos, Position merchantPos, Position bankerPos)
        : Obstacle(x, y, height, width), priest(configFile, priestPos)
        , merchant(configFile, merchantPos), banker(bankerPos){}

bool City::isOcupied(Position pos) {
    return priest.pos == pos || banker.pos == pos || merchant.pos == pos;
}
