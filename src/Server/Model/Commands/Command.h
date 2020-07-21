#ifndef ARGENTUM_COMMAND_H
#define ARGENTUM_COMMAND_H


#include "string"
class Command {
public:
    virtual void execute(std::string username,std::string params,int x,int y) = 0;
    virtual ~Command() = default;
};

#endif //ARGENTUM_COMMAND_H