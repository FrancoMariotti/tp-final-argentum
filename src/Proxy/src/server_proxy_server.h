//
// Created by franco on 15/6/20.
//

#ifndef ARGENTUM_SERVER_PROXY_SERVER_H
#define ARGENTUM_SERVER_PROXY_SERVER_H


#include "common_blocking_queue.h"

class ProxySocket;
class ProxyServer {
    ProxySocket& proxySocket;
public:
    explicit ProxyServer(ProxySocket& proxySocket);
    void operator()();
    void run();
};


#endif //ARGENTUM_SERVER_PROXY_SERVER_H
