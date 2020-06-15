//
// Created by agustin on 12/6/20.
//

#include <iostream>
#include "client_command.h"
#include "common_proxy_socket.h"

void Consume::operator()(ProxySocket &proxySocket, int i) {
    t_command command = {"consumir", i, 0};
    proxySocket.writeToServer(command);
}

void Consume::free() {
    delete this;
}


void Equip::operator()(ProxySocket &proxySocket, int i) {
    t_command command = {"equipar ",i, 0};
    proxySocket.writeToServer(command);
}

void Equip::free() {
    delete this;
}
