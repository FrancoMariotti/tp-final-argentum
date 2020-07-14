//
// Created by agustin on 20/6/20.
//

#include "client_th_recv.h"
#include "Common/common_proxy_socket.h"
#include "Common/Message.h"
#include "Common/Socket.h"

ThRecv::ThRecv(ProtectedList<std::unique_ptr<Message>> &serverEvents,
        Socket &socket) :
        serverEvents(serverEvents),
        socket(socket),
        keep_recieving(true)
        {}

ThRecv::ThRecv(ThRecv &&other) noexcept :
    serverEvents(other.serverEvents),
    socket(other.socket),
    keep_recieving(other.keep_recieving)
    {}

void ThRecv::run() {
    while(keep_recieving){
        /*Si no hay eventos se bloquea*/
        try {
            std::cout << "recieving event" << std::endl;

            Message* message = protocol.recieve(socket);
            if(message) serverEvents.push(std::unique_ptr<Message>(message));
            //serverEvents.push(proxySocket.readClient());
        } catch (std::exception &e){
             keep_recieving = false;
        }
    }
}

void ThRecv::stop() {
    keep_recieving = false;
    /*proxy
     * el shutdown lo haria el server al desconectarse el jugador*/
    socket.shutdown(SHUT_RDWR);
}

ThRecv::~ThRecv() = default;
