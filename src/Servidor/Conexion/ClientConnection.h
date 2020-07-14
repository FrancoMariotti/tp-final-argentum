//
// Created by franco on 6/7/20.
//

#ifndef ARGENTUM_CLIENTCONNECTION_H
#define ARGENTUM_CLIENTCONNECTION_H


#include <Common/Message.h>
#include <memory>
#include <Common/Socket.h>
#include "ThClientSender.h"
#include "ThClientReceiver.h"

class ClientConnection {
    std::string id;
    Socket client;
    ThClientSender sender;
    BlockingQueue<Message*> events;
    ThClientReceiver receiver;
    bool dead;
    void stop();
    friend class ThClientReceiver;
public:
    ClientConnection(Socket client,ProtectedList<std::unique_ptr<Message>>& messages);
    ClientConnection(ClientConnection&) = delete;
    bool isDead() const;
    std::string getId();
    void joinResources();
    void start();
    void finish();
    ~ClientConnection();

    void sendMessage(Message *event);
};


#endif //ARGENTUM_CLIENTCONNECTION_H
