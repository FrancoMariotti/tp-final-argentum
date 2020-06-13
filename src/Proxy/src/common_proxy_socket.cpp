//
// Created by agustin on 13/6/20.
//

#include "common_proxy_socket.h"

int ProxySocket::writeToServer(const t_command &msg) {
    this->proxyServerSocket.push(msg);
    return 0;
}

t_command ProxySocket::readServer() {
    t_command msg = {"",0,0};
    if(!proxyServerSocket.isEmpty()){
        msg = proxyServerSocket.pop();
    }
    return msg;
}

int ProxySocket::writeToClient(const t_command &msg) {
    this->proxyClientSocket.push(msg);
    return 0;
}

t_command ProxySocket::readClient() {
    t_command msg = {"",0,0};
    if(!proxyServerSocket.isEmpty()){
        msg = proxyServerSocket.pop();
    }
    return msg;
}
