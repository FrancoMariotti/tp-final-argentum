//
// Created by franco on 5/7/20.
//

#ifndef ARGENTUM_DROPITEMCOMMAND_H
#define ARGENTUM_DROPITEMCOMMAND_H


#include "Command.h"
#include "Map.h"

class DropItemCommand : public Command {
    Map* map;
public:
    explicit DropItemCommand(Map *map);
    void execute(std::string username,std::string params,int x,int y) override;

};


#endif //ARGENTUM_DROPITEMCOMMAND_H
