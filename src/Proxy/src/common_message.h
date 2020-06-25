//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_COMMON_MESSAGE_H
#define ARGENTUM_COMMON_MESSAGE_H

#include <string>
#include <vector>

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
    virtual std::vector<int> getData();
    virtual int getWidth();
    virtual int getHeight();
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
    std::string name; // nombre del layer a dibujar
    int width, height;
    std::vector<int> data;// x e y en unidades del modelo
public:
    Draw(std::string name, std::vector<int> data, int width, int height);
    std::string getTileName() const override;
    std::vector<int> getData() override;
    int getWidth() override;
    int getHeight() override;
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
