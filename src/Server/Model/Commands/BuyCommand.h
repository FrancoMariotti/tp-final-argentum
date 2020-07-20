//
// Created by franco on 4/7/20.
//

#ifndef ARGENTUM_BUYCOMMAND_H
#define ARGENTUM_BUYCOMMAND_H


#include "Command.h"
#include "Server/Model/Map/Map.h"

class BuyCommand: public Command {
    Map* map;
public:
    explicit BuyCommand(Map *map);
    void execute(std::string username, std::string params, int x, int y) override;
};


#endif //ARGENTUM_BUYCOMMAND_H
