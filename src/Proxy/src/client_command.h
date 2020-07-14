//
// Created by agustin on 12/6/20.
//

#ifndef ARGENTUM_CLIENT_COMMAND_H
#define ARGENTUM_CLIENT_COMMAND_H

#include "Common/BlockingQueue.h"
#include "Common/common_proxy_socket.h"

class Message;
class Command {
public:
    virtual void operator()(BlockingQueue<std::unique_ptr<Message>>& clientEvents , int i) = 0;
    virtual ~Command() = default;
};

class UseItemCommand: public Command{
public:
    void operator()(BlockingQueue<std::unique_ptr<Message>>& clientEvents, int i) override;
};


#endif //ARGENTUM_CLIENT_COMMAND_H
