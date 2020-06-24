#include "server_proxy_server.h"
#include "common_proxy_socket.h"
#include "common_message.h"
#include "../../Servidor/Modelo/Game.h"
#include "../../Servidor/Modelo/Event.h"
#include "../../Servidor/Modelo/EventMove.h"

ProxyServer::ProxyServer(ProxySocket& proxySocket) :
    keepListening(true),
    proxySocket(proxySocket)
    {}

void ProxyServer::run() {
    std::cout << "Server is running" << std::endl;
    //std::unique_ptr<Message> msg = proxySocket.readServer();
    /*proxySocket.writeToClient(std::unique_ptr<Message> (
            new Draw("pasto", 10, 10)));*/
    //En el parametro del write le paso un unique_ptr que en su constructor recibe un
    //new Mensaje donde mensaje es el mensaje especifico que quiero crear

    Game game("src/Servidor/config/config.json");
    game.createPlayer("franco", "human", "wizard");

    while(this->keepListening) {
        /*Si no hay eventos se bloquea*/
        std::unique_ptr<Message> msg = proxySocket.readServer();
        if(!msg) break;
        std::cout << "MSG type:"<< msg->getId() << std::endl;

        if (msg->getId() == 'm') {

            Movement* event = (Movement*) msg.release();
            std::cout << "VEL X:"<< event->getPlayerVelX() << std::endl;
            std::cout << "VEL Y:"<< event->getPlayerVelY() << std::endl;

            /*
            Offset offset(event->getPlayerVelX(), event->getPlayerVelX());
            Event* move = new EventMove(offset);
            move->execute(game, "franco");
            */
            proxySocket.writeToClient(std::unique_ptr<Message> (
                        new Movement(event->getPlayerVelX(),event->getPlayerVelY())));
            }

    }

    std::cout << "Server finaliza run" << std::endl;
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