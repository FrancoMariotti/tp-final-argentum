//
// Created by agustin on 12/6/20.
//

#include <iostream>
#include "client_command.h"

void Consume::operator()(BlockingQueue<t_command> &proxySocket) {
    std::cout << "Consumir!" << std::endl;
}

void Consume::free() {
    delete this;
}

void Equip::operator()(BlockingQueue<t_command> &proxySocket) {
    std::cout << "Equipar!" << std::endl;
}

void Equip::free() {
    delete this;
}

void Move::operator()(BlockingQueue<t_command> &proxySocket) {
    std::cout << "Mover!" << std::endl;
    t_command player_movement = {1, 1};
    proxySocket.push(player_movement);
}

void Move::free() {
    delete this;
}
