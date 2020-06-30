//
// Created by agustin on 20/6/20.
//

#include "client_th_recv.h"
#include "common_proxy_socket.h"
#include "common_message.h"

ThRecv::ThRecv(ProtectedList<std::unique_ptr<Message>> &serverEvents,
        ProxySocket &proxySocket) :
        serverEvents(serverEvents),
        proxySocket(proxySocket),
        keep_recieving(true)
        {}

ThRecv::ThRecv(ThRecv &&other) noexcept :
    serverEvents(other.serverEvents),
    proxySocket(other.proxySocket),
    keep_recieving(other.keep_recieving)
    {}

void ThRecv::run() {
    while(keep_recieving){
        /*Si no hay eventos se bloquea*/
        try{
            //std::cout << "recieving event" << std::endl;
            serverEvents.push(proxySocket.readClient());
        } catch ( ClosedQueueException &e){

        }
    }
}

void ThRecv::stop() {
    keep_recieving = false;
    /*proxy
     * el shutdown lo haria el server al desconectarse el jugador*/
    proxySocket.shutdown();
}

ThRecv::~ThRecv() {

}
