//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_COMMON_MESSAGE_H
#define ARGENTUM_COMMON_MESSAGE_H

#include <string>
#include <vector>
#include "common_message_structs.h"
enum MESSAGES {
MOVEMENT_MESSAGE_ID,
DRAW_MESSAGE_ID,
COMMAND_MESSAGE_ID,
INVENTORY_UPDATE_MESSAGE_ID,
SPAWN_NPC_MESSAGE_ID,
STATS_UPDATE_MESSAGE_ID,
NPC_MOVEMENT_UPDATE_MESSAGE_ID,
EQUIPMENT_UPDATE_MESSAGE_ID
};


class Message {
protected:
    const int id;
    explicit Message(int id);
public:
    int getId() const;
    virtual int getPlayerVelX() const;
    virtual int getPlayerVelY() const;
    virtual int getIndex() const;
    virtual std::string getTileName() const;
    virtual int getTileX() const;
    virtual int getTileY() const;
    virtual std::vector<int> getData();
    virtual int getWidth();
    virtual int getHeight();
    virtual std::string getCommand() const;
    virtual int getX() const;
    virtual int getY() const;
    virtual t_stats getStats();
    virtual equipment_t getEquipment();
    virtual std::vector<std::string> getItems();
    virtual std::vector<spawn_character_t> getSpawnData();
    virtual ~Message() = default;
};

class Movement : public Message{
private:
    const int player_vel_x;
    const int player_vel_y;
public:
    Movement(int player_vel_x, int player_vel_y);
    int getPlayerVelX() const override;
    int getPlayerVelY() const override;
};

class UseItem : public Message{
private:
    const int inventory_i;
public:
    explicit UseItem(int i);
    int getIndex() const override;
};

class Draw : public Message {
private:
    std::string name; // nombre del layer a dibujar
    int width, height;
    std::vector<int> data;// x e y en unidades del modelo
public:
    Draw(std::string name, std::vector<int> data, int width, int height);
    std::string getTileName() const override;
    std::vector<int> getData() override;
    int getWidth() override;
    int getHeight() override;
};

class ExecuteCommand : public Message {
private:
    const std::string command;
    const int x;
    const int y;
public:
    explicit ExecuteCommand(const std::string command);
    ExecuteCommand(std::string input, int x, int y);
    std::string getCommand() const override;
    int getX() const override;
    int getY() const override;
};

class Connect : public Message {
private:
    const std::string username;
public:
    explicit Connect(const std::string username);
    std::string getUserName() const;
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
    std::string weaponName;
    std::string armourName;
    std::string shieldName;
    std::string helmetName;
public:
    EquipmentUpdate(std::string weaponName, std::string armourName,
            std::string shieldName, std::string helmetName);
    equipment_t getEquipment() override;

};

class InventoryUpdate: public Message {
    std::vector<std::string> items;
public:
    explicit InventoryUpdate(std::vector<std::string> &items);
    std::vector<std::string> getItems() override;
};

class SpawnNpc: public Message {
    std::vector<spawn_character_t> renderables;
public:
    explicit SpawnNpc(std::vector<spawn_character_t> renderables);
    std::vector<spawn_character_t> getSpawnData() override;
};


class MovementNpcUpdate: public Message {
    std::string id;
    int x;
    int y;
public:
    explicit MovementNpcUpdate(std::string id,int x,int y);
};



#endif //ARGENTUM_COMMON_MESSAGE_H
