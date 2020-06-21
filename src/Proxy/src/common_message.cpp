//
// Created by agustin on 19/6/20.
//

#include <string>
#include "common_message.h"


char Message::getId(char id) const {
    return id;
}

int Message::getPlayerVelX() const {
    return 0;
}

int Message::getPlayerVelY() const {
    return 0;
}

int Message::getIndex() const {
    return 0;
}

Movement::Movement(const int player_vel_x, const int player_vel_y) :
        id('m'),
        player_vel_x(player_vel_x),
        player_vel_y(player_vel_y)
        {}

char Movement::getId() const{
    return Message::getId(id);
}

int Movement::getPlayerVelX() const {
    return player_vel_x;
}

int Movement::getPlayerVelY() const {
    return player_vel_y;
}

UseItem::UseItem(const int i) :
    id('u'),
    inventory_i(i)
    {}

char UseItem::getId() const {
    return Message::getId(id);
}

int UseItem::getIndex() const {
    return inventory_i;
}

Draw::Draw(std::string name, int x, int y) : id('d'), name(name), x(x), y(y) {

}

char Draw::getId() const {
    return Message::getId(id);
}
