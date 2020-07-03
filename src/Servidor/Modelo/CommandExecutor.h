//
// Created by franco on 3/7/20.
//

#ifndef ARGENTUM_COMMANDEXECUTOR_H
#define ARGENTUM_COMMANDEXECUTOR_H
#include "map"
#include "Command.h"

class CommandExecutor {
    std::map<std::string,Command*> commands;
public:
    CommandExecutor();
    void execute(const std::string& username,const std::string& command,int x,int y);
    ~CommandExecutor();
};


#endif //ARGENTUM_COMMANDEXECUTOR_H
