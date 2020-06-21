//
// Created by franco on 15/6/20.
//

#include "server_proxy_server.h"
ProxyServer::ProxyServer(ProxySocket& proxySocket) :
    proxySocket(proxySocket)
    {}

void ProxyServer::run() {
    std::cout << "Server is running" << std::endl;
}

void ProxyServer::operator()() {
    this->run();
}

/*
t_command ProxyServer::processCommand(t_command command) {
    std::string type = command.command;
    t_command result;

    if (type == "m") {
        Offset offset(command.x,command.y);
        Event* event = new EventMove(offset);
        event->execute(game,"franco");
        delete event;
    }

    return game.sendPlayerPosition();
}*/