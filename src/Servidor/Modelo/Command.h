#ifndef ARGENTUM_COMMAND_H
#define ARGENTUM_COMMAND_H

#include <Proxy/src/common_message.h>

class Command {
public:
    virtual void execute(std::string username,std::string command,int x,int y) = 0;
};

#endif //ARGENTUM_COMMAND_H
