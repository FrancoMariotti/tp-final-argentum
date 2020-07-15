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
    int id;
    Socket client;
    ThClientSender sender;
    BlockingQueue<event_t> events;
    ThClientReceiver receiver;
    bool dead;
    void stop();
    friend class ThClientReceiver;
public:
    ClientConnection(int id,Socket client,ProtectedList<std::unique_ptr<Message>>& messages);
    ClientConnection(ClientConnection&) = delete;
    bool isDead() const;
    int getId();
    void joinResources();
    void sendMessage(int messageId,std::string data);
    void start();
    void finish();
    ~ClientConnection();
};


#endif //ARGENTUM_CLIENTCONNECTION_H
