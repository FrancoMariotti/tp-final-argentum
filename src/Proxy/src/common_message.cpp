//
// Created by agustin on 19/6/20.
//

#include <string>
#include "common_message.h"
#include "common_osexception.h"


Message::Message(const char id) :
    id(id)
    {}

char Message::getId() const {
    return id;
}

int Message::getPlayerVelX() const {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

int Message::getPlayerVelY() const {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

int Message::getIndex() const {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

std::string Message::getTileName() const {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

int Message::getTileX() const {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

int Message::getTileY() const {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

Movement::Movement(const int player_vel_x, const int player_vel_y) :
        Message('m'),
        player_vel_x(player_vel_x),
        player_vel_y(player_vel_y)
        {
        }

int Movement::getPlayerVelX() const {
    return player_vel_x;
}

int Movement::getPlayerVelY() const {
    return player_vel_y;
}

UseItem::UseItem(const int i) :
    Message('u'),
    inventory_i(i)
    {}

int UseItem::getIndex() const {
    return inventory_i;
}

Draw::Draw(const std::string name,const int x,const int y) :
    Message('d'),
    name(name),
    x(x),
    y(y)
    {}

std::string Draw::getTileName() const {
    return name;
}

int Draw::getTileX() const {
    return x;
}

int Draw::getTileY() const {
    return y;
}

