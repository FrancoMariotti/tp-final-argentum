//
// Created by agustin on 19/7/20.
//

#ifndef ARGENTUM_CLIENT_UPDATE_H
#define ARGENTUM_CLIENT_UPDATE_H

#include <Common/Messages/Message.h>

class GUI;
class Update {
public:
    virtual void execute(GUI& gui, std::unique_ptr<Message> msg) const = 0;
    virtual ~Update() = default;
};

class InitDraw : public Update{
public:
    void execute(GUI& gui, std::unique_ptr<Message> msg) const override;

};

class UpdatePlayerPos : public Update{
    void execute(GUI &gui, std::unique_ptr<Message> msg) const override;
};

class UpdateInventory : public Update {
public:
    void execute(GUI &gui, std::unique_ptr<Message> msg) const override;
};

class UpdateStats : public Update{
public:
    void execute(GUI &gui, std::unique_ptr<Message> msg) const override;
};

class UpdateNPCs : public Update{
public:
    void execute(GUI &gui, std::unique_ptr<Message> msg) const override;
};

class UpdateDrops : public Update{
    void execute(GUI &gui, std::unique_ptr<Message> msg) const override;
};

class UpdateNPCPos : public Update{
    void execute(GUI &gui, std::unique_ptr<Message> msg) const override;
};

class UpdateConsole : public Update{
    void execute(GUI &gui, std::unique_ptr<Message> msg) const override;
};

class UpdateEquipment : public Update{
    void execute(GUI &gui, std::unique_ptr<Message> msg) const override;
};

class UpdatePlayers : public Update{
    void execute(GUI &gui, std::unique_ptr<Message> msg) const override;
};
#endif //ARGENTUM_CLIENT_UPDATE_H
