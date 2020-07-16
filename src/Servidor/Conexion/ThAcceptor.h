#ifndef ARGENTUM_THACCEPTOR_H
#define ARGENTUM_THACCEPTOR_H

#include "vector"
#include "ProtectedConnections.h"
#include <Common/Thread.h>
#include <Common/Socket.h>
#include <Common/BlockingQueue.h>
#include <Proxy/src/client_protected_list.h>
#include <Common/Message.h>

class ClientConnection;

class ThAcceptor: public Thread {
    int counter;
    Socket acceptor;
    ProtectedConnections& clients;
    ProtectedList<std::unique_ptr<Message>>& events;
    bool keepTalking;
public:
    ThAcceptor(const std::string& service,ProtectedConnections& clients,
                                    ProtectedList<std::unique_ptr<Message>>& events);
    void start() override;
    void run() override;
    void stop();
    ~ThAcceptor() override;
};


#endif //ARGENTUM_THACCEPTOR_H
