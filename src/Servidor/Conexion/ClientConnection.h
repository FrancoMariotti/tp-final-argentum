//
// Created by franco on 6/7/20.
//

#ifndef ARGENTUM_CLIENTCONNECTION_H
#define ARGENTUM_CLIENTCONNECTION_H


#include <Proxy/src/common_message.h>
#include <memory>
#include <Proxy/src/common_socket.h>
#include "ThClientSender.h"
#include "ThClientReceiver.h"

class ClientConnection {
    Socket client;
    ThClientSender sender;
    BlockingQueue<Message*> events;
    ThClientReceiver receiver;
    bool dead;
    void stop();
    friend class ThClientReceiver;
public:
    ClientConnection(Socket client, ProtectedList<std::unique_ptr<Message>>& messages);
    ClientConnection(ClientConnection&) = delete;
    bool isDead() const;
    void joinResources();
    void start();
    void finish();
    ~ClientConnection();

    void sendMessage(Message *event);
};


#endif //ARGENTUM_CLIENTCONNECTION_H
