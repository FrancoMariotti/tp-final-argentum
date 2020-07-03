//
// Created by franco on 3/7/20.
//

#ifndef ARGENTUM_COMMANDEXECUTOR_H
#define ARGENTUM_COMMANDEXECUTOR_H
#include "map"
#include "Command.h"
#include "Map.h"

class CommandExecutor {

    std::map<std::string,Command*> commands;
public:
    CommandExecutor(Map *map);
    void execute(const std::string& username,const std::string& command,int x,int y);
    ~CommandExecutor();

    CommandExecutor();
};


#endif //ARGENTUM_COMMANDEXECUTOR_H
