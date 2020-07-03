//
// Created by franco on 2/7/20.
//

#ifndef ARGENTUM_CITY_H
#define ARGENTUM_CITY_H

#include "Obstacle.h"
#include "Priest.h"
#include "Merchant.h"
#include "Banker.h"

class City : public Obstacle {
    Priest priest;
    Merchant merchant;
    Banker banker;
public:
    City(int x, int y, int height, int width, std::string configFile,
            Position priestPos, Position merchantPos, Position bankerPos);
    bool isOcupied(Position pos);
};


#endif //ARGENTUM_CITY_H
