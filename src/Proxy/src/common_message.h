//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_COMMON_MESSAGE_H
#define ARGENTUM_COMMON_MESSAGE_H

#include <string>
#include <vector>
#include "common_message_structs.h"
enum MESSAGES {
    /*logeo Qt*/
    PROXY_CONNECT_MESSAGE_ID,
    LOGIN_MESSAGE_ID,
    SIGNUP_MESSAGE_ID,
    CREATE_MESSAGE_ID,
    /**/
    ACCEPT_CREDENTIALS_MESSAGE_ID,
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
    virtual std::string getLayerName() const;
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
    virtual std::vector<spawn_playable_character_t> getPcSpawnData();
    virtual npc_movement_t getMovement();
    virtual t_player_attack getAttack();
    virtual std::vector<std::string> getConsoleOutput();
    virtual t_create_connect getConnectData() const;
    virtual bool getAnswer() const;
    virtual t_login getLogin() const;
    virtual ~Message() = default;
};

class Draw : public Message {
private:
    std::string name; // nombre del layer a dibujar
    int width, height;
    std::vector<int> data;// x e y en unidades del modelo
public:
    Draw(std::string name, std::vector<int> data, int width, int height);
    std::string getLayerName() const override;
    std::vector<int> getData() override;
    int getWidth() override;
    int getHeight() override;
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

class ExecuteCommand : public Message {
private:
    const std::string username;
    const std::string command;
    const int x;
    const int y;
public:
    ExecuteCommand(const std::string& command, const std::string& username);
    ExecuteCommand(const std::string& input, const std::string& username, int x, int y);
    std::string getUserName() const;
    std::string getCommand() const override;
    int getX() const override;
    int getY() const override;
};

class Create : public Message {
private:
    const std::string username;
    const std::string password;
    const std::string race;
    const std::string char_class;
public:
    Create(const std::string &username, const std::string &password, const std::string &race,
           const std::string &char_class);
    t_create_connect getConnectData() const override;
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

class SpawnNpc : public Message {
    std::vector<spawn_character_t> renderables;
public:
    explicit SpawnNpc(std::vector<spawn_character_t> renderables);
    std::vector<spawn_character_t> getSpawnData() override;
};

class SpawnPc : public Message {
    std::vector<spawn_playable_character_t> renderables;
public:
    explicit SpawnPc(std::vector<spawn_playable_character_t> renderables);
    std::vector<spawn_playable_character_t> getPcSpawnData() override;
};

class SpawnDrops: public Message {
    std::vector<spawn_character_t> renderables;
public:
    explicit SpawnDrops(std::vector<spawn_character_t> renderables);
    std::vector<spawn_character_t> getSpawnData() override;
};

class SpawnCityCharacters : public Message {
    std::vector<spawn_character_t> renderables;
public:
    SpawnCityCharacters(std::vector<spawn_character_t> renderables);
    std::vector<spawn_character_t> getSpawnData() override;
};

class MovementNpcUpdate: public Message {
    std::string id;
    int x;
    int y;
public:
    explicit MovementNpcUpdate(std::string id,int x,int y);
    npc_movement_t getMovement();
};

class Attack : public Message{
private:
    std::string username;
    int enemy_x;
    int enemy_y;
public:
    Attack(std::string username, int enemy_x, int enemy_y);
    t_player_attack getAttack() override;
};

class ConsoleOutput : public Message{
private:
    std::vector<std::string> outputs;
public:
    explicit ConsoleOutput(std::vector<std::string>);
    std::vector<std::string> getConsoleOutput() override;
};

/*Server side
 * envia un 0 si las credenciales son correctas, 1 en caso contrario no*/
class Accept : public Message{
private:
    const bool accepted;
public:
    explicit Accept(bool accepted);
    bool getAnswer() const;
};

class Login : public Message{
private:
    const std::string username;
    const std::string password;
public:
    Login(const std::string &username, const std::string &password, enum MESSAGES ID);
    t_login getLogin() const override;
};

#endif //ARGENTUM_COMMON_MESSAGE_H
