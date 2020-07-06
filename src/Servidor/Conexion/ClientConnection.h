//
// Created by franco on 6/7/20.
//

#ifndef ARGENTUM_CLIENTCONNECTION_H
#define ARGENTUM_CLIENTCONNECTION_H


#include <Proxy/src/common_socket.h>
#include <Proxy/src/common_message.h>
#include <memory>
#include "ThClientSender.h"
#include "ThClientReceiver.h"

class ClientConnection {
    Socket client;
    ThClientSender sender;
    ThClientReceiver receiver;
    bool dead{};
public:
    ClientConnection(Socket client, ProtectedList<std::unique_ptr<Message>>& messages,
                     BlockingQueue<std::unique_ptr<Message>>& events);
    ClientConnection(ClientConnection&) = delete;
    ClientConnection(ClientConnection&&) noexcept ;
    bool isDead();
    void joinResources();
    void start();

    void finish();
};


#endif //ARGENTUM_CLIENTCONNECTION_H
