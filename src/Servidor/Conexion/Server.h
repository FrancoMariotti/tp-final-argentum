//
// Created by franco on 5/7/20.
//

#ifndef ARGENTUM_SERVER_H
#define ARGENTUM_SERVER_H


#include "ThAcceptor.h"

class Server {
    ThAcceptor clientAcceptor;
    BlockingQueue<std::unique_ptr<Message>> messages;
    ProtectedList<std::unique_ptr<Message>> events;
public:
    explicit Server(std::string service);
    void start();
};


#endif //ARGENTUM_SERVER_H
