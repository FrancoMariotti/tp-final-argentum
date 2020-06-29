#include "server_proxy_server.h"
#include "common_proxy_socket.h"
#include "common_message.h"
#include "../../Servidor/Modelo/Game.h"
#include "../../Servidor/Modelo/Event.h"
#include "../../Servidor/Modelo/EventMove.h"
#include "../../Servidor/Modelo/NormalWeapon.h"

ProxyServer::ProxyServer(ProxySocket& proxySocket) :
    keepListening(true),
    proxySocket(proxySocket)
    {}

void ProxyServer::run() {
    /*proxySocket.writeToClient(std::unique_ptr<Message> (
            new Draw("pasto", positions)));*/
    //En el parametro del write le paso un unique_ptr que en su constructor recibe un
    //new Mensaje donde mensaje es el mensaje especifico que quiero crear
    std::cout << "Server is running" << std::endl;
    Game game("config/config.json");
    game.createPlayer("franco", "human", "wizard");
    //Initialize Player debe mandar vida,mana,nivel,experiencia,raza, clase,armaduras, armas
    game.initializeMap();
    NormalWeapon sword("sword", 2, 5);
    game.storeInInventory("franco",&sword);
    game.sendUpdates(proxySocket);
    try{

        while(this->keepListening) {
            /*Si no hay eventos se bloquea*/
            std::unique_ptr<Message> msg = proxySocket.readServer();
            if (msg->getId() == MOVEMENT_MESSAGE_ID) {
                Offset offset(msg->getPlayerVelX(), msg->getPlayerVelY());
                Event* move = new EventMove(offset);
                move->execute(game, "franco");
                game.sendUpdates(proxySocket);
            }

        }
    } catch (ClosedQueueException &e){

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