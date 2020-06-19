//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_COMMON_MESSAGE_H
#define ARGENTUM_COMMON_MESSAGE_H


class Message {
public:
    virtual char getId() const = 0;
    virtual int getPlayerX() const = 0;
    virtual int getPlayerY() const = 0;
    virtual int getIndex() const = 0;
    //virtual ~Message() = default;

};

class Movement : public Message{
private:
    const char id;
    const int player_vel_x;
    const int player_vel_y;
public:
    Movement(int player_vel_x, int player_vel_y);
    char getId() const override;
    int getPlayerX() const override;
    int getPlayerY() const override;
    int getIndex() const override;
};

class UseItem : public Message{
private:
    const char id ;
    const int inventory_i;
public:
    explicit UseItem(int i);
    char getId() const override;
    int getIndex() const override;
    int getPlayerX() const override;
    int getPlayerY() const override;
};

#endif //ARGENTUM_COMMON_MESSAGE_H
