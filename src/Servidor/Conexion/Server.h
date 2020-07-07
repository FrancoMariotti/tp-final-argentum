//
// Created by franco on 5/7/20.
//

#ifndef ARGENTUM_SERVER_H
#define ARGENTUM_SERVER_H


#include <Servidor/Modelo/Game.h>
#include "ThAcceptor.h"

class Server {
    bool keepTalking;
    Game game;
    ThAcceptor clientAcceptor;
    ProtectedConnections clients;
    ProtectedList<std::unique_ptr<Message>> events;
public:
    explicit Server(const std::string& service,const std::string& configFile);
    void start();
};


#endif //ARGENTUM_SERVER_H
