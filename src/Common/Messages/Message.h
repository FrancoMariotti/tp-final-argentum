
//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_MESSAGE_H
#define ARGENTUM_MESSAGE_H

#include <string>
#include <vector>
#include "message_structs.h"
enum MESSAGES {
    CREATE_MESSAGE_ID,
    DRAW_MESSAGE_ID,
    MOVEMENT_MESSAGE_ID,
    USE_ITEM_MESSAGE_ID,
    COMMAND_MESSAGE_ID,
    INVENTORY_UPDATE_MESSAGE_ID,
    SPAWN_NPC_MESSAGE_ID,
    STATS_UPDATE_MESSAGE_ID,
    NPC_MOVEMENT_UPDATE_MESSAGE_ID,
    EQUIPMENT_UPDATE_MESSAGE_ID,
    PLAYER_ATTACK_MESSAGE_ID,
    SPAWN_CITY_CHARACTERS_MESSAGE_ID,
    SPAWN_DROPS_MESSAGE_ID,
    CONSOLE_OUTPUT_MESSAGE_ID,
    SPAWN_PC_MESSAGE_ID,
    LOGIN_MESSAGE_ID,
    SIGNUP_MESSAGE_ID,
    DISCONNECT_MESSAGE_ID
};


class Message {
protected:
    int id;
    int connectionId;
    explicit Message(int id);
public:
    int getId() const;
    void setConnectionlId(int id);
    int getConnectionlId() const;
    virtual int getPlayerVelX() const;
    virtual int getPlayerVelY() const;
    virtual int getIndex() const;
    virtual std::string getLayerName() const;
    virtual std::vector<int> getData() const ;
    virtual int getWidth() const ;
    virtual int getHeight() const ;
    virtual command_t getCommand() const;
    virtual int getX() const;
    virtual int getY() const;
    virtual t_stats getStats();
    virtual equipment_t getEquipment();
    virtual std::vector<std::string> getItems();
    virtual std::vector<location_t> getSpawnData();
    virtual std::vector<spawn_playable_character_t> getPcSpawnData();
    virtual location_t getLocation();
    virtual std::vector<std::string> getConsoleOutput();
    virtual create_player_t getCreateData() const;
    virtual t_client_login getLoginData() const;
    virtual std::string getUsername();
    virtual ~Message() = default;
};

class Draw : public Message {
private:
    std::string name;
    int width;
    int height;
    std::vector<int> data;
public:
    Draw();
    Draw(std::string name, std::vector<int> data, int width, int height);
    std::string getLayerName() const override;
    std::vector<int> getData() const override;
    int getWidth() const override;
    int getHeight() const override;
};

class Movement : public Message{
private:
    std::string id;
    const int player_vel_x;
    const int player_vel_y;
public:
    Movement(std::string id,int player_vel_x, int player_vel_y);
    location_t getLocation() override ;
};

class UseItem : public Message{
private:
    const int inventory_i;
public:
    explicit UseItem(int i);
    int getIndex() const override;
};

class ExecuteCommand : public Message {
private:
    const std::string username;
    const std::string command;
    const int x;
    const int y;
public:
    ExecuteCommand(const std::string& command, std::string  username);
    ExecuteCommand(std::string  input, std::string  username, int x, int y);
    command_t getCommand() const override;
};

class Create : public Message {
private:
    const std::string username;
    const std::string race;
    const std::string char_class;
public:
    Create(std::string  username, std::string  race,std::string  char_class);
    create_player_t getCreateData() const override;
};

class Stats : public Message {
    float health_percentage;
    float mana_percentage;
    float exp_percentage;
    int gold;
    int level;
public:
    Stats(float health_percentage, float mana_percentage, float exp_percentage, int gold, int level);
    t_stats getStats() override;
};

class EquipmentUpdate : public Message {
    std::string username;
    std::string weaponName;
    std::string armourName;
    std::string shieldName;
    std::string helmetName;
public:
    EquipmentUpdate(std::string username,std::string weaponName, std::string armourName,
            std::string shieldName, std::string helmetName);
    equipment_t getEquipment() override;
};

class InventoryUpdate: public Message {
    std::vector<std::string> items;
public:
    explicit InventoryUpdate(std::vector<std::string> &items);
    std::vector<std::string> getItems() override;
};

class SpawnStaticObjects : public Message {
    std::vector<location_t> renderables;
public:
    SpawnStaticObjects(int messageId,std::vector<location_t> renderables);
    std::vector<location_t> getSpawnData() override;
};

class SpawnPc : public Message {
    std::vector<spawn_playable_character_t> renderables;
public:
    explicit SpawnPc(std::vector<spawn_playable_character_t> renderables);
    std::vector<spawn_playable_character_t> getPcSpawnData() override;
};

class ActionUpdate: public Message {
    int x;
    int y;
    std::string id;
public:
    ActionUpdate(int messageId,std::string id,int x,int y);
    location_t getLocation() override;
};

class ConsoleOutput : public Message{
private:
    std::vector<std::string> outputs;
public:
    explicit ConsoleOutput(std::vector<std::string>);
    std::vector<std::string> getConsoleOutput() override;
};

class Login : public Message{
private:
    const std::string username;
    const std::string password;
public:
    Login(std::string  username, std::string  password, int msg_id);
    t_client_login getLoginData() const override;
};

class Disconnect : public Message {
private:
    const std::string username;
public:
    explicit Disconnect(std::string  username);
    std::string getUsername() override;
};

#endif //ARGENTUM_MESSAGE_H
