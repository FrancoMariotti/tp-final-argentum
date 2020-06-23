//
// Created by agustin on 23/6/20.
//

#include "client_command_factory.h"
#include "client_command.h"

CommandFactory::CommandFactory() = default;

Command *CommandFactory::get(const std::string& input_text) {
    Command* command = nullptr;
    if(input_text == "/tomar"){
      command = new ConsoleCommand("tomar");
    }
    return command;
}
