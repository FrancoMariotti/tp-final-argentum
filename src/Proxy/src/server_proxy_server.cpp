#include "server_proxy_server.h"
#include "common_proxy_socket.h"
#include "common_message.h"

ProxyServer::ProxyServer(ProxySocket& proxySocket) :
    keepListening(false),
    proxySocket(proxySocket)
    {}

void ProxyServer::run() {
    std::cout << "Server is running" << std::endl;
    //std::unique_ptr<Message> msg = proxySocket.readServer();
    /*proxySocket.writeToClient(std::unique_ptr<Message> (
            new Draw("pasto", 10, 10)));*/
    //En el parametro del write le paso un unique_ptr que en su constructor recibe un
    //new Mensaje donde mensaje es el mensaje especifico que quiero crear
    while(this->keepListening) {
        /*Si no hay eventos se bloquea*/
        std::unique_ptr<Message> msg = proxySocket.readServer();
        if(!msg) break;

        Movement* event = (Movement*) msg.release();

        std::cout << "MSG type:"<< event->getId() << std::endl;
        std::cout << "VEL X:"<< event->getPlayerVelX() << std::endl;
        std::cout << "VEL Y:"<< event->getPlayerVelY() << std::endl;


        proxySocket.writeToClient(std::unique_ptr<Message> (
                    new Movement(10,10)));

    }

    std::cout << "Server finaliza run" << std::endl;
    /*std::unique_ptr<Message> msg2 = proxySocket.readServer();
    std::cout << "MSG type:"<< msg2->getId() << std::endl;
    std::cout << "VEL X:"<< msg2->getPlayerVelX() << std::endl;
    std::cout << "VEL Y:"<< msg2->getPlayerVelY() << std::endl;
    proxySocket.writeToClient(std::unique_ptr<Message>(new Movement(2,2)));*/
}

void ProxyServer::start() {
    Thread::start();
}

void ProxyServer::stop() {
    this->keepListening = false;
}

ProxyServer::~ProxyServer() {}

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