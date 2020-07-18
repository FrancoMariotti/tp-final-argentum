//
// Created by franco on 18/7/20.
//

#ifndef ARGENTUM_PRIVATEMESSAGECOMMAND_H
#define ARGENTUM_PRIVATEMESSAGECOMMAND_H


#include "Command.h"
#include "Map.h"

class PrivateMessageCommand : public Command {
    Map* map;
public:
    explicit PrivateMessageCommand(Map *map);
    void execute(std::string username, std::string params, int x, int y) override;
};


#endif //ARGENTUM_PRIVATEMESSAGECOMMAND_H
