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

std::vector<int> Message::getData() {
     throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

int Message::getWidth() {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}
int Message::getHeight() {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

t_stats Message::getStats() {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

std::vector<std::string> Message::getItems() {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

std::string Message::getCommand() const {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

int Message::getX() const {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);

}

int Message::getY() const {
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

Draw::Draw(std::string name, std::vector<int> data, int width, int height) :
    Message('d'), name(name), width(width), height(height) {
    this->data = std::move(data);
}

std::string Draw::getTileName() const {
    return name;
}

std::vector<int> Draw::getData() {
    return std::move(data);
}

int Draw::getWidth() {
    return width;
}

int Draw::getHeight() {
    return height;
}


ExecuteCommand::ExecuteCommand(const std::string command) :
    Message('/'),
    command(command),
    x(-1),
    y(-1)
    {}

ExecuteCommand::ExecuteCommand(const std::string input,const int x,const int y) :
    Message('/'),
    command(input),
    x(x),
    y(y)
    {}

std::string ExecuteCommand::getCommand() const {
    return command;
}

int ExecuteCommand::getX() const {
    return x;
}

int ExecuteCommand::getY() const {
    return y;
}

Connect::Connect(const std::string username) :
    Message('c'),
    username(username)
    {}

std::string Connect::getUserName() const {
    return username;
}

Stats::Stats(float health_percentage, float mana_percentage, float exp_percentage, int gold, int level)
        : Message('s') {
    this->health_percentage = health_percentage;
    this->mana_percentage = mana_percentage;
    this->exp_percentage = exp_percentage;
    this->gold = gold;
    this->level = level;
}

t_stats Stats::getStats(){
    return t_stats{health_percentage, mana_percentage, exp_percentage, gold, level};
}

InventoryUpdate::InventoryUpdate(std::vector<std::string> &items) : Message('i') {
    this->items = std::move(items);
}

std::vector<std::string> InventoryUpdate::getItems() {
    return items;
}
