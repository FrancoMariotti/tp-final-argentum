//
// Created by agustin on 19/6/20.
//

#include "common_message.h"

Movement::Movement(const int player_vel_x, const int player_vel_y) :
        id('m'),
        player_vel_x(player_vel_x),
        player_vel_y(player_vel_y)
        {}

char Movement::getId() const{
    return id;
}

int Movement::getPlayerX() const {
    return player_vel_x;
}

int Movement::getPlayerY() const {
    return player_vel_y;
}

int Movement::getIndex() const {
    return 0;
}

UseItem::UseItem(const int i) :
    id('u'),
    inventory_i(i)
    {}

char UseItem::getId() const {
    return id;
}

int UseItem::getIndex() const {
    return inventory_i;
}

int UseItem::getPlayerX() const {
    return 0;
}

int UseItem::getPlayerY() const {
    return 0;
}
