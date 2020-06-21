//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_COMMON_MESSAGE_H
#define ARGENTUM_COMMON_MESSAGE_H


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
    const int x; // x en unidaes del modelo
    const int y; // y en unidades del modelo
public:
    Draw(std::string name, int x, int y);
    std::string getTileName() const override;
    int getTileX() const override;
    int getTileY() const override;
};

#endif //ARGENTUM_COMMON_MESSAGE_H
