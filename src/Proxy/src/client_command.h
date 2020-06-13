//
// Created by agustin on 12/6/20.
//

#ifndef ARGENTUM_CLIENT_COMMAND_H
#define ARGENTUM_CLIENT_COMMAND_H

#include "common_blocking_queue.h"
#include "common_proxy_socket.h"

class Command {
public:
    virtual void operator()(ProxySocket &proxySocket) = 0;
    virtual void free() = 0;
    virtual ~Command() = default;
};

class Consume: public Command{
public:
    /*Envia el comando 'c' por el socket*/
    void operator()(ProxySocket &proxySocket) override;
    void free() override;
};

class Equip: public Command{
public:
    /*envia el comando 'e' por el socket*/
    void operator()(ProxySocket &proxySocket) override;
    void free() override;
};

class Move: public Command{
public:
    /*envia el comando 'm' por el socket para el movimiento*/
    /*Luego envia el offset*/
    void operator()(ProxySocket &proxySocket) override;
    void free() override;

};



#endif //ARGENTUM_CLIENT_COMMAND_H
