//
// Created by franco on 15/6/20.
//

#ifndef ARGENTUM_SERVER_PROXY_SERVER_H
#define ARGENTUM_SERVER_PROXY_SERVER_H


#include "Common/BlockingQueue.h"
#include "Common/Thread.h"

class ProxySocket;
class ProxyServer: public Thread{
    bool keepListening;
    ProxySocket& proxySocket;
    public:
        explicit ProxyServer(ProxySocket& proxySocket);
        void start() override;
        void run() override;
        void stop();
        bool somethingToRead();
        ~ProxyServer() override;
};


#endif //ARGENTUM_SERVER_PROXY_SERVER_H
