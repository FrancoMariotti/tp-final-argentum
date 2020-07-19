//
// Created by franco on 4/7/20.
//

#ifndef ARGENTUM_HEALCOMMAND_H
#define ARGENTUM_HEALCOMMAND_H


#include "Command.h"
#include "Servidor/Modelo/Map/Map.h"

class HealCommand : public Command {
    Map* map;
public:
    explicit HealCommand(Map *map);
    void execute(std::string username,std::string command,int x,int y) override;
};


#endif //ARGENTUM_HEALCOMMAND_H
