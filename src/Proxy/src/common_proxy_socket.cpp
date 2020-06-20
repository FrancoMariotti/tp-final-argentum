//
// Created by agustin on 13/6/20.
//

#include "common_proxy_socket.h"

void ProxySocket::writeToServer(std::unique_ptr<Message> msg) {
    //this->proxyServerSocket.push(std::move(msg));
}

std::unique_ptr<Message> ProxySocket::readServer() {;
    //return std::unique_ptr<Message>(proxyServerSocket.pop());
}

void ProxySocket::writeToClient(std::unique_ptr<Message> msg) {
    //this->proxyClientSocket.push(std::move(msg));
}

std::unique_ptr<Message> ProxySocket::readClient() {
    //return std::unique_ptr<Message>(proxyServerSocket.pop());
}
