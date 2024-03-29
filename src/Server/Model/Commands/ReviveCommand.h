//
// Created by franco on 4/7/20.
//

#ifndef ARGENTUM_REVIVECOMMAND_H
#define ARGENTUM_REVIVECOMMAND_H


#include <string>
#include "Command.h"
#include "Server/Model/Map/Map.h"


class ReviveCommand : public Command {
    Map* map;
public:
    explicit ReviveCommand(Map *map);
    void execute(std::string username,std::string params,int x,int y) override;
};



#endif //ARGENTUM_REVIVECOMMAND_H
