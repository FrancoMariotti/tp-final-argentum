#include <string>
#include <iostream>
#include <utility>
#include "Message.h"
#include "OsException.h"


Message::Message(const int id) :
    id(id)
    {}

int Message::getId() const {
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

std::string Message::getLayerName() const {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

std::vector<int> Message::getData() const {
     throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

int Message::getWidth() const {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}
int Message::getHeight() const {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

t_stats Message::getStats() {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

equipment_t Message::getEquipment() {
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

std::vector<location_t> Message::getSpawnData() {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

location_t Message::getLocation() {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}


std::vector<std::string> Message::getConsoleOutput() {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

t_create_connect Message::getConnectData() const {
    throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

std::vector<spawn_playable_character_t> Message::getPcSpawnData() {
   throw OSError("Getter de atributo de instancia inexistente, "
                  "fue delegado a padre Message (abstracta), id mensaje: %c", id);
}

Movement::Movement(const int player_vel_x, const int player_vel_y) :
        Message(MOVEMENT_MESSAGE_ID),
        player_vel_x(player_vel_x),
        player_vel_y(player_vel_y)
        {}

int Movement::getPlayerVelX() const {
    return player_vel_x;
}

int Movement::getPlayerVelY() const {
    return player_vel_y;
}

UseItem::UseItem(const int i) :
    Message(USE_ITEM_MESSAGE_ID),
    inventory_i(i)
    {}

int UseItem::getIndex() const {
    return inventory_i;
}

Draw::Draw(std::string name, std::vector<int> data, int width, int height) :
    Message(DRAW_MESSAGE_ID), name(std::move(name)),width(width), height(height),data(std::move(data)) {
}

std::string Draw::getLayerName() const {
    return name;
}

std::vector<int> Draw::getData() const {
    return data;
}

int Draw::getWidth() const {
    return width;
}

int Draw::getHeight() const {
    return height;
}

Draw::Draw():Message(DRAW_MESSAGE_ID) {}


ExecuteCommand::ExecuteCommand(const std::string& command) :
    Message(COMMAND_MESSAGE_ID),
    username("franco"),
    command(command),
    x(-1),
    y(-1)
    {
        std::cout << command << "x:" << x << "y:" << y << std::endl;
    }

ExecuteCommand::ExecuteCommand(std::string username,std::string input,const int x,const int y) :
    Message(COMMAND_MESSAGE_ID),
    username(std::move(username)),
    command(std::move(input)),
    x(x),
    y(y)
    {
    std::cout << command << "x:" << x << "y:" << y << std::endl;
    }
ExecuteCommand::ExecuteCommand(std::string input,const int x,const int y) :
        Message(COMMAND_MESSAGE_ID),
        command(input),
        x(x),
        y(y)
{
    std::cout << command << std::endl;
    std::cout << "x:" << x << "y:" << y << std::endl;
}




std::string ExecuteCommand::getCommand() const {
    return command;
}

int ExecuteCommand::getX() const {
    return x;
}

int ExecuteCommand::getY() const {
    return y;
}

Connect::Connect(const std::string& username,const std::string race,const std::string char_class) :
                                                                    Message(CONNECT_MESSAGE_ID),
                                                                    username(username),
                                                                    race(race),
                                                                    char_class(char_class)
                                                                    {}

t_create_connect Connect::getConnectData() const{
    return t_create_connect{username, race, char_class};
}

Stats::Stats(float health_percentage, float mana_percentage, float exp_percentage, int gold, int level)
        : Message(STATS_UPDATE_MESSAGE_ID) {
    this->health_percentage = health_percentage;
    this->mana_percentage = mana_percentage;
    this->exp_percentage = exp_percentage;
    this->gold = gold;
    this->level = level;
}

t_stats Stats::getStats(){
    return t_stats{health_percentage, mana_percentage, exp_percentage, gold, level};
}

EquipmentUpdate::EquipmentUpdate(std::string weaponName, std::string armourName,
        std::string shieldName, std::string helmetName) : Message(EQUIPMENT_UPDATE_MESSAGE_ID),
        weaponName(std::move(weaponName)), armourName(std::move(armourName)), shieldName(std::move(shieldName)),
        helmetName(std::move(helmetName)) {}

equipment_t EquipmentUpdate::getEquipment() {
    return equipment_t {weaponName, armourName, shieldName, helmetName};
}

InventoryUpdate::InventoryUpdate(std::vector<std::string> &items) :
                                Message(INVENTORY_UPDATE_MESSAGE_ID) {
    this->items = std::move(items);
}

std::vector<std::string> InventoryUpdate::getItems() {
    return items;
}

SpawnPc::SpawnPc(std::vector<spawn_playable_character_t> renderables) :
                                    Message(SPAWN_PC_MESSAGE_ID),
                                    renderables(std::move(renderables)){}

std::vector<spawn_playable_character_t> SpawnPc::getPcSpawnData() {
    return std::move(renderables);
}

SpawnStaticObjects::SpawnStaticObjects(int messageId,std::vector<location_t> renderables):
                                                            Message(messageId),
                                                            renderables(std::move(renderables)){}
std::vector<location_t> SpawnStaticObjects::getSpawnData() {
    return std::move(renderables);
}

ActionUpdate::ActionUpdate(int messageId,std::string id,int x,int y):
                                                    Message(messageId),
                                                    id(std::move(id)),
                                                    x(x),
                                                    y(y){}
location_t ActionUpdate::getLocation() {
    return location_t{x,y,id};
}



ConsoleOutput::ConsoleOutput(std::vector<std::string> outputs) :
    Message(CONSOLE_OUTPUT_MESSAGE_ID),
    outputs(std::move(outputs))
    {}

std::vector<std::string> ConsoleOutput::getConsoleOutput() {
    return std::move(outputs);
}
