//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_COMMON_MESSAGE_H
#define ARGENTUM_COMMON_MESSAGE_H

#include <string>
#include <vector>

typedef struct position {
    position(int newX, int newY) {
        x = newX;
        y = newY;
    }
    int x;
    int y;
} position_t;

class Message {
protected:
    const char id;
    explicit Message(char id);
public:
    char getId() const;
    virtual int getPlayerVelX() const;
    virtual int getPlayerVelY() const;
    virtual int getIndex() const;
    virtual std::string getTileName() const;
    virtual int getTileX() const;
    virtual int getTileY() const;
    virtual position_t getPosition();
};

class Movement : public Message{
private:
    const int player_vel_x;
    const int player_vel_y;
public:
    Movement(int player_vel_x, int player_vel_y);
    int getPlayerVelX() const override ;
    int getPlayerVelY() const override ;
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
    std::string name; // nombre del tile a dibujar
    std::vector<position_t> positions;// x e y en unidades del modelo
public:
    Draw(std::string name, std::vector<position_t>& positions);
    std::string getTileName() const override;
    virtual position_t getPosition() override;
    //int getTileX() const override;
    //int getTileY() const override;
};

class ExecuteCommand : public Message {
private:
    const std::string command;
public:
    explicit ExecuteCommand(const std::string command);
    std::string getCommand();
};

class Connect : public Message {
private:
    const std::string username;
public:
    explicit Connect(const std::string username);
    std::string getUserName() const;
};

#endif //ARGENTUM_COMMON_MESSAGE_H
