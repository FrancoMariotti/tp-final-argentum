//
// Created by franco on 6/7/20.
//

#ifndef ARGENTUM_LISTITEMSCOMMAND_H
#define ARGENTUM_LISTITEMSCOMMAND_H


#include "Command.h"
#include "Map.h"

class ListItemsCommand  : public Command {
    Map* map;
public:
    explicit ListItemsCommand(Map *map);
    void execute(std::string username,std::string command,int x,int y) override;
};



#endif //ARGENTUM_LISTITEMSCOMMAND_H
