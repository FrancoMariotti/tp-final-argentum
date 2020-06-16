//
// Created by agustin on 12/6/20.
//

#ifndef ARGENTUM_CLIENT_COMMAND_H
#define ARGENTUM_CLIENT_COMMAND_H

#include "common_blocking_queue.h"
#include "common_proxy_socket.h"

class Command {
public:
    virtual void operator()(BlockingQueue<t_command> &event_sender, int i) = 0;
    virtual void free() = 0;
    virtual ~Command() = default;
};

class Use: public Command{
public:
    /*envia el comando 'e' por el socket*/
    void operator()(BlockingQueue<t_command> &event_sender, int i) override;
    void free() override;
};



#endif //ARGENTUM_CLIENT_COMMAND_H
