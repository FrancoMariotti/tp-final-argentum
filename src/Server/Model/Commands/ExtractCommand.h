//
// Created by franco on 4/7/20.
//

#ifndef ARGENTUM_EXTRACTCOMMAND_H
#define ARGENTUM_EXTRACTCOMMAND_H


#include "Command.h"
#include "Server/Model/Map/Map.h"

class ExtractCommand: public Command {
    Map* map;
public:
    explicit ExtractCommand(Map *map);
    void execute(std::string username,std::string command,int x,int y) override;
};


#endif //ARGENTUM_EXTRACTCOMMAND_H
