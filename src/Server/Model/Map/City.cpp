#include <utility>
#include <Common/Utils.h>
#include "City.h"
#include "Server/Model/Character/PlayableCharacter.h"

City::City(int x, int y, int height, int width): Obstacle(x, y, height, width){}

City::City(City &&city) noexcept:Obstacle(city)  {}

Position City::getRandomPos(Map *map) {
    int x, y;
    x = Utils::random_int_number(position.getX(), position.getX() + height - 1);
    y = Utils::random_int_number(position.getY(), position.getY() + width - 1);
    while (map->isOccupied(Position(x, y))) {
        x = Utils::random_int_number(position.getX(), position.getX() + height - 1);
        y = Utils::random_int_number(position.getY(), position.getY() + width - 1);
    }
    return Position(x, y);
}

