#include <iostream>
#include "client_command.h"
#include "common_proxy_socket.h"

void Use::operator()(ProxySocket &proxySocket, int i) {
    t_command command = {"usar ",i, 0};
    proxySocket.writeToServer(command);
}

void Use::free() {
    delete this;
}
