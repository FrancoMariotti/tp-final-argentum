//
// Created by agustin on 12/6/20.
//

#include <iostream>
#include "client_command.h"
#include "common_proxy_socket.h"

void Consume::operator()(ProxySocket &proxySocket) {
    std::cout << "Consumir!" << std::endl;
    //t_command command = {"c",0, 0};
    //proxySocket.push(command);
}

void Consume::free() {
    delete this;
}

void Equip::operator()(ProxySocket &proxySocket) {
    std::cout << "Equipar!" << std::endl;
    //t_command command = {"e",0, 0};
    //proxySocket.push(command);
}

void Equip::free() {
    delete this;
}

void Move::operator()(ProxySocket &proxySocket) {
    std::cout << "Mover!" << std::endl;
    t_command player_movement = {"m",1, 1};
    proxySocket.writeToServer(player_movement);
}

void Move::free() {
    delete this;
}
