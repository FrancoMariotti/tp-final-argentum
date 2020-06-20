//
// Created by agustin on 19/6/20.
//

#include <iostream>
#include "client_th_send.h"
#include "common_proxy_socket.h"
#include "common_message.h"

ThSend::ThSend(BlockingQueue<std::unique_ptr<Message>> &clientEvents, ProxySocket &proxySocket) :
        clientEvents(clientEvents),
        proxySocket(proxySocket),
        keep_sending(true){

}

ThSend::ThSend(ThSend &&other) noexcept :
        clientEvents(other.clientEvents),
        proxySocket(other.proxySocket),
        keep_sending(true){
}

void ThSend::run() {
    std::cout << "sending event" << std::endl;
    try{
        while(this->keep_sending){
            proxySocket.writeToServer(clientEvents.pop());
        }
    } catch (ClosedQueueException &e){
        /*Antes de joinear cierro la cola Bloqueante lo que provoca una excepcion si esta vacia,
         * de esta manera termino la ejecucion*/
    }
}

ThSend::~ThSend() {

}

void ThSend::stop() {
    clientEvents.close();
    keep_sending = false;
}
