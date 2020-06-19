//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_COMMON_MESSAGE_H
#define ARGENTUM_COMMON_MESSAGE_H


class Message {
protected:
    virtual char getId(char id) const;
public:
    /*Pure virtual es para que llame a las derivadas y estas llamen a la base con @param id*/
    virtual char getId() const = 0;
    virtual int getPlayerVelX() const;
    virtual int getPlayerVelY() const;
    virtual int getIndex() const;
    //virtual ~Message() = default;
};

class Movement : public Message{
private:
    const char id;
    const int player_vel_x;
    const int player_vel_y;
public:
    Movement(int player_vel_x, int player_vel_y);
    char getId() const override ;
    int getPlayerVelX() const override ;
    int getPlayerVelY() const override ;
};

class UseItem : public Message{
private:
    const char id ;
    const int inventory_i;
public:
    explicit UseItem(int i);
    char getId() const override ;
    int getIndex() const override;
};

#endif //ARGENTUM_COMMON_MESSAGE_H
