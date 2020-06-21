//
// Created by franco on 15/6/20.
//

#include "server_proxy_server.h"
#include "common_message.h"
#include "common_proxy_socket.h"

ProxyServer::ProxyServer(ProxySocket& proxySocket) :
    proxySocket(proxySocket)
    {}

void ProxyServer::run() {
    std::cout << "Server is running" << std::endl;
    proxySocket.writeToClient(std::unique_ptr<Message> (
            new Draw("hongo", 1, 1)));
    //En el parametro del write le paso un unique_ptr que en su constructor recibe un
    //new Mensaje donde mensaje es el mensaje especifico que quiero crear
    std::cout << "id del mensaje leido por el cliente: " << (proxySocket.readClient())->getId() << std::endl;

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