//
// Created by franco on 15/6/20.
//

#ifndef ARGENTUM_SERVER_PROXY_SERVER_H
#define ARGENTUM_SERVER_PROXY_SERVER_H


#include "common_blocking_queue.h"

class ProxyServer {

public:
    t_command processCommand(t_command command);
};


#endif //ARGENTUM_SERVER_PROXY_SERVER_H
