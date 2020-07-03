//
// Created by franco on 2/7/20.
//

#ifndef ARGENTUM_DEPOSITCOMMAND_H
#define ARGENTUM_DEPOSITCOMMAND_H


#include "Command.h"
#include "Map.h"

class DepositCommand: public Command {
    Map* map;
public:
    explicit DepositCommand(Map *map);
    void execute(std::string username,std::string command,int x,int y) override;
};


#endif //ARGENTUM_DEPOSITCOMMAND_H
