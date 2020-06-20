//
// Created by agustin on 19/6/20.
//

#include "client_th_send.h"
#include "common_proxy_socket.h"

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
    while(this->keep_sending){
        //proxySocket.writeToServer(clientEvents.pop());
    }
}

ThSend::~ThSend() {

}
