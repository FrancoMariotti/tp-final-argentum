//
// Created by franco on 3/7/20.
//

#include "CommandExecutor.h"
#include "DepositCommand.h"
#include "ExtractCommand.h"

CommandExecutor::CommandExecutor() = default;

CommandExecutor::CommandExecutor(Map* map) {
    this->commands["/depositar"] = new DepositCommand(map);
    this->commands["/retirar"] = new ExtractCommand(map);
}

void CommandExecutor::execute(const std::string& username, const std::string& command, int x, int y) {
    std::string delimiter = " ";
    std::string token = command.substr(0, command.find(delimiter));
    auto itr = commands.find(token);

    if(itr != commands.end()) {
        std::string params = command.substr( command.find(delimiter) + 1);
        commands.at(token)->execute(username,params,x,y);
    }
}

CommandExecutor::~CommandExecutor() {
    auto itr = commands.begin();
    for(;itr!=commands.end();itr++) {
        delete itr->second;
    }
}



