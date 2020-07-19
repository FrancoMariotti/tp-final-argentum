//
// Created by franco on 5/7/20.
//

#ifndef ARGENTUM_TAKEITEMCOMMAND_H
#define ARGENTUM_TAKEITEMCOMMAND_H


#include "Command.h"
#include "Servidor/Modelo/Map/Map.h"

class TakeItemCommand : public Command {
    Map* map;
public:
    explicit TakeItemCommand(Map *map);
    void execute(std::string username,std::string params,int x,int y) override;
};


#endif //ARGENTUM_TAKEITEMCOMMAND_H
