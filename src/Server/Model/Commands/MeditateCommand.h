//
// Created by franco on 19/7/20.
//

#ifndef ARGENTUM_MEDITATECOMMAND_H
#define ARGENTUM_MEDITATECOMMAND_H


#include "Command.h"
#include "Server/Model/Map/Map.h"

class MeditateCommand : public Command {
    Map* map;
public:
    explicit MeditateCommand(Map *map);
    void execute(std::string username,std::string params,int x,int y) override;
};


#endif //ARGENTUM_MEDITATECOMMAND_H
