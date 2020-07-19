//
// Created by franco on 5/7/20.
//

#ifndef ARGENTUM_SELLCOMMAND_H
#define ARGENTUM_SELLCOMMAND_H


#include "Command.h"
#include "Servidor/Modelo/Map/Map.h"

class SellCommand: public Command {
    Map* map;
public:
    explicit SellCommand(Map* map);
    void execute(std::string username, std::string params, int x, int y) override;
};


#endif //ARGENTUM_SELLCOMMAND_H
