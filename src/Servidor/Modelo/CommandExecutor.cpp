//
// Created by franco on 3/7/20.
//

#include "CommandExecutor.h"
#include "DepositCommand.h"

CommandExecutor::CommandExecutor() {
    this->commands["/depositar"] = new DepositCommand();
}

void CommandExecutor::execute(const std::string& username, const std::string& command, int x, int y) {
    std::string delimiter = " ";
    std::string token = command.substr(0, command.find(delimiter)); // token is "scott"
    auto itr = commands.find(token);

    if(itr != commands.end()) {
        commands.at(token)->execute(username,command,x,y);
    }

}

CommandExecutor::~CommandExecutor() {
    auto itr = commands.begin();
    for(;itr!=commands.end();itr++) {
        delete itr->second;
    }
}



