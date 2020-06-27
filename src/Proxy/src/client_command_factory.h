//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_CLIENT_COMMAND_FACTORY_H
#define ARGENTUM_CLIENT_COMMAND_FACTORY_H


#include <string>
#include <list>

class Command;
class CommandFactory {
private:
    CommandFactory(const CommandFactory& other);
    CommandFactory(CommandFactory&& other) = default;
    std::list<std::string> valid_commands;
public:
    CommandFactory();
    //CommandFactory* getFactory();
    Command* get(const std::string& input_text, int x, int y);

};


#endif //ARGENTUM_CLIENT_COMMAND_FACTORY_H
