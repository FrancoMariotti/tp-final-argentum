#ifndef ARGENTUM_COMMAND_H
#define ARGENTUM_COMMAND_H

class Command {
public:
    virtual void execute(std::string username,std::string command,int x,int y) = 0;
    virtual ~Command() = default;
};

#endif //ARGENTUM_COMMAND_H
