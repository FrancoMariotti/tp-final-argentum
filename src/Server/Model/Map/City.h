#ifndef ARGENTUM_CITY_H
#define ARGENTUM_CITY_H

#include "Obstacle.h"
#include "Server/Model/Character/Priest.h"
#include "Server/Model/Character/Merchant.h"
#include "Server/Model/Character/Banker.h"

class City : public Obstacle {
public:
    City(int x, int y, int height, int width);
    City(City &&city) noexcept ;
    Position getRandomPos(Map *map);
};


#endif //ARGENTUM_CITY_H
