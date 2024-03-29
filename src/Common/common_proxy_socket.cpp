//
// Created by agustin on 13/6/20.
//

#include "common_proxy_socket.h"
#include "Messages/Message.h"

void ProxySocket::writeToServer(std::unique_ptr<Message> msg) {
    this->proxyServerSocket.push(std::move(msg));
}

std::unique_ptr<Message> ProxySocket::readServer() {
    return proxyServerSocket.pop();
}

void ProxySocket::writeToClient(std::unique_ptr<Message> msg) {
    this->proxyClientSocket.push(std::move(msg));
}

std::unique_ptr<Message> ProxySocket::readClient() {
    return proxyClientSocket.pop();
}

void ProxySocket::shutdown() {
    proxyClientSocket.close();
    proxyServerSocket.close();
}

bool ProxySocket::isEmpty() {
    return proxyServerSocket.isEmpty();
}
