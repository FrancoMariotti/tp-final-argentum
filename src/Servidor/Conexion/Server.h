//
// Created by franco on 5/7/20.
//

#ifndef ARGENTUM_SERVER_H
#define ARGENTUM_SERVER_H


#include "ThAcceptor.h"

class Server {
    ThAcceptor clientAcceptor;
public:
    explicit Server(std::string service);
};


#endif //ARGENTUM_SERVER_H
